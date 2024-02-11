// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Character/Camera/PMCharacterCamera.h"
#include "Controllers/Character/PMCharacter.h"


void UPMCharacterCamera::Init(APMCharacter* InCharacter)
{
	Character = InCharacter;
	Character->Cameras.Add(this);
	if (bIsDefaultCamera)
	{
		SelectCameraAsCurrent();
	}
}

void UPMCharacterCamera::SelectCameraAsCurrent_Implementation()
{
	if (const auto CurrentCamera = Character->GetCurrentCamera())
	{
		CurrentCamera->OnDeselectCamera();
	}
	bIsCurrentCamera = true;
	Character->ResetSettingsToDefault();
}

void UPMCharacterCamera::OnDeselectCamera_Implementation()
{
	bIsCurrentCamera = false;
}
