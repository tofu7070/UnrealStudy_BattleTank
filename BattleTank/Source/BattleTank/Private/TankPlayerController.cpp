// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
//Tick
// Super

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTOwardsCrosshair();
	UE_LOG(LogTemp, Warning, TEXT("Player controller Ticking"));
}

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
void ATankPlayerController::AimTOwardsCrosshair() {
	if (!GetControlledTank()) {
		return;
	}
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("Hot Location: %s"), *HitLocation.ToString());
		// Tell controlled tank to aim at his point
	}

}
//Get world location if linetrace through crosshair, If it hit the lindscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& outhitlocation) const{
	outhitlocation = FVector(1.0);
	return true;
}