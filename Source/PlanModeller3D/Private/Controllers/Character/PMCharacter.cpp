// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Character/PMCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "Controllers/Character/CharactersManager.h"
#include "Core/CoreFunctionLib.h"
#include "Widgets/Properties/PropertiesConstructData.h"


void APMCharacter::Init(UCharactersManager* InManager)
{
	Manager = InManager;
	SavingService = UCoreFunctionLib::GetSavingService(this);
}

void APMCharacter::SelectAsCurrent_Implementation()
{
	if (const auto CurrentCamera = Manager->GetCurrentCharacter())
	{
		CurrentCamera->OnDeselect();
	}

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

	bIsCurrentCharacter = true;
	if (bResetLocationAndRotation || !bWasPlayedBefore)
	{
		ResetStartLocationAndRotation();
		bWasPlayedBefore = true;
	}
	SetActorLocation(SavedLocation);
	SetActorRotation(SavedRotation);
	OnUpdateProperties();
}

void APMCharacter::OnDeselect_Implementation()
{
	bIsCurrentCharacter = false;
	SavedLocation = GetActorLocation();
	SavedRotation = GetActorRotation();
	SetActorLocation(FVector(0.0f, 0.0f, -1000.0f));
}

UPropertiesConstructData* APMCharacter::GetProperties_Implementation()
{
	UPropertiesConstructData* const Data = NewObject<UPropertiesConstructData>();

	FOnGetBoolValue GetResetLocationAndRotation = FOnGetBoolValue();
	GetResetLocationAndRotation.BindDynamic(this, &APMCharacter::GetResetLocationAndRotation);
	FOnSetBoolValue SetResetLocationAndRotation = FOnSetBoolValue();
	SetResetLocationAndRotation.BindDynamic(this, &APMCharacter::SetResetLocationAndRotation);
	Data->BoolProperties.Add(FBoolPropertyConstructObject(
		-1, FText::FromString("Reset Location On Setup"), false, GetResetLocationAndRotation, SetResetLocationAndRotation));

	return Data;
}

void APMCharacter::ResetStartLocationAndRotation_Implementation() { }

void APMCharacter::OnUpdateProperties_Implementation() { }
