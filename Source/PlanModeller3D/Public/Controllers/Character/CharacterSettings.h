#pragma once

#include "CoreMinimal.h"
#include "CharacterSettings.generated.h"

USTRUCT(BlueprintType)
struct FCharacterSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsCurrentCharacter = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bWasPlayedBefore = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bResetLocationAndRotation = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector SavedLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator SavedRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin=0f, ClampMax=180f))
	float CameraFOV = 90.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin=0f, ClampMax=100f))
	float CameraSpeed = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsColliding = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RoomID;
};
