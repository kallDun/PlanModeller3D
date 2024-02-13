// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Character/PMCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "Controllers/Character/CharactersManager.h"
#include "Widgets/Properties/PropertiesConstructData.h"


void APMCharacter::Init(UCharactersManager* InManager)
{
	Manager = InManager;
}

void APMCharacter::SelectAsCurrent_Implementation()
{
	if (const auto CurrentCamera = Manager->GetCurrentCharacter())
	{
		CurrentCamera->OnDeselect();
	}
	bIsCurrentCharacter = true;
	OnUpdateProperties();

	Manager->PlayerController->Possess(this);
	if (Manager->PlayerController)
	{
		// Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Manager->PlayerController->GetLocalPlayer()))
		{
			// PawnClientRestart can run more than once in an Actor's lifetime, so start by clearing out any leftover mappings.
			Subsystem->ClearAllMappings();

			// Add each mapping context, along with their priority values. Higher values out-prioritize lower values.
			Subsystem->AddMappingContext(PlayerInputMappingContext, 0);
		}
	}
}

void APMCharacter::OnDeselect_Implementation()
{
	bIsCurrentCharacter = false;
}

UPropertiesConstructData* APMCharacter::GetProperties_Implementation()
{
	return NewObject<UPropertiesConstructData>();
}

void APMCharacter::OnUpdateProperties_Implementation() { }
