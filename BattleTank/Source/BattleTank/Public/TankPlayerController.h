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
};
