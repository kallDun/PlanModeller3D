#pragma once


UENUM(BlueprintType)
enum class EPlanModelType : uint8
{
	None = 0			UMETA(DisplayName = "None"),
	Room = 1			UMETA(DisplayName = "Room"),
	Wall = 2			UMETA(DisplayName = "Wall"),
	Window = 3			UMETA(DisplayName = "Window"),
	Door = 4			UMETA(DisplayName = "Door"),
	Furniture = 5		UMETA(DisplayName = "Furniture"),
};
