// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

class UTankBarrel;
class UTankTurrel;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Called every frame
	UFUNCTION(BlueprintCallable, Category = Setup)
		void Initialise(UTankBarrel* BarrelToSet, UTankTurrel* TurretToSet);
	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable, Category = Fireing)//This can be used in Blueprint
		void Fire();
protected:
	// Called when the game starts
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Reloading;
private:
	UTankAimingComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool IsBarrelMoving();
	void MoveBarrelTowards(FVector AimDirection);
	UTankBarrel* Barrel = nullptr;
	UTankTurrel* Turret = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 4000.0;//40 m/s
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;
	//Local barrel reference for spawnimg projectile
	float ReloadTimeInSeconds = 3.0f;
	double LastFireTime = 0;
	FVector AimDirection;
};
