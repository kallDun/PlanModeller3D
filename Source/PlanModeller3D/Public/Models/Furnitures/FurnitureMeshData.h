#pragma once

#include "CoreMinimal.h"
#include "FurnitureMeshData.generated.h"

USTRUCT(BlueprintType)
struct FFurnitureMeshData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int VariationIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UMaterialInterface*> MeshMaterials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector RelativeLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator RelativeRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector RelativeScale3D;
};
