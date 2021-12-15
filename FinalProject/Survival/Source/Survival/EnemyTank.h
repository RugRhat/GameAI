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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AActor* CurrentCoverPoint;

	virtual void Fire() override;

	float GetMaxHealth() const { return HealthComponent->GetMaxHealth(); }

	bool GetTankSize() const { return bIsBigTank; }

	void StartFiring();
	bool IsFiring();
	void StopFiring();
	
	void PrepForDestruction(); 

private:
	UPROPERTY(EditDefaultsOnly)
	bool bIsBigTank;

	UPROPERTY(EditDefaultsOnly)
	float FireRate = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float DestructionDelay = 0.5f;
	
	class APlayerTank* PlayerTank;

	FTimerHandle FireTimer;
	FTimerHandle DestructionTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void HandleDestruction() override;

};
