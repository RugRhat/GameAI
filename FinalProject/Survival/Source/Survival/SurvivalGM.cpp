// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivalGM.h"
// #include "EnemyTank.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerTank.h"

// bool ASurvivalGM::IsCoverPointFree(UPARAM(ref) AActor* CoverPoint)
// {
//     return true;
// }

void ASurvivalGM::BeginPlay()
{
    Super::BeginPlay();

    PlayerTank = Cast<APlayerTank>(UGameplayStatics::GetPlayerPawn(this, 0));

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), SpawnPointClass, SpawnPoints);
}

void ASurvivalGM::SpawnEnemy(TSubclassOf<AEnemyTank> EnemyClass)
{
    if(SpawnPoints.Num() == 0) { return; }

    for (AActor* Point : SpawnPoints)
    {
        // If cover point is too close to player, pick a new one
        float DistBetweenPlayerAndPoint = (PlayerTank->GetActorLocation() - Point->GetActorLocation()).Size();
        if(DistBetweenPlayerAndPoint < SpawnRange) { continue; }

        AEnemyTank* EnemyTank = GetWorld()->SpawnActor<AEnemyTank>(EnemyClass, Point->GetActorLocation(), Point->GetActorRotation());
        
        break;
    }
}

void ASurvivalGM::TankDestroyed(ABaseTank* DestroyedTank)
{
    UE_LOG(LogTemp, Warning, TEXT("Tank Destroyed: %s"), *DestroyedTank->GetName());

    if(DestroyedTank == PlayerTank)
    {
        PlayerTank->HandleDestruction();

        GameOver();
    } 

    else 
    {
        Score++;

        AEnemyTank* EnemyTank = Cast<AEnemyTank>(DestroyedTank);
        bool bBigTank = EnemyTank->GetTankSize();
        EnemyTank->PrepForDestruction();

        if(bBigTank) { SpawnEnemy(BigTankClass); }
        else { SpawnEnemy(SmallTankClass); }
    }
}

