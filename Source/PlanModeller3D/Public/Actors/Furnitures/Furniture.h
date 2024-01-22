// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Models/Furnitures/FurnitureData.h"
#include "Services/Pool/PoolObject.h"
#include "Furniture.generated.h"

class UPoolService;

UCLASS(Abstract, Blueprintable, BlueprintType)
class PLANMODELLER3D_API AFurniture : public AActor, public IPoolObject
{
	GENERATED_BODY()

public:
	AFurniture() = default;

	UPROPERTY(BlueprintReadOnly)
	FFurnitureData Data;
	
	UFUNCTION()
	void Init(const FFurnitureData& FurnitureData);

	virtual void GetFromPool_Implementation(UPoolService* Pool) override;

	virtual void ReturnToPool_Implementation(UPoolService* Pool) override;
	
};
