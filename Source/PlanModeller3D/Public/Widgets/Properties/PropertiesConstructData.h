// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoolPropertyConstructObject.h"
#include "NumberPropertyConstructObject.h"
#include "TextPropertyConstructObject.h"
#include "UObject/Object.h"
#include "PropertiesConstructData.generated.h"

UCLASS(BlueprintType)
class PLANMODELLER3D_API UPropertiesConstructData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FNumberPropertyConstructObject> NumberProperties = {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FTextPropertyConstructObject> TextProperties = {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FBoolPropertyConstructObject> BoolProperties = {};

	TArray<int> GetPropertiesOrder() const
	{
		TArray<int> PropertiesOrder = {};
		for (auto Property : NumberProperties)
		{
			if (!PropertiesOrder.Contains(Property.Order))
			{
				PropertiesOrder.Add(Property.Order);
			}
		}
		for (auto Property : TextProperties)
		{
			if (!PropertiesOrder.Contains(Property.Order))
			{
				PropertiesOrder.Add(Property.Order);
			}
		}
		for (auto Property : BoolProperties)
		{
			if (!PropertiesOrder.Contains(Property.Order))
			{
				PropertiesOrder.Add(Property.Order);
			}
		}
		PropertiesOrder.Sort();
		return PropertiesOrder;
	}
};
