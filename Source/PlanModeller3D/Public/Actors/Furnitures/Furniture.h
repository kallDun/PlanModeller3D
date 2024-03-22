// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Models/Furnitures/FurnitureData.h"
#include "Models/Furnitures/FurnitureMeshData.h"
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

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* PreviewMaterial;
	
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* WrongPlacementMaterial;
	
	UPROPERTY(BlueprintReadOnly)
	FFurnitureData Data;

	UPROPERTY(BlueprintReadOnly)
	FString ID;

	UPROPERTY(BlueprintReadOnly)
	FMFurniture SaveModel;

	UPROPERTY(BlueprintReadOnly)
	TArray<FFurnitureMeshData> Meshes = {};
	
	UFUNCTION()
	void Init(const FFurnitureData& FurnitureData, const FMFurniture& Model, const FString& Identifier);

	UFUNCTION(BlueprintCallable)
	void AddMeshData(int VariationIndex, UStaticMeshComponent* Mesh);

	UFUNCTION(BlueprintNativeEvent)
	void UpdateView(const FMFurniture& Model);

	UFUNCTION(BlueprintNativeEvent)
	void UpdateMeshesByVariation(int VariationIndex, FFurnitureVariationData VariationData);

	UFUNCTION(BlueprintNativeEvent)
	bool CheckPlacement();

	UFUNCTION()
	void UpdateMaterials(bool IsPlacementCorrect);

	virtual void GetFromPool_Implementation(UPoolService* Pool) override;

	virtual void ReturnToPool_Implementation(UPoolService* Pool) override;
};
