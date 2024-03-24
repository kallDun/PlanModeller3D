#pragma once

UENUM(BlueprintType)
enum class EFurnitureInstrumentType : uint8
{
	SpawnFromLibrary = 0			UMETA(DisplayName = "Spawn from Library"),
	UpdateConcrete = 1				UMETA(DisplayName = "UpdateConcrete"),
	SpawnWithoutLibrary = 2			UMETA(DisplayName = "Spawn without Library"),
};
