#pragma once

#include "CoreMinimal.h"
#include "FurniturePlacementType.h"
#include "FurnitureVariationData.h"
#include "FurnitureData.generated.h"

USTRUCT(BlueprintType)
struct FFurnitureData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Furniture")
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Furniture")
	EFurniturePlacementType PlacementType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Furniture")
	TSubclassOf<class AFurniture> FurnitureClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Construct Data")
	FVector ForwardVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Construct Data")
	bool IsTransparentForPlacement = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Construct Data",
		meta = (EditCondition = "IsTransparentForPlacement", EditConditionHides=true))
	int PlacementPriority;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Construct Data")
	TArray<FFurnitureVariationData> Variations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="View")
	FString Category;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="View")
	FString Description;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="View")
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pool")
	bool UseNameAsPoolID = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pool",
		meta = (EditCondition = "!UseNameAsPoolID", EditConditionHides=true))
	FString PoolID;
	
};
