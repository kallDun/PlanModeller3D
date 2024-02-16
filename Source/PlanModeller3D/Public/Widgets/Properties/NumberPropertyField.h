// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePropertyField.h"
#include "NumberPropertyConstructObject.h"
#include "TextPropertyConstructObject.h"
#include "NumberPropertyField.generated.h"



UCLASS(Abstract, BlueprintType, Blueprintable)
class PLANMODELLER3D_API UNumberPropertyField : public UBasePropertyField
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UEditableTextBox* InputField;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class USlider* InputSlider;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* SliderValueText;

protected:
	UPROPERTY()
	FOnGetNumberValue GetValueDelegate;

	UPROPERTY()
	FOnSetNumberValue SetValueDelegate;

	UPROPERTY()
	bool bIsSliderEnabled;

	UPROPERTY()
	ENumberType NumberType;

public:
	UFUNCTION(BlueprintCallable)
	void Init(FNumberPropertyConstructObject InConstructObject);
	
protected:
	virtual void NativeOnInitialized() override;
	
	virtual void OnApplyButtonClicked() override;

	virtual void OnRevertButtonClicked() override;

	UFUNCTION()
	void OnInputFieldChanged(const FText& Text);

	UFUNCTION()
	void OnInputSliderChanged(float Value);

private:
	UFUNCTION()
	double GetNumberValue() const;

	UFUNCTION()
	bool IsNumberValid() const;
};
