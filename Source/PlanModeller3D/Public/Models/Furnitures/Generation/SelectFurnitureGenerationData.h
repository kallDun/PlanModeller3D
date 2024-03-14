#pragma once

#include "CoreMinimal.h"
#include "SelectedFurnitureData.h"
#include "SelectFurnitureGenerationData.generated.h"

USTRUCT(BlueprintType)
struct FSelectFurnitureGenerationData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSelectedFurnitureData> GeneratedFurniture = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSelectedFurnitureData> CustomFurniture = {};
};
