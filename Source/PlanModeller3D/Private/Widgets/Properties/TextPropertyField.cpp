// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Properties/TextPropertyField.h"
#include "Components/EditableTextBox.h"


void UTextPropertyField::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	InputField->OnTextChanged.AddDynamic(this, &UTextPropertyField::OnInputFieldTextChanged);
}


void UTextPropertyField::Init(const FTextPropertyConstructObject InConstructObject)
{
	BaseInit(InConstructObject.Name);
	InputField->SetIsReadOnly(InConstructObject.bIsReadOnly);
	GetValueDelegate = InConstructObject.GetValue;
	SetValueDelegate = InConstructObject.SetValue;
	OnRevertButtonClicked();
}

void UTextPropertyField::OnInputFieldTextChanged(const FText& Text)
{
	if (GetValueDelegate.Execute() != Text.ToString())
	{
		SetButtonsVisibility(true);
	}
	else
	{
		SetButtonsVisibility(false);
	}
}

void UTextPropertyField::OnApplyButtonClicked()
{
	Super::OnApplyButtonClicked();
	SetValueDelegate.Execute(InputField->GetText().ToString());
	SetButtonsVisibility(false);
}

void UTextPropertyField::OnRevertButtonClicked()
{
	Super::OnRevertButtonClicked();
	InputField->SetText(FText::FromString(GetValueDelegate.Execute()));
	SetButtonsVisibility(false);
}
