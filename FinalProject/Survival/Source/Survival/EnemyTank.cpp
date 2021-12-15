// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTank.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerTank.h"
#include "SurvivalGM.h"
#include "AI/TankAI.h"

void AEnemyTank::BeginPlay()
{
    Super::BeginPlay();

    PlayerTank = Cast<APlayerTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AEnemyTank::Fire()
{
    if(TankAlive() && PlayerTank->TankAlive()) { Super::Fire(); }
}

void AEnemyTank::StartFiring()
{
    // Call Fire() according to FireRate
    GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &AEnemyTank::Fire, FireRate, true);

    // Inform the game mode that the tank is currently attacking
    ASurvivalGM* GameMode = Cast<ASurvivalGM>(UGameplayStatics::GetGameMode(GetWorld()));
    if(GameMode) { GameMode->NumOfTanksAttacking++; }
}

void AEnemyTank::StopFiring()
{
    GetWorld()->GetTimerManager().ClearTimer(FireTimer);

    // Inform the game mode that the tank is no longer attacking
    ASurvivalGM* GameMode = Cast<ASurvivalGM>(UGameplayStatics::GetGameMode(GetWorld()));
    if(GameMode) { GameMode->NumOfTanksAttacking--; }
}

bool AEnemyTank::IsFiring()
{
    return GetWorld()->GetTimerManager().IsTimerActive(FireTimer);
}

void AEnemyTank::PrepForDestruction()
{
    UE_LOG(LogTemp, Warning, TEXT("%s: Prepping for destruction"), *GetName());

    ATankAI* TankController = Cast<ATankAI>(GetController());
    if(TankController) { TankController->HandleDestruction(); }

    // Handle destruction after destruction delay
    GetWorld()->GetTimerManager().SetTimer(DestructionTimer, this, &AEnemyTank::HandleDestruction, DestructionDelay, false);
}

void AEnemyTank::HandleDestruction()
{
    Super::HandleDestruction();

    Destroy();
}
