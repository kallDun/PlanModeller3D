// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Instrument/CharacterInstrument.h"


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

void ACharacterInstrument::Preview_Implementation()
{
}

void ACharacterInstrument::Use_Implementation()
{
	OnInstrumentUsed.Broadcast();
}