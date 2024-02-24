#pragma once
#include "MaterialPropertyConstructObject.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(FName, FOnGetMaterialValue, const int, MaterialIndex);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnSetMaterialValue, const FName, Value, const int, MaterialIndex);

USTRUCT(BlueprintType)
struct FMaterialPropertyConstructObject
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Order;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FOnGetMaterialValue GetValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FOnSetMaterialValue SetValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int MaterialIndex;
	
};
