// Fill out your copyright notice in the Description page of Project Settings.


#include "PursueTask.h"
#include "Navigation/PathFollowingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Survival/SurvivalGM.h"
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
    TankController->MoveToActor(TargetActor, TankController->GetFiringRange() / 1.5);
        
    // If tank has stopped moving, complete execution
    if(TankController->GetMoveStatus() == EPathFollowingStatus::Type::Idle) { TankAITask::Execute(); }
}
