// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVAL_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	float GetMaxHealth() const { return MaxHealth; }
	float GetHealth() const { return Health; }

	void RegenHealth();

private:
	class ASurvivalGM* GameModeRef;

	AActor* Owner;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere)
	float Health = 0.f;
	
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InistigatedBy, AActor* DamageCauser);
		
};
