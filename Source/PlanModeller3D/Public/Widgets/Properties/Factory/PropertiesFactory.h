// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PropertiesFactory.generated.h"

class UPropertiesConstructData;
class UPropertiesFactoryData;
class UBasePropertyField;

UCLASS()
class PLANMODELLER3D_API UPropertiesFactory : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Widgets", meta=(HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static TArray<UBasePropertyField*> CreateProperties(const UObject* WorldContextObject, UObject* Parent,
														const UPropertiesConstructData* Properties, UPropertiesFactoryData* Data);
	
};
