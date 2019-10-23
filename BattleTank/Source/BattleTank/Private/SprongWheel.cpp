// Copyright EmbraceIT Ltd.

#include "Components/StaticMeshComponent.h"
#include "SprongWheel.h"

// Sets default values
ASprongWheel::ASprongWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
	SetRootComponent(MassWheelConstraint);
	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(MassWheelConstraint);
}

// Called when the game starts or when spawned
void ASprongWheel::BeginPlay()
{
	Super::BeginPlay();
	SetupConstraint();
}

// Called every frame
void ASprongWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASprongWheel::SetupConstraint()
{
	if (!GetAttachParentActor())
	{
		UE_LOG(LogTemp, Warning, TEXT(" Null"));
		return;
	}
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }
	MassWheelConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Wheel, NAME_None);
}

