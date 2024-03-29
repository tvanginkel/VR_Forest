// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "HandController.generated.h"

class UMotionControllerComponent;
class UPhysicsHandleComponent;

UCLASS()
class VR_FOREST_API AHandController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHandController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Ray-cast and grab
	void Grab();

	//Called when grab is released
	void Release();

	void SetHand(EControllerHand hand);

private:

	UMotionControllerComponent* Controller = nullptr;
	
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;

	float Reach = 150.0f;
};
