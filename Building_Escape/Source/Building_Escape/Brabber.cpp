// Fill out your copyright notice in the Description page of Project Settings.

//It selects the reference
#define OUT 

#include "Brabber.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UBrabber::UBrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"));
	
}


// Called every frame
void UBrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get the player view point this tick
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerLocation, OUT PlayerRotation);

	//UE_LOG(LogTemp, Warning, TEXT("Location: %s,\nRotation: %s"), *PlayerLocation.ToString(), *PlayerRotation.ToString());
	FVector LineTranceEnd = PlayerLocation + PlayerRotation.Vector() * Reach;
	//Draw a red trance in the world to visualise
	DrawDebugLine(GetWorld(), PlayerLocation, LineTranceEnd, FColor::Red, false, 0.f, 0.f, 10.f);
	//Ray-cast out to reach distance
	//See what we hit
}

