// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Properties/SceneObjectPropertyField.h"
#include "Components/Button.h"
#include "Components/RichTextBlock.h"
#include "Controllers/Instrument/InstrumentsManager.h"
#include "Controllers/Instrument/Selection/SelectionCharacterInstrument.h"
#include "Core/CoreFunctionLib.h"


void USceneObjectPropertyField::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ChangeSceneObjectButton->OnClicked.AddDynamic(this, &USceneObjectPropertyField::OnChangeSceneObjectButtonClicked);
}

void USceneObjectPropertyField::Init(const FSceneObjectPropertyConstructObject InConstructObject)
{
	InstrumentsManager = UCoreFunctionLib::GetInstrumentsManager(this);
	BaseInit(InConstructObject.Name);
	CurrentConstructObject = InConstructObject;
	bIsInstrumentActive = false;
	GetValueDelegate = InConstructObject.GetValue;
	SetValueDelegate = InConstructObject.SetValue;
	OnRevertButtonClicked();
}

void USceneObjectPropertyField::OnChangeSceneObjectButtonClicked()
{
	if (bIsInstrumentActive)
	{
		InstrumentsManager->DeactivateCurrentInstrument();
		return;
	}
	const FString SelectInstrumentName = InstrumentsManager->GetInstrumentName(ASelectionCharacterInstrument::StaticClass());
	const auto Instrument = InstrumentsManager->ActivateInstrument(SelectInstrumentName);
	if (const auto SelectionInstrument = Cast<ASelectionCharacterInstrument>(Instrument))
	{
		SelectionInstrument->AvailableSelections = CurrentConstructObject.AvailableSelections;
		SelectionInstrument->InstrumentType = EInstrumentType::UI;
	}
	Instrument->OnInstrumentUsed.AddDynamic(InstrumentsManager, &UInstrumentsManager::DeactivateCurrentInstrument);
	Instrument->OnInstrumentDeactivated.AddDynamic(this, &USceneObjectPropertyField::OnInstrumentDeactivated);
	bIsInstrumentActive = true;
}

void USceneObjectPropertyField::OnInstrumentDeactivated()
{
	bIsInstrumentActive = false;
	if (const auto SelectionInstrument = Cast<ASelectionCharacterInstrument>(InstrumentsManager->ActiveInstrument))
	{
		UpdateCurrentValue(SelectionInstrument->SelectedSceneObject);
		if (GetValueDelegate.Execute() != CurrentValue)
		{
			SetButtonsVisibility(true);
		}
		else
		{
			SetButtonsVisibility(false);
		}
	}
}

void USceneObjectPropertyField::OnApplyButtonClicked()
{
	Super::OnApplyButtonClicked();
	SetValueDelegate.Execute(CurrentValue);
	SetButtonsVisibility(false);
	UpdateCurrentValue(GetValueDelegate.Execute());
}

void USceneObjectPropertyField::OnRevertButtonClicked()
{
	Super::OnRevertButtonClicked();
	UpdateCurrentValue(GetValueDelegate.Execute());
	SetButtonsVisibility(false);
}

void USceneObjectPropertyField::UpdateCurrentValue_Implementation(const FSceneObjectSelection& InSceneObject)
{
	CurrentValue = InSceneObject;
	SceneObjectName->SetText(FText::FromString(InSceneObject.SelectionName));
}
