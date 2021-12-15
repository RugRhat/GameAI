// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTank.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerTank.h"
#include "SurvivalGM.h"

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
    // UE_LOG(LogTemp, Warning, TEXT("Start firing called..."));

    // Update task according to TaskUpdateFrequency
    GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &AEnemyTank::Fire, FireRate, true);

    ASurvivalGM* GameMode = Cast<ASurvivalGM>(UGameplayStatics::GetGameMode(GetWorld()));
    if(GameMode) { GameMode->NumOfTanksAttacking++; }
}

void AEnemyTank::StopFiring()
{
    // UE_LOG(LogTemp, Warning, TEXT("Stop firing called..."));
    GetWorld()->GetTimerManager().ClearTimer(FireTimer);

    ASurvivalGM* GameMode = Cast<ASurvivalGM>(UGameplayStatics::GetGameMode(GetWorld()));
    if(GameMode) { GameMode->NumOfTanksAttacking--; }
}

bool AEnemyTank::IsFiring()
{
    return GetWorld()->GetTimerManager().IsTimerActive(FireTimer);
}

void AEnemyTank::HandleDestruction()
{
    Super::HandleDestruction();

    Destroy();
}
