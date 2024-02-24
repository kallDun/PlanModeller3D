#pragma once

#include "CoreMinimal.h"
#include "SavedMaterialData.generated.h"

USTRUCT(BlueprintType)
struct FSavedMaterialData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MaterialName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MaterialID;
	
};
