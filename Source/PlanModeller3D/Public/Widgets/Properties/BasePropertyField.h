// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/UI/PanelUI.h"
#include "BasePropertyField.generated.h"


UCLASS(Abstract)
class PLANMODELLER3D_API UBasePropertyField : public UPanelUI
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UVerticalBox* ButtonsContainer;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class URichTextBlock* Label;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* ApplyButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* RevertButton;
	
protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void BaseInit(FText Name);

	UFUNCTION()
	void SetButtonsVisibility(bool bVisible);

	UFUNCTION()
	virtual void OnApplyButtonClicked() {}

	UFUNCTION()
	virtual void OnRevertButtonClicked() {}
};
