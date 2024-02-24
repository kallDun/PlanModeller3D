#pragma once
#include "MaterialPropertyConstructObject.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal(FName, FOnGetMaterialValue);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSetMaterialValue, const FName, Value);

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
	
};
