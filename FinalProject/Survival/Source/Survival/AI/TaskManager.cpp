// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskManager.h"
#include "AttackTask.h"
#include "HideTask.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Survival/SurvivalGM.h"
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
}

TaskManager::~TaskManager() { }

void TaskManager::AddTask(TaskType TaskType, TankAITask* Task)
{
    TaskMap.Add(TaskType, Task);
}

void TaskManager::StartNewTask()
{
    bTaskComplete = false;
    
    // Clear heap before queueing new tasks
    TaskPriorityQueue.Empty();

    for(auto Task : TaskMap)
    {
        // Don't add a task with a 0 priority to queue.
        if(Task.Value->GetPriority() == 0) { continue; }            

        Task.Value->Start();
        TaskPriorityQueue.HeapPush(TaskPriority(Task.Value), TaskPriorityPredicate());
    }
}

// Run task at the top of queue
void TaskManager::RunTask()
{
    TaskPriority TopTask;

    if(bTaskComplete && !TaskPriorityQueue.Num() == 0) 
    {
        TaskPriorityQueue.HeapPopDiscard(TaskPriorityPredicate()); 
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
        CurrentTask = TopTask.Task;
        CurrentTask->Execute();
    }
}

// Refresh parameters based on changes in world
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
    ASurvivalGM* GameMode = Cast<ASurvivalGM>(UGameplayStatics::GetGameMode(TankController->GetWorld()));
    if(GameMode) 
    { 
        if(GameMode->NumOfTanksAttacking > 0) { bOtherAttackers = true; }
        else { bOtherAttackers = false; }
    }

    UpdatePriorities();
}

// Update priorities based on changes in parameters
void TaskManager::UpdatePriorities()
{
    TEnumAsByte<TaskType> NewTaskType;

    // Always prioritize survival
    if(bNeedToHeal) { NewTaskType = PrioritizeHiding(); }

    // Big tanks will always prioritize attacking player
    else if(TankController->GetControlledTank()->GetTankSize()) 
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
        // Ensuring that tank doesn't keep firing despite change in task
        if(TankController->GetControlledTank()->IsFiring()) { TankController->GetControlledTank()->StopFiring(); }

        CurrentTaskType = NewTaskType;
        UE_LOG(LogTemp, Warning, TEXT("Priorities Changed To: %s"), *UEnum::GetValueAsString(CurrentTaskType));

        StartNewTask();
    }

    return;
}

TEnumAsByte<TaskType> TaskManager::PrioritizeHiding()
{
    HideTaskRef->SetPriority(1);            // Finding cover given highest priority
    AttackTaskRef->SetPriority(0);
    PursueTaskRef->SetPriority(0);

    AttackTaskRef->bCanExecute = false;

    float TankHealth = TankController->GetControlledTank()->GetHealth();
    UE_LOG(LogTemp, Warning, TEXT("Health: %f"), TankHealth);

    return TaskType::HIDE; 
}

TEnumAsByte<TaskType> TaskManager::PrioritizeMovingToAttack()
{
    PursueTaskRef->SetPriority(1);          // Pursuing player set to highest priority
    AttackTaskRef->SetPriority(2);          // Attacking player given secondary priority
    HideTaskRef->SetPriority(0);

    return TaskType::PURSUE;
}

TEnumAsByte<TaskType> TaskManager::PrioritizeAttacking()
{
    AttackTaskRef->SetPriority(1);          // Attacking player set to highest priority
    PursueTaskRef->SetPriority(2);          // Pursuing player given secondary priority
    HideTaskRef->SetPriority(0);

    AttackTaskRef->bCanExecute = true;

    return TaskType::ATTACK;
}
