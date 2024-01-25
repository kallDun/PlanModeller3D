#pragma once

UENUM(BlueprintType)
enum class ECrudActionType : uint8
{
	None = 0		UMETA(DisplayName = "None"),
	Create = 1		UMETA(DisplayName = "Create"),
	Read = 2		UMETA(DisplayName = "Read"),
	Update = 3		UMETA(DisplayName = "Update"),
	Delete = 4		UMETA(DisplayName = "Delete"),
};
