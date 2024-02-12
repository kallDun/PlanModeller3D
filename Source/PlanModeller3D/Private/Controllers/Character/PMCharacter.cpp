// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Character/PMCharacter.h"
#include "Camera/CameraComponent.h"
#include "Controllers/Character/Camera/PMCharacterCamera.h"


APMCharacter::APMCharacter()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
}

UPMCharacterCamera* APMCharacter::GetCurrentCamera() const
{
	for (const auto Camera : Cameras)
	{
		if (Camera->bIsCurrentCamera)
		{
			return Camera;
		}
	}
	return nullptr;
}

void APMCharacter::ResetSettingsToDefault_Implementation()
{
	
}
