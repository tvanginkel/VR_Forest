// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VR_Character.generated.h"

class UCameraComponent;

UCLASS()
class VR_FOREST_API AVR_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVR_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UCameraComponent * Camera;

	void MoveForward(float throttle);
	void MoveBackward(float throttle);
	void MoveRight(float throttle);
	void MoveLeft(float throttle);
	
};
