// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Properties/BaseButton.h"

void UBaseButton::AssignClick(const FOnBaseButtonClicked ButtonClicked, const int InIndex)
{
	OnButtonClicked = ButtonClicked;
	Index = InIndex;
}

void UBaseButton::SetupAsRadioButton(const TArray<UBaseButton*> InRelatedRadioButtons)
{
	RelatedRadioButtons = InRelatedRadioButtons;
	bIsRadioButton = true;
	bIsSelected = false;
	UpdateView();
}

void UBaseButton::SetRadioButtonSelected()
{
	if (bIsRadioButton)
	{
		for (const auto Button : RelatedRadioButtons)
		{
			if (Button == this) continue;
			Button->bIsSelected = false;
			Button->UpdateView();
		}
		bIsSelected = true;
		UpdateView();
	}
}

void UBaseButton::Click_Implementation()
{
	OnButtonClicked.ExecuteIfBound(Index);
	SetRadioButtonSelected();
}

void UBaseButton::UpdateView_Implementation()
{
}

void UBaseButton::ReturnToPool_Implementation(UPoolService* Pool)
{
	UpdateView();
	Super::ReturnToPool_Implementation(Pool);
	OnButtonClicked.Unbind();
	RelatedRadioButtons = {};
	bIsRadioButton = false;
	bIsSelected = false;
}
