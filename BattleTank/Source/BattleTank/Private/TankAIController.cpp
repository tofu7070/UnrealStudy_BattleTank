// Fill out your copyright notice in the Description page of Project Settings.
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"
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

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if(InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
	}
}


void ATankAIController::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlTank = GetPawn();
	if (!ensure(PlayerTank) && ControlTank) { return; }
	//move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);
	auto AimingComponent = ControlTank-> FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	if(AimingComponent->GetFireingState() == EFiringState::Locked)
	AimingComponent->Fire();	
}

void ATankAIController::OnPossedTankDeath()
{
	//UE_LOG(LogTemp, Warning, TEXT("Tank Death"));
	if (!ensure(GetPawn())) {return;}
	GetPawn()->DetachFromControllerPendingDestroy();
}
