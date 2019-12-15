// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_Character.h"

#include "Classes/Camera/CameraComponent.h"
#include"HandController.h"
#include "Components/InputComponent.h"


// Sets default values
AVR_Character::AVR_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AVR_Character::BeginPlay()
{
	Super::BeginPlay();

	LeftController = GetWorld()->SpawnActor<AHandController>(HandControllerClass);
	if (LeftController != nullptr)
	{
		LeftController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		LeftController->SetHand(EControllerHand::Left);
	}

	RightController = GetWorld()->SpawnActor<AHandController>(HandControllerClass);
	if (RightController != nullptr)
	{
		RightController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		RightController->SetHand(EControllerHand::Right);
	}

}

// Called every frame
void AVR_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 

}

// Called to bind functionality to input
void AVR_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("GrabR", IE_Pressed, this, &AVR_Character::ControllerGrabR);
	InputComponent->BindAction("GrabR", IE_Released, this, &AVR_Character::ControllerReleaseR);

	InputComponent->BindAction("GrabL", IE_Pressed, this, &AVR_Character::ControllerGrabL);
	InputComponent->BindAction("GrabL", IE_Released, this, &AVR_Character::ControllerReleaseL);
	 
	InputComponent->BindAxis("Forward", this, &AVR_Character::MoveForward);
	InputComponent->BindAxis("Right", this, &AVR_Character::MoveRight);

}

void AVR_Character::MoveForward(float throttle)
{
	AddMovementInput(Camera->GetForwardVector() * -throttle);
}


void AVR_Character::MoveRight(float throttle)
{
	AddMovementInput(Camera->GetRightVector() * throttle);
}

void AVR_Character::ControllerGrabR()
{
	RightController->Grab();
}

void AVR_Character::ControllerReleaseR()
{
	RightController->Release();
}

void AVR_Character::ControllerGrabL()
{
	LeftController->Grab();
}

void AVR_Character::ControllerReleaseL()
{
	LeftController->Release();
}
