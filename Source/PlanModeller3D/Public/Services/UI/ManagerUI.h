// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ManagerUI.generated.h"

class UPoolsSystem;
class UPanelUI;
class UManagerUIData;

UCLASS(BlueprintType)
class PLANMODELLER3D_API UManagerUI : public UObject, public IInitializable
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UManagerUIData* Data;

	UPROPERTY()
	UPoolsSystem* PoolsSystem;

public:
	UFUNCTION()
	virtual void Init_Implementation(UPrimaryDataAsset* ManagerData) override;

	UFUNCTION()
	void Init2(UPrimaryDataAsset* ManagerData);

	UFUNCTION(BlueprintCallable)
	UPanelUI* GetPanel(FName PanelName, UObject* Parent) const;

	UFUNCTION(BlueprintCallable)
	void ReturnPanel(UPanelUI* Panel) const;
	
};
