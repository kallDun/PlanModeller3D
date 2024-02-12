#pragma once
#include "NumberPropertyConstructObject.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal(double, FOnGetNumberValue);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSetNumberValue, const double, Value);

UENUM(BlueprintType)
enum class ENumberType : uint8
{
	NT_Integer = 0		UMETA(DisplayName = "Integer"),
	NT_Float = 1		UMETA(DisplayName = "Float"),
	NT_Double = 2		UMETA(DisplayName = "Double"),
};

USTRUCT(BlueprintType)
struct FNumberPropertyConstructObject
{
	GENERATED_BODY()

	FNumberPropertyConstructObject() = default;

	FNumberPropertyConstructObject(const int InOrder, const FText& InName, const bool InIsReadOnly, const ENumberType InNumberType,
	                               const FOnGetNumberValue& InGetValue, const FOnSetNumberValue& InSetValue)
		: Order(InOrder), Name(InName), bIsReadOnly(InIsReadOnly), NumberType(InNumberType)
		, GetValue(InGetValue), SetValue(InSetValue) { }

	FNumberPropertyConstructObject(const int InOrder, const FText& InName, const bool InIsReadOnly, const ENumberType InNumberType,
	                               const FOnGetNumberValue& InGetValue, const FOnSetNumberValue& InSetValue,
	                               const double InMinValue, const double InMaxValue)
		: Order(InOrder), Name(InName), bIsReadOnly(InIsReadOnly), NumberType(InNumberType)
		, GetValue(InGetValue), SetValue(InSetValue)
		, MinValue(InMinValue), MaxValue(InMaxValue)
	{
		bIsClamped = true;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Order;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsReadOnly;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ENumberType NumberType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FOnGetNumberValue GetValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FOnSetNumberValue SetValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsClamped = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	double MinValue = DBL_MIN;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	double MaxValue = DBL_MAX;
	
};
