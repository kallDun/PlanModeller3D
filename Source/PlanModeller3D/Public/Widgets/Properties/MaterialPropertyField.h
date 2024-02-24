// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePropertyField.h"
#include "MaterialPropertyConstructObject.h"
#include "MaterialPropertyField.generated.h"

class USidePanel;
struct FStoredMaterialData;
struct FMaterialPropertyConstructObject;

UCLASS(Abstract, BlueprintType, Blueprintable)
class PLANMODELLER3D_API UMaterialPropertyField : public UBasePropertyField
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	URichTextBlock* MaterialName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* MaterialIcon;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* ChangeMaterialButton;

	UPROPERTY(BlueprintReadOnly)
	USidePanel* SidePanel;

protected:
	UPROPERTY()
	FOnGetMaterialValue GetValueDelegate;

	UPROPERTY()
	FOnSetMaterialValue SetValueDelegate;

	UPROPERTY()
	int MaterialIndex;
	
	UPROPERTY()
	FName MaterialID;

public:
	UFUNCTION(BlueprintCallable)
	void Init(FMaterialPropertyConstructObject InConstructObject, USidePanel* InSidePanel);
	
protected:
	virtual void NativeOnInitialized() override;
	
	virtual void OnApplyButtonClicked() override;

	virtual void OnRevertButtonClicked() override;

	UFUNCTION(BlueprintCallable)
	void MaterialChangedEventHandler(FName ID);

	UFUNCTION(BlueprintNativeEvent)
	void OnMaterialChanged(FStoredMaterialData MaterialData);

	UFUNCTION(BlueprintImplementableEvent)
	void OnChangeMaterialButtonClicked();

};
