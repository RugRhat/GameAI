// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTank.h"
#include "EnemyTank.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API AEnemyTank : public ABaseTank
{
	GENERATED_BODY()

public:
	// bool GetPlayerAlive();

	virtual void Fire() override;

private:
	class APlayerTank* PlayerTank;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void HandleDestruction() override;
};
