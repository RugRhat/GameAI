// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class SURVIVAL_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageType;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UParticleSystemComponent* ParticleTrail;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UParticleSystem* HitParticle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundBase* LaunchSound;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// TSubclassOf<UCameraShake> HitShake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed = 1300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 25.f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
