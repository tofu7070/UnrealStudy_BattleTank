// Copyright EmbraceIT Ltd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "SprongWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprongWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprongWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	void SetupConstraint();
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* Wheel = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* MassWheelConstraint = nullptr;
};
