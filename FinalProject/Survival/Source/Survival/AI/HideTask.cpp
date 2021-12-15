// Fill out your copyright notice in the Description page of Project Settings.


#include "HideTask.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"
#include "Survival/SurvivalGM.h"
#include "TankAI.h"
#include "TaskManager.h"

HideTask::HideTask(ATankAI* AIController) : TankAITask(AIController)
{
    Priority = 1;
}

HideTask::~HideTask() { }

void HideTask::Start()
{
    TankAITask::Start();

    UGameplayStatics::GetAllActorsOfClass(TankController->GetWorld(), TankController->CoverPointClass, CoverPoints);

    GameMode = Cast<ASurvivalGM>(UGameplayStatics::GetGameMode(TankController->GetWorld()));

    TargetActor = nullptr;
    float DistanceToCover = 100000.f;

    for(AActor* Point : CoverPoints)
    {
        // If a tank is already at cover point, pick different point       
        if(GameMode && !GameMode->IsCoverPointFree(Point, ControlledTank)) { continue; }

        // If cover point is too close to player, pick a new one
        float DistBetweenPlayerAndCover = (PlayerTank->GetActorLocation() - Point->GetActorLocation()).Size();
        if(DistBetweenPlayerAndCover < TankController->GetCoverRange()) { continue; }
 
        float DistanceToPoint = (ControlledTank->GetActorLocation() - Point->GetActorLocation()).Size();

        if(DistanceToPoint < DistanceToCover) 
        { 
            DistanceToCover = DistanceToPoint;
            TargetActor = Point;
        }
    }
}

void HideTask::Execute()
{
    if(TargetActor == nullptr || !bCanExecute) { return; }

    // if(GameMode &&  GameMode->NumOfTanksAttacking != 0) { GameMode->NumOfTanksAttacking--; }

    TankController->SetFocus(TargetActor);
    TankController->MoveToActor(TargetActor);

    // If tank has stopped moving, complete execution
    if(TankController->GetMoveStatus() == EPathFollowingStatus::Type::Idle) { TankAITask::Execute(); }    
}
