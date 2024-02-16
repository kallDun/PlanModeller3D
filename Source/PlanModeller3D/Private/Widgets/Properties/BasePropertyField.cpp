// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Properties/BasePropertyField.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/RichTextBlock.h"
#include "Components/VerticalBox.h"


void UBasePropertyField::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ApplyButton->OnClicked.AddDynamic(this, &UBasePropertyField::OnApplyButtonClicked);
	RevertButton->OnClicked.AddDynamic(this, &UBasePropertyField::OnRevertButtonClicked);
}

void UBasePropertyField::BaseInit(const FText Name)
{
	Label->SetText(Name);
}

void UBasePropertyField::SetButtonsVisibility(const bool bVisible)
{
	ButtonsContainer->SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	ApplyButton->SetVisibility(ESlateVisibility::Visible);
	RevertButton->SetVisibility(ESlateVisibility::Visible);
}
