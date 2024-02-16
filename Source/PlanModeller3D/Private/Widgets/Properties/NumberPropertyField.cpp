// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Properties/NumberPropertyField.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Misc/DefaultValueHelper.h"


void UNumberPropertyField::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	InputField->OnTextChanged.AddDynamic(this, &UNumberPropertyField::OnInputFieldChanged);
	InputSlider->OnValueChanged.AddDynamic(this, &UNumberPropertyField::OnInputSliderChanged);
}


void UNumberPropertyField::Init(const FNumberPropertyConstructObject InConstructObject)
{
	BaseInit(InConstructObject.Name);
	InputField->SetIsReadOnly(InConstructObject.bIsReadOnly);
	InputSlider->SetLocked(InConstructObject.bIsReadOnly);
	GetValueDelegate = InConstructObject.GetValue;
	SetValueDelegate = InConstructObject.SetValue;
	NumberType = InConstructObject.NumberType;

	if (InConstructObject.bIsClamped)
	{
		InputField->SetVisibility(ESlateVisibility::Collapsed);
		InputSlider->SetVisibility(ESlateVisibility::Visible);
		SliderValueText->SetVisibility(ESlateVisibility::Visible);
		InputSlider->SetMinValue(InConstructObject.MinValue);
		InputSlider->SetMaxValue(InConstructObject.MaxValue);
	}
	else
	{
		InputField->SetVisibility(ESlateVisibility::Visible);
		InputSlider->SetVisibility(ESlateVisibility::Collapsed);
		SliderValueText->SetVisibility(ESlateVisibility::Collapsed);
	}
	OnRevertButtonClicked();
}

void UNumberPropertyField::OnApplyButtonClicked()
{
	Super::OnApplyButtonClicked();
	SetValueDelegate.Execute(GetNumberValue());
	InputField->SetText(FText::FromString(std::to_string(GetValueDelegate.Execute()).c_str()));
	SetButtonsVisibility(false);
}

void UNumberPropertyField::OnRevertButtonClicked()
{
	Super::OnRevertButtonClicked();
	InputField->SetText(FText::FromString(std::to_string(GetValueDelegate.Execute()).c_str()));
	InputSlider->SetValue(GetValueDelegate.Execute());
	SliderValueText->SetText(FText::FromString(std::to_string(GetValueDelegate.Execute()).c_str()));
	SetButtonsVisibility(false);
}

bool UNumberPropertyField::IsNumberValid() const
{
	if (bIsSliderEnabled) return true;
	double RetVal;
	return FDefaultValueHelper::ParseDouble(InputField->GetText().ToString(), RetVal);
}

double UNumberPropertyField::GetNumberValue() const
{
	if (bIsSliderEnabled) return InputSlider->GetValue();
	double RetVal; 
	FDefaultValueHelper::ParseDouble(InputField->GetText().ToString(), RetVal);
	switch (NumberType)
	{
		case ENumberType::NT_Integer:
			return FMath::RoundToInt(RetVal);
		
		case ENumberType::NT_Float:
			return FMath::RoundToFloat(RetVal);
		
		case ENumberType::NT_Double:
			return RetVal;
	}
	return RetVal;
}

void UNumberPropertyField::OnInputFieldChanged(const FText& Text)
{
	if (std::to_string(GetValueDelegate.Execute()).c_str() != Text.ToString())
	{
		SetButtonsVisibility(true);
		ApplyButton->SetVisibility(IsNumberValid() ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
	else
	{
		SetButtonsVisibility(false);
	}
}

void UNumberPropertyField::OnInputSliderChanged(float Value)
{
	if (GetValueDelegate.Execute() != Value)
	{
		SetButtonsVisibility(true);
	}
	else
	{
		SetButtonsVisibility(false);
	}
	SliderValueText->SetText(FText::FromString(std::to_string(Value).c_str()));
}
