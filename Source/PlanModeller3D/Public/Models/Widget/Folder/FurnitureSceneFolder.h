#pragma once

#include "FurnitureSceneFolder.generated.h"

class AFurniture;

USTRUCT(BlueprintType)
struct FFurnitureSceneFolder
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AFurniture*> Furnitures;
};
