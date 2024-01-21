// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Services/Pool/PoolObject.h"
#include "PanelUI.generated.h"

class UPoolService;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPanelClosed);

UCLASS(Abstract, BlueprintType, Blueprintable)
class PLANMODELLER3D_API UPanelUI : public UUserWidget, public IPoolObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UPoolService* PoolService;

public:
	UPROPERTY(BlueprintAssignable, Category = "UI Panel")
	FOnPanelClosed OnPanelClosed;
	
	UFUNCTION(BlueprintCallable, Category = "UI Panel")
	void Close();
	
	virtual void GetFromPool_Implementation(UPoolService* Pool) override;

	virtual void ReturnToPool_Implementation(UPoolService* Pool) override;
};
