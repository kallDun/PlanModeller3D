#pragma once

#include "CoreMinimal.h"
#include "StoredMaterialData.generated.h"

USTRUCT(BlueprintType)
struct FStoredMaterialData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* Interface;
	
};
