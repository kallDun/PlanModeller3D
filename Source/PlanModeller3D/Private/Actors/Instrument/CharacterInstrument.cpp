// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Instrument/CharacterInstrument.h"
#include "Actors/Character/PMCharacter.h"
#include "Managers/Instrument/InstrumentsManager.h"
#include "Models/Instrument/InstrumentInputData.h"


void ACharacterInstrument::Init(UInstrumentsManager* InstrumentsManager)
{
	Manager = InstrumentsManager;
}

void ACharacterInstrument::Activate(APMCharacter* InCharacter)
{
	Character = InCharacter;
	Character->AddInstrument(this);
	OnActivated();
}

void ACharacterInstrument::Deactivate()
{
	OnInstrumentUsed.Clear();
	OnInstrumentDeactivated.Broadcast();
	OnInstrumentDeactivated.Clear();
	if (Character->ActiveInstrument == this)
	{
		Character->RemoveActiveInstrument();
	}
	OnDeactivated();
	Character = nullptr;
}

void ACharacterInstrument::Input_Implementation(FInstrumentInputData InputData)
{
	if (Contains(static_cast<EInstrumentInputType>(InputTypes), EInstrumentInputType::TriggerExitInput)
		&& InputData.ExitInput)
	{
		Manager->DeactivateCurrentInstrument();
	}
}
