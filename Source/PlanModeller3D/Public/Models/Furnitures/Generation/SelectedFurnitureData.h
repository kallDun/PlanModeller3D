#pragma once

#include "CoreMinimal.h"
#include "SelectedFurnitureData.generated.h"

USTRUCT(BlueprintType)
struct FSelectedFurnitureData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Priority;
};
