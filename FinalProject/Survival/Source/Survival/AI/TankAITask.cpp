// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAITask.h"
#include "TankAI.h"
#include "TaskManager.h"

TankAITask::TankAITask(ATankAI* AIController)
{
    TankController = AIController;
}

TankAITask::~TankAITask() { }

void TankAITask::Start() 
{
    ControlledTank = TankController->GetControlledTank();
    PlayerTank = TankController->GetPlayerTank();
    
    bCanExecute = true;
}

void TankAITask::Execute() 
{ 
    TaskManager* TaskManagerRef = TankController->GetTaskManager();
    // if(TaskManagerRef->bTaskComplete) { return; }

    TaskManagerRef->bTaskComplete = true;

    bCanExecute = false;
}
