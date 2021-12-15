// Fill out your copyright notice in the Description page of Project Settings.


#include "PursueTask.h"
#include "Navigation/PathFollowingComponent.h"
#include "TankAI.h"
#include "TaskManager.h"

PursueTask::PursueTask(ATankAI* AIController) : TankAITask(AIController)
{
    Priority = 3;
}

PursueTask::~PursueTask() { }

void PursueTask::Start()
{
    TankAITask::Start();

    TargetActor = PlayerTank;
}
	
void PursueTask::Execute()
{
    if(!bCanExecute) { return; }

    TankController->SetFocus(TargetActor);

    if(!(TankController->GetMoveStatus() == EPathFollowingStatus::Type::Moving)) 
        TankController->MoveToActor(TargetActor, TankController->GetFiringRange()/2);

    // If tank has stopped moving, complete execution
    if(TankController->GetMoveStatus() == EPathFollowingStatus::Type::Idle) { TankAITask::Execute(); }
}
