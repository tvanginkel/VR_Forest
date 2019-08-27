// Fill out your copyright notice in the Description page of Project Settings.

#include "HandController.h"
#include "MotionControllerComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

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
	
	PhysicsHandle = FindComponentByClass<UPhysicsHandleComponent>();
	
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Physics Handle missing"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Physics Handle found"))
	}
}

// Called every frame
void AHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PhysicsHandle->GrabbedComponent)
	{
		FVector Start = Controller->GetComponentLocation();
		FVector End = ((Controller->GetComponentRotation().Vector() * Reach) + Start);
		PhysicsHandle->SetTargetLocation(End);
	}

}

bool AHandController::GetFirstObjectInReach()
{
	/*FVector Start = Controller->GetComponentLocation();
	FVector End = ((Controller->GetComponentRotation().Vector() * 200.f) + Start);

	FHitResult OutHit;

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, TraceParameters))
	{
		UE_LOG(LogTemp, Warning, TEXT("Object in reach: %s"), *OutHit.GetActor()->GetName())
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);
	}

	return OutHit;*/
	return true;
}

void AHandController::SetHand(EControllerHand hand)
{
	Controller->Hand = hand;
}

void AHandController::Grab()
{
	FVector Start = Controller->GetComponentLocation();
	FVector End = ((Controller->GetComponentRotation().Vector() * Reach) + Start);

	FHitResult OutHit;

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, TraceParameters))
	{
		UE_LOG(LogTemp, Warning, TEXT("Object in reach: %s"), *OutHit.GetActor()->GetName())
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

		UPrimitiveComponent* ComponentToGrab = OutHit.GetComponent();
		AActor* ActorHit = OutHit.GetActor();

		if (ComponentToGrab->GetOwner())
		{
			if (ActorHit)
			{
				///If we hit something then attach a physics handle
				PhysicsHandle->GrabComponent(
					ComponentToGrab,
					NAME_None,
					ComponentToGrab->GetOwner()->GetActorLocation(),
					true);
			}
		}
	}
}

void AHandController::Release()
{
	PhysicsHandle->ReleaseComponent();
}
