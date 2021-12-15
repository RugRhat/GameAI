// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackTask.h"
#include "TankAI.h"
#include "TaskManager.h"

AttackTask::AttackTask(ATankAI* AIController) : TankAITask(AIController)
{
    Priority = 2;
}

AttackTask::~AttackTask() { }

void AttackTask::Start()
{
    TankAITask::Start();

    TargetActor = PlayerTank;
}

void AttackTask::Execute()
{
    if(!bCanExecute) { return; }

    TankController->SetFocus(TargetActor);

    if(ControlledTank->IsFiring()) { return; }

    UE_LOG(LogTemp, Warning, TEXT("Attacking..."));

    ControlledTank->StartFiring();

    TankAITask::Execute();
}
