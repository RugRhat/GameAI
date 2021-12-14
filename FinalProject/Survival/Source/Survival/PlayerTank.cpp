// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

APlayerTank::APlayerTank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->TargetArmLength = 500.f;
    SpringArm->SocketOffset = FVector(0.f, 0.f, 300.f);
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));
    Camera->SetupAttachment(SpringArm);
}

void APlayerTank::BeginPlay()
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(HealthRegenTimerHandle, this, &APlayerTank::RegenHealth, HealthRegenRate, true, false);
}

void APlayerTank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APlayerTank::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("Move", this, &APlayerTank::Move);
    PlayerInputComponent->BindAxis("Rotate", this, &APlayerTank::Rotate);

    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerTank::Fire);
}

void APlayerTank::Move(float AxisValue)
{
    AddMovementInput(GetActorForwardVector() * AxisValue);
}

void APlayerTank::Rotate(float AxisValue)
{
    AddControllerYawInput(AxisValue * RotateSpeed * GetWorld()->GetDeltaSeconds());
}

// void APlayerTank::HandleDestruction()
// {
//     Super::HandleDestruction();

//     bAlive = false;

//     SetActorHiddenInGame(true);
//     SetActorTickEnabled(false);
// }