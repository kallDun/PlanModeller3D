// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Models/Furnitures/Generation/FurnitureGenerationData.h"
#include "Models/Instrument/SceneObjectSelection.h"
#include "Services/Initialization/Initializable.h"
#include "Services/Save/LoadedFromSave.h"
#include "UObject/Object.h"
#include "FurnitureGenerationController.generated.h"

class UPropertiesConstructData;
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

	UFUNCTION() FSceneObjectSelection GetRoom()
	{
		return FSceneObjectSelection(
			EInstrumentAvailableSelection::IAS_Room,
			GetGenerationData().RoomID,
			GetGenerationData().RoomName);
	}
	
	UFUNCTION() void SetRoom(const FSceneObjectSelection Selection)
	{
		if (Selection.SelectionType != EInstrumentAvailableSelection::IAS_Room) return;
		GetGenerationData().RoomID = Selection.SelectionId;
		GetGenerationData().RoomName = Selection.SelectionName;
	}

public:
	UFUNCTION()
	FFurnitureGenerationData& GetGenerationData() const;

	UFUNCTION()
	void SetGenerationData(const FFurnitureGenerationData& Data) const;

public:
	virtual void Init_Implementation(UPrimaryDataAsset* Data) override;

	virtual void LoadFromSave_Implementation(UPlanModellerSaveData* Save) override;

	UFUNCTION(BlueprintCallable)
	void GenerateAll();

	UFUNCTION(BlueprintCallable)
	void ClearAll();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UPropertiesConstructData* GetProperties();
};
