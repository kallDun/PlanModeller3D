// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FurnitureGenerationComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGenerationComponentViewUpdated, UFurnitureGenerationComponent*, Component);

class UPropertiesConstructData;

UCLASS(Abstract, BlueprintType)
class PLANMODELLER3D_API UFurnitureGenerationComponent : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void Initialize(class UFurnitureGenerationController* Controller)
	{
		ParentController = Controller;
	}

	UPROPERTY(BlueprintReadOnly)
	UFurnitureGenerationController* ParentController;

	UPROPERTY(BlueprintReadOnly)
	bool bHasGeneratedItems;

	UPROPERTY(BlueprintReadOnly)
	bool bHasCustomItems;

	UFUNCTION(BlueprintCallable)
	bool IsEmpty() const
	{
		return !bHasGeneratedItems && !bHasCustomItems;
	}
	
	UPROPERTY()
	TArray<UFurnitureGenerationComponent*> RequiredComponentsToGenerate = {};

	UPROPERTY(BlueprintAssignable)
	FGenerationComponentViewUpdated OnGenerationComponentViewUpdated;
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool Generate();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool ClearGeneration();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UPropertiesConstructData* GetProperties();
	
};
