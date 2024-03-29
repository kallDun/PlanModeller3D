#pragma once

#include "CoreMinimal.h"
#include "SelectedFurnitureData.generated.h"

USTRUCT(BlueprintType)
struct FSelectedFurnitureData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName VariationName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Priority;
};
