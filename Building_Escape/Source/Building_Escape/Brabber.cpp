// Fill out your copyright notice in the Description page of Project Settings.

//It selects the reference
#define OUT 

#include "Brabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UBrabber::UBrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UBrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
}

///Look for attached Physics Handle
void UBrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("Physics Handle of %s is found"), *GetOwner()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Physics Handle of %s isn't found"), *GetOwner()->GetName());
	}
}

///Look for attached Input Component (only appears at run time)
void UBrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		///UE_LOG(LogTemp, Warning, TEXT("Input Component of %s is found"), *GetOwner()->GetName());

		/// Bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UBrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UBrabber::Released);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input Component of %s isn't found"), *GetOwner()->GetName());
	}
}
void UBrabber::Grab() 
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
	//Line trace and see if we reach any actors with physics body collision channel set
	GetFirstPhysicsBodyInReach();

	///If we hit something then attach a physics handle
	//TODO attach physics handle
}

FHitResult UBrabber::GetFirstPhysicsBodyInReach()
{
	/// Get the player view point this tick
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerLocation, OUT PlayerRotation);

	///UE_LOG(LogTemp, Warning, TEXT("Location: %s,\nRotation: %s"), *PlayerLocation.ToString(), *PlayerRotation.ToString());
	FVector LineTranceEnd = PlayerLocation + PlayerRotation.Vector() * Reach;

	///Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());


	///Line-trace (AKA ray-cast) out to reach distance
	FHitResult LineTraceHit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT LineTraceHit,
		PlayerLocation,
		LineTranceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	AActor * HitActor = LineTraceHit.GetActor();
	if (HitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace hits %s"), *HitActor->GetName());
	}

	return LineTraceHit;
}

void UBrabber::Released()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released"));
	// TODO release physics handle
}


// Called every frame
void UBrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if the physics handle is attached
		//move the object that we're holding
}



