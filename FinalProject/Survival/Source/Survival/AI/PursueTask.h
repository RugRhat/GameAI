// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAITask.h"

/**
 * 
 */
class SURVIVAL_API PursueTask : public TankAITask
{
	
public:
	PursueTask(ATankAI* );
	~PursueTask();

	void Start() override;
	void Execute();
};
