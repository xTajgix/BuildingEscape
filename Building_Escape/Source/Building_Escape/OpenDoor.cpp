// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	Rotation = FRotator(GetOwner()->GetTransform().GetRotation());
}

void UOpenDoor::OpenDoor()
{
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *Rotation.ToString());
	Owner->SetActorRotation(FRotator(Rotation.Pitch, Rotation.Yaw - OpenAngle, Rotation.Roll));
}

void UOpenDoor::CloseDoor()
{
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *Rotation.ToString());
	Owner->SetActorRotation(Rotation);
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	if (GetTotalMassOfActorOnPlate() > 30.f)//TODO make into parameter
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	//Check if it's time to close the door
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}
	
}

float UOpenDoor::GetTotalMassOfActorOnPlate()
{
	float TotalMass = 0.f;

	//Find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (const auto* Actor: OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on Pressure Plate"), *Actor->GetName());
	}
	//Iterate through them addimg their masses

	return TotalMass;
}
