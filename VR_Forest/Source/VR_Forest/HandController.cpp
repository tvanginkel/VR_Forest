// Fill out your copyright notice in the Description page of Project Settings.

#include "HandController.h"
#include "MotionControllerComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values
AHandController::AHandController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Controller = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
	SetRootComponent(Controller);

}

// Called when the game starts or when spawned
void AHandController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Start = Controller->GetComponentLocation();
	FVector End = ((Controller->GetComponentRotation().Vector() * 200.f) + Start);
	//FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams::AddIgnoredActor();
	
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);


	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility))
	{
		UE_LOG(LogTemp, Warning, TEXT("I grabbed: %s"), *OutHit.GetActor()->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Hit"))
	}
}

void AHandController::SetHand(EControllerHand hand)
{
	Controller->Hand = hand;
}