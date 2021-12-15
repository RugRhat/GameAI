// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAITask.h"

/**
 * 
 */
class SURVIVAL_API RetreatTask : public TankAITask
{

public:
	RetreatTask(ATankAI* );
	~RetreatTask();

	void Start() override;
	void Execute();
};
