// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePropertyField.h"
#include "SceneObjectPropertyConstructObject.h"
#include "SceneObjectPropertyField.generated.h"


class UInstrumentsManager;

UCLASS(Abstract, BlueprintType, Blueprintable)
class PLANMODELLER3D_API USceneObjectPropertyField : public UBasePropertyField
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	URichTextBlock* SceneObjectName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* SceneObjectIcon;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* ChangeSceneObjectButton;

	UPROPERTY(BlueprintReadOnly)
	bool bIsInstrumentActive = false;

protected:
	UPROPERTY()
	FSceneObjectPropertyConstructObject CurrentConstructObject;
	
	UPROPERTY()
	FOnGetSceneObjectValue GetValueDelegate;

	UPROPERTY()
	FOnSetSceneObjectValue SetValueDelegate;

	UPROPERTY()
	FSceneObjectSelection CurrentValue;

	UPROPERTY()
	UInstrumentsManager* InstrumentsManager;

public:
	UFUNCTION(BlueprintCallable)
	void Init(FSceneObjectPropertyConstructObject InConstructObject);
	
protected:
	virtual void NativeOnInitialized() override;
	
	virtual void OnApplyButtonClicked() override;

	virtual void OnRevertButtonClicked() override;

	UFUNCTION(BlueprintNativeEvent)
	void UpdateCurrentValue(const FSceneObjectSelection& InSceneObject);

private:
	UFUNCTION()	void OnChangeSceneObjectButtonClicked();
	UFUNCTION()	void OnInstrumentDeactivated();
};
