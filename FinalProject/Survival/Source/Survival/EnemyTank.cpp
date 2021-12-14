// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTank.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerTank.h"

void AEnemyTank::BeginPlay()
{
    Super::BeginPlay();

    PlayerTank = Cast<APlayerTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AEnemyTank::Fire()
{
    if(TankAlive() && PlayerTank->TankAlive()) { Super::Fire(); }
}

void AEnemyTank::HandleDestruction()
{
    Super::HandleDestruction();

    Destroy();
}