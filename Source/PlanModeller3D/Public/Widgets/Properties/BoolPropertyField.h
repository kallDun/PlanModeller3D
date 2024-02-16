// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePropertyField.h"
#include "BoolPropertyConstructObject.h"
#include "BoolPropertyField.generated.h"


UCLASS(Abstract, BlueprintType, Blueprintable)
class PLANMODELLER3D_API UBoolPropertyField : public UBasePropertyField
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCheckBox* InputField;

protected:
	UPROPERTY()
	FOnGetBoolValue GetValueDelegate;

	UPROPERTY()
	FOnSetBoolValue SetValueDelegate;

public:
	UFUNCTION(BlueprintCallable)
	void Init(FBoolPropertyConstructObject InConstructObject);
	
protected:
	virtual void NativeOnInitialized() override;
	
	virtual void OnApplyButtonClicked() override;

	virtual void OnRevertButtonClicked() override;

	UFUNCTION()
	void OnInputFieldChanged(bool bIsChecked);
};
