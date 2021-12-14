// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTank.h"
#include "PlayerTank.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API APlayerTank : public ABaseTank
{
	GENERATED_BODY()
	
public: 
	APlayerTank();

	// bool GetPlayerAlive() { return bAlive; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotateSpeed = 70.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthRegenRate = 2.f;

	void Move(float AxisValue);
	void Rotate(float AxisValue);

	// bool bAlive = true;

	FTimerHandle HealthRegenTimerHandle;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// virtual void HandleDestruction() override;
};
