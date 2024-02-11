// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Character/PMCharacter.h"
#include "Controllers/Character/Camera/PMCharacterCamera.h"


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
