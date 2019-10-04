// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurrel;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable, Category = Setup)//This can be used in Blueprint
		void SetBarrelReference(UTankBarrel* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)//This can be used in Blueprint
		void SetTurretReference(UTankTurrel* TurretToSet);
	UFUNCTION(BlueprintCallable, Category = Fireing)//This can be used in Blueprint
		void Fire();
protected:
	UTankAimingComponent* TankAimingcomponent = nullptr;
	UPROPERTY(BlueprintReadOnly)//shoudl drag this component to the bluepint 
	UTankMovementComponent* TankMovementcomponent = nullptr;
private:	
	ATank();
	virtual void BeginPlay() override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 100000.0;//1000 m/s
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;
	//Local barrel reference for spawnimg projectile
	UTankBarrel* Barrel = nullptr;
	float ReloadTimeInSeconds = 3.0f;
	double LastFireTime = 0;
};
