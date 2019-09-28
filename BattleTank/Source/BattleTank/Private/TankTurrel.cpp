// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurrel.h"

void UTankTurrel::Rotate(float RelativeSpeed)
{
	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f: Barrel-Elevate() call %f"), Time, RelativeSpeed);
	//Move The barrel the right amont this frame
	// Given a max elevation speed, and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, Rotation, 0));
}