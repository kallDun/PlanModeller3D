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
	UPROPERTY(BlueprintReadOnly)
	int Index;

	UPROPERTY()
	FOnBaseButtonClicked OnButtonClicked;

	UPROPERTY()
	bool bIsRadioButton;
	
	UPROPERTY()
	bool bChangeSelectionOnClick = true;
	
	UPROPERTY()
	TArray<UBaseButton*> RelatedRadioButtons = {};
	
public:
	UPROPERTY(BlueprintReadOnly)
	bool bIsSelected;
	
	UFUNCTION(BlueprintCallable)
	void AssignClick(FOnBaseButtonClicked ButtonClicked, int InIndex);

	UFUNCTION(BlueprintCallable)
	void SetupAsRadioButton(TArray<UBaseButton*> InRelatedRadioButtons, bool ChangeSelectionOnClick = true);

	UFUNCTION(BlueprintCallable)
	void SetRadioButtonSelected();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Click();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateView();

	virtual void ReturnToPool_Implementation(UPoolService* Pool) override;
};
