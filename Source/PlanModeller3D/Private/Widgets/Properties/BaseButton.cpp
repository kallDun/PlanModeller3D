// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Properties/BaseButton.h"

void UBaseButton::AssignClick(const FOnBaseButtonClicked ButtonClicked, const int InIndex)
{
	OnButtonClicked = ButtonClicked;
	Index = InIndex;
}

void UBaseButton::Click()
{
	OnButtonClicked.ExecuteIfBound(Index);
}

void UBaseButton::ReturnToPool_Implementation(UPoolService* Pool)
{
	Super::ReturnToPool_Implementation(Pool);
	OnButtonClicked.Unbind();
}
