// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControllTank = GetControlledTank();
	if (!ControllTank) {
		UE_LOG(LogTemp, Warning, TEXT("Not Possesing a tank"));
	}else
	UE_LOG(LogTemp, Warning, TEXT("Player Controller Begin Play %s"), *(ControllTank->GetName()));
}
