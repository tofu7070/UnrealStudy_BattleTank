// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankPlayerController.h"
//Tick
// Super

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTOwardsCrosshair();
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
		GetControlledTank()->AimAt(HitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
		// Tell controlled tank to aim at his point
	}

}
//Get world location if linetrace through crosshair, If it hit the lindscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& outhitlocation) const{
	//Find the crosshaire postion
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("ScreeenLocation: %s"), *ScreenLocation.ToString());
	//De-Project the screen position of the crosshaire to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		//line-trane along that look direction and see what we hit (Up to max range)

		//UE_LOG(LogTemp, Warning, TEXT("Look Direction %s"), *LookDirection.ToString());
		//Get look Vector hHit Location
		GetLookVectorHitLocation(LookDirection,outhitlocation);
	}
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;// Tobe declaired
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult,StartLocation,EndLocation,ECollisionChannel::ECC_Visibility)) //line trace successed
	{
		HitLocation = HitResult.Location;
		return true;
	}
	return false;
}
