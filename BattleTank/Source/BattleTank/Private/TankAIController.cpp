// Fill out your copyright notice in the Description page of Project Settings.
#include "Tank.h"
#include "Engine/World.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	/*auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("Not Possesing AI a tank"));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("AI Controller found playe tank %s"), *(PlayerTank->GetName()));*/

}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlTank = Cast<ATank>(GetPawn());
	if (PlayerTank) {
		//AIm towards the player
		ControlTank->AimAt(PlayerTank->GetActorLocation());
		ControlTank->Fire();
	}
}
