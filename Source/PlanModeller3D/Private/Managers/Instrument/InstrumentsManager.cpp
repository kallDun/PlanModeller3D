// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/Instrument/InstrumentsManager.h"
#include "Actors/Instrument/CharacterInstrument.h"
#include "Core/CoreFunctionLib.h"
#include "Managers/Character/CharactersManager.h"
#include "Managers/Instrument/InstrumentsManagerData.h"


void UInstrumentsManager::Init_Implementation(UPrimaryDataAsset* DataAsset)
{
	IInitializable::Init_Implementation(DataAsset);
	Data = Cast<UInstrumentsManagerData>(DataAsset);

	for (auto CharacterClass : Data->InstrumentClasses)
	{
		const auto Instrument = GetWorld()->SpawnActor<ACharacterInstrument>(CharacterClass);
		Instrument->Init(this);
		Instruments.Add(Instrument);
	}

	CharactersManager = UCoreFunctionLib::GetCharactersManager(this);
	CharactersManager->OnBeforeCharacterSelected.AddDynamic(this, &UInstrumentsManager::OnBeforeCharacterSelected);
}

ACharacterInstrument* UInstrumentsManager::ActivateInstrument(const FString& InstrumentName, const FInstrumentActivationFunction ActivateFunction)
{
	DeactivateCurrentInstrument();
	if (const auto Instrument = GetInstrument(InstrumentName))
	{
		auto Character = CharactersManager->GetCurrentCharacter();
		Instrument->Activate(Character);
		ActiveInstrument = Instrument;
		if (ActivateFunction.IsBound())
		{
			ActivateFunction.Execute(Instrument);
		}
		OnInstrumentActivated.Broadcast();
		return Instrument;
	}
	return nullptr;
}

void UInstrumentsManager::DeactivateCurrentInstrument()
{
	if (ActiveInstrument)
	{
		ActiveInstrument->Deactivate();
		ActiveInstrument = nullptr;
		OnInstrumentDeactivated.Broadcast();
	}
}

ACharacterInstrument* UInstrumentsManager::GetInstrument(const FString& InstrumentName)
{
	for (const auto Instrument : Instruments)
	{
		if (Instrument->InstrumentName == InstrumentName)
		{
			return Instrument;
		}		
	}
	return nullptr;
}

ACharacterInstrument* UInstrumentsManager::GetInstrumentByType(TSubclassOf<ACharacterInstrument> InstrumentType)
{
	for (const auto Item : Instruments)
	{
		if (Item->IsA(InstrumentType))
		{
			return Item;
		}
	}
	return nullptr;
}

FString UInstrumentsManager::GetInstrumentName(const TSubclassOf<ACharacterInstrument> InstrumentType)
{
	for (const auto Item : Instruments)
	{
		if (Item->IsA(InstrumentType))
		{
			return Item->InstrumentName;
		}
	}
	return "";
}

void UInstrumentsManager::OnBeforeCharacterSelected(APMCharacter* Character)
{
	DeactivateCurrentInstrument();
}
