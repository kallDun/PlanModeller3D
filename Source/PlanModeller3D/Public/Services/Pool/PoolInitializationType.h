#pragma once


UENUM(BlueprintType)
enum class EPoolInitializationType : uint8
{
	Immediate = 0		UMETA(DisplayName = "Immediate"),
	Lazy = 1			UMETA(DisplayName = "Lazy"),
};
