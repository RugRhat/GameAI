// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Survival/EnemyTank.h"
#include "Survival/PlayerTank.h"
// #include "TaskManager.h"
#include "TankAI.generated.h"

class TaskManager;

UCLASS()
class SURVIVAL_API ATankAI : public AAIController
{
	GENERATED_BODY()

public:
	ATankAI();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> CoverPointClass;

	AEnemyTank* GetControlledTank() const { return ControlledTank; }
	APlayerTank* GetPlayerTank() const { return PlayerTank; }

	TaskManager* GetTaskManager() const { return TaskManagerRef; }

	float GetAttackRange() const { return AttackRange; }
	float GetFiringRange() const { return FiringRange; }
	float GetCoverRange() const { return CoverRange; }

	void HandleDestruction();

	bool ShouldContinue() const { return bShouldContinue; }

	void DoubleCheckTanks();

private:
	UPROPERTY(EditDefaultsOnly)
	float CoverRange = 1500.f;

	UPROPERTY(EditDefaultsOnly)
	float AttackRange = 1000.f;

	UPROPERTY(EditDefaultsOnly)
	float FiringRange = 750.f;

	UPROPERTY(EditDefaultsOnly)
	float TaskUpdateFrequency = 0.5f;

	void UpdateTask();
	void BeginTasks();

	AEnemyTank* ControlledTank;
	APlayerTank* PlayerTank;

	TaskManager* TaskManagerRef;

	FTimerHandle TaskTimer;
	FTimerHandle DelayTimer;

	bool bShouldContinue;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
};
