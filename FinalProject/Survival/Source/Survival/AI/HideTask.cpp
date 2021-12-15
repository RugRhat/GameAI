// Fill out your copyright notice in the Description page of Project Settings.


#include "HideTask.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"
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

    TargetActor = nullptr;
    float DistanceToCover = 100000.f;

    for(AActor* Point : CoverPoints)
    {
        if(Point->GetActorLocation() == ControlledTank->GetActorLocation()) { continue; }
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

    TankController->SetFocus(TargetActor);

    if(!(TankController->GetMoveStatus() == EPathFollowingStatus::Type::Moving)) { TankController->MoveToActor(TargetActor); }

    // If tank has stopped moving, complete execution
    if(TankController->GetMoveStatus() == EPathFollowingStatus::Type::Idle) { TankAITask::Execute(); }    
}
