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
	
	void TankDestroyed(ABaseTank* DestroyedTank);

private:
	void SpawnEnemy(TSubclassOf<AEnemyTank> EnemyClass);

	class APlayerTank* PlayerTank;
	
	TArray<AActor*> SpawnPoints;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemyTank> BigTankClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemyTank> SmallTankClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> SpawnPointClass;

	UPROPERTY(EditDefaultsOnly)
	float SpawnRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Score = 0;

	virtual void BeginPlay() override;
};
