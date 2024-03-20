// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Models/Furnitures/FurnitureData.h"
#include "Models/Plan3D/MFurniture.h"
#include "Services/Pool/PoolObject.h"
#include "Furniture.generated.h"

struct FMFurniture;
class UPoolService;

UCLASS(Abstract, Blueprintable, BlueprintType)
class PLANMODELLER3D_API AFurniture : public AActor, public IPoolObject
{
	GENERATED_BODY()

public:
	AFurniture() = default;

	UPROPERTY(BlueprintReadOnly)
	FFurnitureData Data;

	UPROPERTY(BlueprintReadOnly)
	FString ID;

	UPROPERTY(BlueprintReadOnly)
	FMFurniture SaveModel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMeshComponent*> Meshes = {};
	
	UFUNCTION()
	void Init(const FFurnitureData& FurnitureData, const FMFurniture& Model, const FString& Identifier);

	UFUNCTION(BlueprintNativeEvent)
	void UpdateView(const FMFurniture& Model);

	UFUNCTION(BlueprintNativeEvent)
	bool CheckPlacement();

	virtual void GetFromPool_Implementation(UPoolService* Pool) override;

	virtual void ReturnToPool_Implementation(UPoolService* Pool) override;
};
