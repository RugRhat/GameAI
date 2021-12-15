// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTank.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABaseTank::ABaseTank()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void ABaseTank::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(HealthRegenTimerHandle, this, &ABaseTank::RegenHealth, HealthRegenRate, true, false);
}

void ABaseTank::Fire()
{
	if(ProjectileClass == nullptr) { return; } 

	FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

	AProjectile* TempProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
	TempProjectile->SetOwner(this);
}

void ABaseTank::HandleDestruction()
{
	if(DeathParticle){
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation(), FRotator::ZeroRotator);
	}

	if(DeathSound){
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}

	bAlive = false;

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);	
}

