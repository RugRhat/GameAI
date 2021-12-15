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

    TargetLocation = FVector(0, 0, 0);
    // If ControlledTank is biggerTank && Health > 50 { return; }
    // If

    // Find destination to move to.
    // TargetLocation = CurrentLocation + FleeDistance;
}

void RetreatTask::Execute()
{
    if(TargetLocation == FVector(0, 0, 0)) { return; }

    TankController->SetFocalPoint(TargetLocation);
    TankController->MoveToLocation(TargetLocation);
}