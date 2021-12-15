// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "BaseTank.h"
// #include "EnemyTank.h"
#include "Kismet/GameplayStatics.h"
#include "SurvivalGM.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Health = MaxHealth;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GameModeRef = Cast<ASurvivalGM>(UGameplayStatics::GetGameMode(GetWorld()));

	Owner = GetOwner();

	if(Owner) { Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage); } 
	else { UE_LOG(LogTemp, Warning, TEXT("Health component has no reference to owner")); }
}

void UHealthComponent::RegenHealth()
{
	if(Health <= (MaxHealth - 5)) { Health += 5; }
}

// Decides how to react when damage is taken (loss health or die).
void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InistigatedBy, AActor* DamageCauser)
{
	if(Damage == 0 || Health == 0){return;}

	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);

	if(Health <= 0)
	{
		if(GameModeRef) 
		{ 
			ABaseTank* MyTank = Cast<ABaseTank>(Owner);
			if(MyTank && MyTank->TankAlive()) { GameModeRef->TankDestroyed(MyTank); } 
		}
		else { UE_LOG(LogTemp, Warning, TEXT("Health component has no reference to GameMode")); }
	}
}

