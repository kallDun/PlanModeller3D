#pragma once


UENUM(BlueprintType)
enum class ELevelTransitionPoolBehaviour : uint8
{
	Hide = 0				UMETA(DisplayName = "Hide"),
	HideThenShow = 1		UMETA(DisplayName = "Hide Then Show"),
	DoNothing = 2			UMETA(DisplayName = "Do Nothing"),
	Dispose = 3				UMETA(DisplayName = "Dispose"),
};
