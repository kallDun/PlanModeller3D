#pragma once

#include "CoreMinimal.h"
#include "AreaGenerationData.h"
#include "PathGenerationData.h"
#include "PlacedFurnitureGenerationData.h"
#include "SelectFurnitureGenerationData.h"
#include "FurnitureGenerationData.generated.h"

USTRUCT(BlueprintType)
struct FFurnitureGenerationData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RoomID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RoomName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSelectFurnitureGenerationData SelectFurnitureComponentData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPlacedFurnitureGenerationData PlacedFurnitureComponentData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPathGenerationData PathComponentData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAreaGenerationData AreaComponentData;
	
};
