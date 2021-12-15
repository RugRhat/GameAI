// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "TankAI.h"

class ATankAI;

class SURVIVAL_API TankAITask
{

public:
	TankAITask(ATankAI* );

	virtual ~TankAITask();
	virtual void Start();
	virtual void Execute();

	void SetPriority(int PriorityLevel) { Priority = PriorityLevel; }
	
	int GetPriority() const { return Priority; }

	bool bCanExecute;

protected:
	class AEnemyTank* ControlledTank;
	class APlayerTank* PlayerTank;

	ATankAI* TankController;

	int Priority = 1;

	FVector TargetLocation;
	AActor* TargetActor;

};
