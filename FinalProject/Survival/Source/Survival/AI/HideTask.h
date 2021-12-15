// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAITask.h"

/**
 * 
 */
class SURVIVAL_API HideTask : public TankAITask
{
public:
	HideTask(ATankAI* );
	~HideTask();

	void Start() override;
	void Execute();

private:
	TArray<AActor*> CoverPoints;

	class ASurvivalGM* GameMode;
};
