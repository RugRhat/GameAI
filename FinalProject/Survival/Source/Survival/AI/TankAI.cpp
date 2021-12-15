// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAI.h"
#include "Kismet/GameplayStatics.h"
#include "TaskManager.h"

ATankAI::ATankAI()
{
    PrimaryActorTick.bCanEverTick = true;

    TaskManagerRef = new TaskManager(this);
}

void ATankAI::BeginPlay()
{
    Super::BeginPlay();

    bShouldContinue = true;

    ControlledTank = Cast<AEnemyTank>(GetPawn()); 
    PlayerTank = Cast<APlayerTank>(UGameplayStatics::GetPlayerPawn(this, 0));

    // Have a short delay before begining tasks.
    GetWorld()->GetTimerManager().SetTimer(DelayTimer, this, &ATankAI::BeginTasks, 2.f, false);
}

void ATankAI::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    TaskManagerRef->RunTask();

    // If not moving, look at player
    if(GetMoveStatus() == EPathFollowingStatus::Type::Idle) { SetFocus(PlayerTank); }
}

void ATankAI::BeginTasks()
{
    TaskManagerRef->CheckParameters();

    GetWorld()->GetTimerManager().SetTimer(TaskTimer, this, &ATankAI::UpdateTask, TaskUpdateFrequency, true);
}

void ATankAI::UpdateTask()
{
    if(bShouldContinue) { TaskManagerRef->CheckParameters(); }
}

// Reassigns tank references in event that they were not assigned
void ATankAI::DoubleCheckTanks()
{
    ControlledTank = Cast<AEnemyTank>(GetPawn()); 
    PlayerTank = Cast<APlayerTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATankAI::HandleDestruction()
{
    UE_LOG(LogTemp, Warning, TEXT("%s: Handling destruction"), *GetName());

    bShouldContinue = false; 

    GetWorld()->GetTimerManager().ClearTimer(TaskTimer);

    SetActorTickEnabled(false);

    TaskManagerRef->DestroyTasks(); 
    TaskManagerRef = NULL;

    Destroy();
}
