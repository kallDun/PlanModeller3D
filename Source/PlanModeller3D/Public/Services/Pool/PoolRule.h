#pragma once

UENUM(BlueprintType)
enum class EPoolRule : uint8
{
	None = 0					UMETA(DisplayName = "None"),
	AddOne = 1					UMETA(DisplayName = "Add One"),
	MultiplyByTwo = 2			UMETA(DisplayName = "Multiply By Two"),
	AddConstant = 3				UMETA(DisplayName = "Add Constant"),
	MultiplyByConstant = 4		UMETA(DisplayName = "Multiply By Constant"),
	Num = 5						UMETA(Hidden)
};