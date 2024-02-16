#pragma once
#include "BoolPropertyConstructObject.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal(bool, FOnGetBoolValue);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSetBoolValue, const bool, Value);

USTRUCT(BlueprintType)
struct FBoolPropertyConstructObject
{
	GENERATED_BODY()

	FBoolPropertyConstructObject() = default;
	
	FBoolPropertyConstructObject(int Order, const FText& Name, const FOnGetBoolValue& GetValue,
		const FOnSetBoolValue& SetValue): Order(Order),Name(Name),GetValue(GetValue),SetValue(SetValue){ }

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Order;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FOnGetBoolValue GetValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FOnSetBoolValue SetValue;
	
};
