// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyTank.h"
#include "GameFramework/GameModeBase.h"
#include "SurvivalGM.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API ASurvivalGM : public AGameModeBase
{
	GENERATED_BODY()

public: 
	UFUNCTION(BlueprintImplementableEvent)
	bool IsCoverPointFree(const AActor* CoverPoint, const AEnemyTank* EnemyTank);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 NumOfTanksAttacking;
	
};
