// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VR_Character.generated.h"

class UCameraComponent;
class AHandController;

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

	//Calls controller grab R
	void ControllerGrabR(); 

	//Calls controller release R
	void ControllerReleaseR();

	//Calls controller grab L
	void ControllerGrabL();

	//Calls controller release L
	void ControllerReleaseL();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY(EditAnywhere)
	UCameraComponent * Camera;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandController>HandControllerClass;

	AHandController* LeftController;
	AHandController* RightController;

	void MoveForward(float throttle);
	void MoveRight(float throttle);
	
};
