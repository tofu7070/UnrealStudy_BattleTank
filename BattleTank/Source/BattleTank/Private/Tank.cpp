// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"
#include "Tank.h"

float ATank::GetHealthcPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}

// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}
float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	UE_LOG(LogTemp, Warning, TEXT("DamageAmount is : %f   DamageToApply is : %i"), DamageAmount, DamageToApply);
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("TankDied"));
		OnDeath.Broadcast();
	}
	return DamageToApply;
}