// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAITask.h"

/**
 * 
 */
class SURVIVAL_API AttackTask : public TankAITask
{
	
public:
	AttackTask(ATankAI* );
	~AttackTask();

	void Start() override;
	void Execute();
};
