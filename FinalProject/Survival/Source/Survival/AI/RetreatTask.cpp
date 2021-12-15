// Fill out your copyright notice in the Description page of Project Settings.


#include "RetreatTask.h"
#include "TankAI.h"

RetreatTask::RetreatTask(ATankAI* AIController) : TankAITask(AIController)
{
    Priority = 3;
}

RetreatTask::~RetreatTask() { }

void RetreatTask::Start()
{
    TankAITask::Start();

    // UGameplayStatics::GetAllActorsOfClass(TankController->GetWorld(), TankController->CoverPointClass, CoverPoints);

    // TargetActor = nullptr;
    // float DistanceToCover = 100000.f;

    // for(AActor* Point : CoverPoints)
    // {
    //     if(Point->GetActorLocation() == ControlledTank->GetActorLocation()) { continue; }
    //     float DistanceToPoint = (ControlledTank->GetActorLocation() - Point->GetActorLocation()).Size();

    //     if(DistanceToPoint < DistanceToCover) 
    //     { 
    //         DistanceToCover = DistanceToPoint;
    //         TargetActor = Point;
    //     }
    // }
}

void RetreatTask::Execute()
{
    if(TargetLocation == FVector(0, 0, 0)) { return; }

    TankController->SetFocalPoint(TargetLocation);
    TankController->MoveToLocation(TargetLocation);
}