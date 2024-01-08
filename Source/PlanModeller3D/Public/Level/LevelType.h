#pragma once

UENUM(BlueprintType)
enum class ELevelType : uint8
{
	None = 0				UMETA(DisplayName = "None"),
	MainMenu = 1			UMETA(DisplayName = "Main Menu"),
	Game = 2				UMETA(DisplayName = "Game"),
	Count = 3				UMETA(Hidden)
};
