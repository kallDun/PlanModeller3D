#pragma once

UENUM(BlueprintType)
enum class EActionOnGetSingletonPanel : uint8
{
	None = 0					UMETA(DisplayName = "None"),
	DoNothing = 1				UMETA(DisplayName = "Do Nothing"),
	ReturnAndGetPanel = 2		UMETA(DisplayName = "Return And Get Panel"),
	ReturnOld = 3				UMETA(DisplayName = "Return Old"),
};
