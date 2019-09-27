// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("Not Possesing AI a tank"));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("AI Controller found playe tank %s"), *(PlayerTank->GetName()));
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) {
		return nullptr;
	}
	return Cast<ATank>(PlayerPawn);
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);
	if (GetPlayerTank()) {
		//AIm towards the player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}
