// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HealthComponent.h"
#include "BaseTank.generated.h"

UCLASS()
class SURVIVAL_API ABaseTank : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseTank();

	UFUNCTION(BlueprintPure)
	float GetHealth() const { return HealthComponent->GetHealth(); }

	void RegenHealth() { HealthComponent->RegenHealth(); }

	bool TankAlive() { return bAlive; }

	virtual void Fire();
	virtual void HandleDestruction();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthRegenRate = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* DeathSound;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	// TSubclassOf<UCameraShake> DeathShake;

	bool bAlive = true;

	FTimerHandle HealthRegenTimerHandle;

	virtual void BeginPlay() override;

};
