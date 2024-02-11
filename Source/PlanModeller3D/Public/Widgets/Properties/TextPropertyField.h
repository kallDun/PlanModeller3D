// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePropertyField.h"
#include "TextPropertyConstructObject.h"
#include "TextPropertyField.generated.h"



UCLASS(Abstract, BlueprintType, Blueprintable)
class PLANMODELLER3D_API UTextPropertyField : public UBasePropertyField
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UEditableTextBox* InputField;

protected:
	UPROPERTY()
	FOnGetStringValue GetValueDelegate;

	UPROPERTY()
	FOnSetStringValue SetValueDelegate;

public:
	UFUNCTION(BlueprintCallable)
	void Init(FTextPropertyConstructObject InConstructObject);
	
protected:
	virtual void NativeOnInitialized() override;
	
	virtual void OnApplyButtonClicked() override;

	virtual void OnRevertButtonClicked() override;

	UFUNCTION()
	void OnInputFieldTextChanged(const FText& Text);
};
