// Fill out your copyright notice in the Description page of Project Settings.
#include "Engine/World.h"
#include "TankAimingComponent.h"
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


void ATankAIController::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlTank = GetPawn();
	if (!ensure(PlayerTank) && ControlTank) {}
	//move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);
	auto AimingComponent = ControlTank-> FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	AimingComponent->Fire();	
}
