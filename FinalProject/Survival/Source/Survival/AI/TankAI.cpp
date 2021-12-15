// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAI.h"
#include "Kismet/GameplayStatics.h"
#include "TaskManager.h"

ATankAI::ATankAI()
{
    PrimaryActorTick.bCanEverTick = true;

    TaskManagerRef = new TaskManager(this);
}

void ATankAI::BeginPlay()
{
    Super::BeginPlay();

    ControlledTank = Cast<AEnemyTank>(GetPawn()); 
    PlayerTank = Cast<APlayerTank>(UGameplayStatics::GetPlayerPawn(this, 0));

    // TaskManagerRef->StartNewTask();
    TaskManagerRef->CheckParameters();
    
    // Update task according to TaskUpdateFrequency
    GetWorld()->GetTimerManager().SetTimer(TaskTimer, this, &ATankAI::UpdateTask, TaskUpdateFrequency, true);
}

void ATankAI::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    TaskManagerRef->RunTask();

    if(GetMoveStatus() == EPathFollowingStatus::Type::Idle) { SetFocus(PlayerTank); }
}

void ATankAI::UpdateTask()
{
    // TaskManagerRef->StartNewTask();
    TaskManagerRef->CheckParameters();
}

// void ATankAI::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
// {
//     Super::OnMoveCompleted(RequestID, Result);

//     SetFocus(PlayerTank);
// }


// void ATankAI::UpdatePlayerLocation()
// {
//     if(PlayerTank == nullptr) { return; }
//     PlayerLocation = PlayerTank->GetActorLocation();

//     if(ControlledTank == nullptr) { return; }
//     float DistanceToPlayer = FVector(ControlledTank->GetActorLocation() - PlayerLocation).Size();

//     if(DistanceToPlayer <= AttackRange) { bPlayerInRange = true; }
//     else { bPlayerInRange = false; }
// }

// void ATankAI::UpdateTask()
// {
//     if(bPlayerInRange)
//     {
//         // if(bBiggerTank || OtherTankAttacking()) { AttackPlayer(); }

//         if(ControlledTank->GetHealth() <= 50) { }
//         if(CurrentGoal = Goal::Retreat)
//         {
//             // if other tanks attacking && health > 50, move to attack player
//             // else find cover
//         }
//         if(CurrentGoal = Goal::Hide)
//         {
//             // if other tanks attacking, attack from cover
//             // else continue hiding
//         }
//     }
//     else
//     {
//        // if(bBiggerTank) { SearchForPlayer(); }
//     }
//     // if(bPlayerInPossibleAttackRange)
//     // {
//     //     if(CurrentGoal = Goal::Hide)
//     //     {
//     //         // if other tanks attacking, move to attack player
//     //         // else continue hiding
//     //     }
//     // }

// }

// bool ATankAI::AttackPlayer()
// {
//     bool TaskSuccessful = false;

//     if(CurrentGoal != Goal::Attack)
//     {
//         CurrentGoal = Goal::Attack;

//         SetFocus(PlayerTank);

//     }
//     MoveToActor(PlayerTank, FiringRange, true, true, true);
    
//     // ControlledTank-> Fire();

//     return TaskSuccessful;
// }

// void ATankAI::FindCover()
// {
//     //Loop through cover points
//     // Find nearest one
//     // Assign location as nearest cover point
//     // SetFocus(CoverLocation);
//     // MoveTo(CoverLocation);
// }