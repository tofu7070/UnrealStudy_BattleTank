// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float DegreePerSecond) 
{
	UE_LOG(LogTemp, Warning, TEXT(" Barrel-Elevate() call %f"),DegreePerSecond);
	//Move The barrel the right amont this frame
	// Given a max elevation speed, and the frame time
}