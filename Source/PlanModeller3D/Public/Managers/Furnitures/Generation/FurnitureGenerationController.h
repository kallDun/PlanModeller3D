// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/Initialization/Initializable.h"
#include "Services/Save/LoadedFromSave.h"
#include "UObject/Object.h"
#include "FurnitureGenerationController.generated.h"

class UFurnitureGenerationComponent;
struct FFurnitureGenerationData;

UCLASS(BlueprintType)
class PLANMODELLER3D_API UFurnitureGenerationController : public UObject, public IInitializable, public ILoadedFromSave
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<UFurnitureGenerationComponent*> GenerationComponents = {};

protected:
	UPROPERTY()
	UPlanModellerSaveData* SaveData;

public:
	UFUNCTION()
	FFurnitureGenerationData GetGenerationData() const;

	UFUNCTION()
	void SetGenerationData(const FFurnitureGenerationData& Data) const;

public:
	virtual void Init_Implementation(UPrimaryDataAsset* Data) override;

	virtual void LoadFromSave_Implementation(UPlanModellerSaveData* Save) override;

	UFUNCTION(BlueprintCallable)
	void GenerateAll();

	UFUNCTION(BlueprintCallable)
	void ClearAll();
};
