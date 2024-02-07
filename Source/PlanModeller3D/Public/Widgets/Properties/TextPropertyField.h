// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePropertyField.h"
#include "TextPropertyField.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal(FString, FOnGetStringValue);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSetStringValue, const FString, Value);

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
	void Init(const FText Name, bool bIsReadOnly, FOnGetStringValue GetValue, FOnSetStringValue SetValue);
	
protected:
	virtual void NativeOnInitialized() override;
	
	virtual void OnApplyButtonClicked() override;

	virtual void OnRevertButtonClicked() override;

	UFUNCTION()
	void OnInputFieldTextChanged(const FText& Text);
};
