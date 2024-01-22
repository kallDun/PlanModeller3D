#pragma once


UENUM(BlueprintType)
enum class EFurniturePlacementType : uint8
{
	Floor = 0			UMETA(DisplayName = "Floor"),
	Wall = 1			UMETA(DisplayName = "Wall"),
	Ceiling = 2			UMETA(DisplayName = "Ceiling"),
	Window = 3			UMETA(DisplayName = "Window"),
	Door = 4			UMETA(DisplayName = "Door"),
	Prop = 5			UMETA(DisplayName = "Prop"),
};
