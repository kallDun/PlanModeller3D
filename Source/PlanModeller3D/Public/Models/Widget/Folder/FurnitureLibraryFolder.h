#pragma once

#include "Models/Furnitures/FurnitureData.h"
#include "FurnitureLibraryFolder.generated.h"

USTRUCT(BlueprintType)
struct FFurnitureLibraryFolder
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FFurnitureData> Furnitures;
};
