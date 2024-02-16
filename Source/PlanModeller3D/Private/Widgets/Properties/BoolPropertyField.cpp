// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Properties/BoolPropertyField.h"
#include "Components/CheckBox.h"
#include "Widgets/Properties/BoolPropertyConstructObject.h"


void UBoolPropertyField::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	InputField->OnCheckStateChanged.AddDynamic(this, &UBoolPropertyField::OnInputFieldChanged);
}


void UBoolPropertyField::Init(const FBoolPropertyConstructObject InConstructObject)
{
	BaseInit(InConstructObject.Name);
	GetValueDelegate = InConstructObject.GetValue;
	SetValueDelegate = InConstructObject.SetValue;
	OnRevertButtonClicked();
}

void UBoolPropertyField::OnInputFieldChanged(const bool bIsChecked)
{
	if (GetValueDelegate.Execute() != bIsChecked)
	{
		SetButtonsVisibility(true);
	}
	else
	{
		SetButtonsVisibility(false);
	}
}

void UBoolPropertyField::OnApplyButtonClicked()
{
	Super::OnApplyButtonClicked();
	SetValueDelegate.Execute(InputField->GetCheckedState() == ECheckBoxState::Checked);
	SetButtonsVisibility(false);
}

void UBoolPropertyField::OnRevertButtonClicked()
{
	Super::OnRevertButtonClicked();
	InputField->SetCheckedState(GetValueDelegate.Execute() ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
	SetButtonsVisibility(false);
}
