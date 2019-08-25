// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_Character.h"

#include "Classes/Camera/CameraComponent.h"
#include"HandController.h"


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

	LeftController = GetWorld()->SpawnActor<AHandController>();
	if (LeftController != nullptr)
	{
		LeftController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}

	RightController = GetWorld()->SpawnActor<AHandController>();
	if (RightController != nullptr)
	{
		RightController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
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
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AVR_Character::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Back"), this, &AVR_Character::MoveBackward);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &AVR_Character::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Left"), this, &AVR_Character::MoveLeft);

}

void AVR_Character::MoveForward(float throttle)
{
	AddMovementInput(Camera->GetForwardVector() * throttle);
}

void AVR_Character::MoveBackward(float throttle)
{
	AddMovementInput(Camera->GetForwardVector() * -throttle);
}

void AVR_Character::MoveRight(float throttle)
{
	AddMovementInput(Camera->GetRightVector() * throttle);
}

void AVR_Character::MoveLeft(float throttle)
{
	AddMovementInput(Camera->GetRightVector() * -throttle);
}