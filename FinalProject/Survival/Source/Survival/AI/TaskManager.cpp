// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskManager.h"
#include "AttackTask.h"
#include "HideTask.h"
#include "Kismet/KismetMathLibrary.h"
#include "PursueTask.h"

TaskManager::TaskManager(ATankAI* AIController)
{
    UE_LOG(LogTemp, Warning, TEXT("Task Manager Created..."));

    TankController = AIController;
    CurrentTask = nullptr;

    PursueTaskRef = new PursueTask(AIController);
    AddTask(PURSUE, PursueTaskRef);

    AttackTaskRef = new AttackTask(AIController);
    AddTask(ATTACK, AttackTaskRef);

    HideTaskRef = new HideTask(AIController);
    AddTask(HIDE, HideTaskRef);

    // AddTask(WANDER, new WanderTask(TankController));
    // AddTask(RETREAT, new RetreatTask(TankController));
}

TaskManager::~TaskManager() { }

void TaskManager::AddTask(TaskType TaskType, TankAITask* Task)
{
    TaskMap.Add(TaskType, Task);
}

void TaskManager::StartNewTask()
{
    bTaskComplete = false;

    for(auto Task : TaskMap)
    {
        if(Task.Value->GetPriority() == 0) { continue; }
        Task.Value->Start();
        TaskPriorityQueue.HeapPush(TaskPriority(Task.Value), TaskPriorityPredicate());
    }
}

void TaskManager::RunTask()
{
    TaskPriority TopTask;

    if(bTaskComplete && !TaskPriorityQueue.Num() == 0) 
    {
        UE_LOG(LogTemp, Warning, TEXT("Popping old task. Current heap size: %d"), TaskPriorityQueue.Num());
        // UE_LOG(LogTemp, Warning, TEXT("Predicate: %s"), *TaskPriorityPredicate().ToString());
        TaskPriorityQueue.HeapPopDiscard(TaskPriorityPredicate()); 
        UE_LOG(LogTemp, Warning, TEXT("New heap size: %d"), TaskPriorityQueue.Num());
        bTaskComplete = false;
    }
    
    if(TaskPriorityQueue.Num() == 0) 
    { 
        TopTask.Task = nullptr; 

        StartNewTask();
    }
    else 
    { 
        TopTask =  TaskPriorityQueue.HeapTop(); 
        // UE_LOG(LogTemp, Warning, TEXT("Top Task: %d"), TopTask.Task);

        CurrentTask = TopTask.Task;

        // UE_LOG(LogTemp, Warning, TEXT("CurrentTask: %s"), *UEnum::GetValueAsString(CurrentTaskType));

        CurrentTask->Execute();
    }
}

void TaskManager::CheckParameters()
{
    FVector TankLocation = TankController->GetControlledTank()->GetActorLocation();
    FVector PlayerLocation = TankController->GetPlayerTank()->GetActorLocation();

    float DistanceToPlayer = FVector(TankLocation - PlayerLocation).Size();
    
    // Check if player in range
    if(DistanceToPlayer <= TankController->GetAttackRange()) { bPlayerInRange = true; }
    else { bPlayerInRange = false;}

    // Check if player in firing range
    if(DistanceToPlayer <= TankController->GetFiringRange()) { bPlayerInFiringRange = true; }
    else { bPlayerInFiringRange = false;}

    float TankHealth = TankController->GetControlledTank()->GetHealth();

    // Check if player needs to heal
    if(TankHealth < 50) { bNeedToHeal = true; }
    else { bNeedToHeal = false; }

    // Check if player fully healed
    if(TankHealth == TankController->GetControlledTank()->GetMaxHealth()) { bAtFullHealth = true; }
    else { bAtFullHealth = false; }

    // Check if other tanks attacking player
    // Get game mode and check if 
    // if(NumOfTanksAttacking > 1) { bOtherAttackers = true; }
    // else { bOtherAttackers = false; }

    UpdatePriorities();
}

void TaskManager::UpdatePriorities()
{
    TEnumAsByte<TaskType> NewTaskType;

    // Always prioritize survival
    if(bNeedToHeal) { NewTaskType = PrioritizeHiding(); }

    // Big tanks will always prioritize attacking player
    if(TankController->GetControlledTank()->GetTankSize()) 
    { 
        if(bPlayerInFiringRange) { NewTaskType = PrioritizeAttacking(); }
        else {NewTaskType = PrioritizeMovingToAttack(); }
    }

    // Attack from current position
    else if(bPlayerInFiringRange) { NewTaskType = PrioritizeAttacking(); }    

    // Small tanks only consider moving to attack if they have support
    else if(bPlayerInRange && bOtherAttackers) 
    {
        // Move closer to attack
        if(bAtFullHealth) { NewTaskType = PrioritizeMovingToAttack(); }   
        
        // Attack from cover
        else { NewTaskType = PrioritizeAttacking(); }                
    }

    // Default to hiding
    else { NewTaskType = PrioritizeHiding(); }

    if(CurrentTaskType != NewTaskType)
    {
        if(TankController->GetControlledTank()->IsFiring()) { TankController->GetControlledTank()->StopFiring(); }

        CurrentTaskType = NewTaskType;
        UE_LOG(LogTemp, Warning, TEXT("Priorities Changed To: %s"), *UEnum::GetValueAsString(CurrentTaskType));
        StartNewTask();
    }

    return;
}

TEnumAsByte<TaskType> TaskManager::PrioritizeHiding()
{
    HideTaskRef->SetPriority(1);
    PursueTaskRef->SetPriority(0);
    AttackTaskRef->SetPriority(0);

    AttackTaskRef->bCanExecute = false;

    return TaskType::HIDE; 
}

TEnumAsByte<TaskType> TaskManager::PrioritizeMovingToAttack()
{
    PursueTaskRef->SetPriority(1);
    AttackTaskRef->SetPriority(0);
    HideTaskRef->SetPriority(0);

    // if(bPlayerInFiringRange) { AttackTaskRef->bCanExecute = true; }

    return TaskType::PURSUE;
}

TEnumAsByte<TaskType> TaskManager::PrioritizeAttacking()
{
    AttackTaskRef->SetPriority(1);
    PursueTaskRef->SetPriority(0);
    HideTaskRef->SetPriority(0);

    AttackTaskRef->bCanExecute = true;

    return TaskType::ATTACK;
}