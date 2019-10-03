// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurrel.h"
#include "GameFramework/Actor.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurrel* TurretToSet)
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.,
		0.,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution) // cacluate the out launch velocity
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("%s: Aimdirection"), *AimDirection.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("%s: OutHitvelocity"), *OutLaunchVelocity.ToString());
		MoveBarrelTowards(OutLaunchVelocity);
	}
	else {
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No aim solve found"), Time);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//Work out difference between barrel location and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	//UE_LOG(LogTemp, Warning, TEXT("BarrelRotator........%f:"), BarrelRotator.Yaw);
	auto AimAsRotatior = AimDirection.Rotation();
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotatoior........%f:"), AimAsRotatior.Yaw);
	auto DeltaRotator = AimAsRotatior - BarrelRotator;
	Turret->Rotate(DeltaRotator.Yaw);
	Barrel->Elevate(DeltaRotator.Pitch);
}

