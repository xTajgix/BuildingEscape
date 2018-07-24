// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Components/ActorComponent.h"

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
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

}

void UOpenDoor::OpenDoor()
{
	AActor * Owner = GetOwner();
	FQuat Rotation = Owner->GetTransform().GetRotation();
	//UE_LOG(LogTemp, Warning, TEXT("Rotation1 of door is %s"), *Rotation.ToString());
	Rotation.Z = Rotation.Z - 60;
	//UE_LOG(LogTemp, Warning, TEXT("Rotation2 of door is %s"), *Rotation.ToString());
	Owner->SetActorRotation(Rotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))//If ActorThatOpens is in the volume
	{
		OpenDoor();
	}
	
	
}

