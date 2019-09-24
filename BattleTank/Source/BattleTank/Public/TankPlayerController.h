// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"//must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ATank* GetControlledTank() const;
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	//Start the tank moving thebarrel so that a shot would hit where
	// the crosshair intersects the world
	void AimTOwardsCrosshair();

private:
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5f;
	
	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.33f;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.f;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector lookDirection, FVector& HitLocation) const;

};
