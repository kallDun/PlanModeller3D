#pragma once
#include "TextPropertyConstructObject.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal(FString, FOnGetStringValue);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSetStringValue, const FString, Value);

USTRUCT(BlueprintType)
struct FTextPropertyConstructObject
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Order;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsReadOnly;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FOnGetStringValue GetValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FOnSetStringValue SetValue;
	
};
