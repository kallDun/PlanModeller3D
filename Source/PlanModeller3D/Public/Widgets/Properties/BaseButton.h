// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/UI/PanelUI.h"
#include "BaseButton.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnBaseButtonClicked, int, Index);

UCLASS(Abstract, BlueprintType, Blueprintable)
class PLANMODELLER3D_API UBaseButton : public UPanelUI
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	int Index;

	UPROPERTY()
	FOnBaseButtonClicked OnButtonClicked;
	
public:
	UFUNCTION(BlueprintCallable)
	void AssignClick(FOnBaseButtonClicked ButtonClicked, int InIndex);
	
	UFUNCTION(BlueprintCallable)
	void Click();

	virtual void ReturnToPool_Implementation(UPoolService* Pool) override;
};
