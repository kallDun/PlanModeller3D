// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Character/PMCharacter.h"
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
	Manager->PlayerController->Possess(this);
}

void APMCharacter::OnDeselect_Implementation()
{
	bIsCurrentCharacter = false;
}

UPropertiesConstructData* APMCharacter::GetProperties_Implementation()
{
	return NewObject<UPropertiesConstructData>();
}
