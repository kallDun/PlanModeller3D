// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Character/PMThirdPersonCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Models/Plan/DMRoom.h"
#include "Models/SaveData/PlanModellerSaveData.h"
#include "Services/Save/SavingService.h"
#include "Utils/Vector2D_MathLib.h"
#include "Widgets/Properties/NumberPropertyConstructObject.h"
#include "Widgets/Properties/PropertiesConstructData.h"


UPropertiesConstructData* APMThirdPersonCharacter::GetProperties_Implementation()
{
	UPropertiesConstructData* Data = Super::GetProperties_Implementation();

	FOnGetSceneObjectValue GetRoom = FOnGetSceneObjectValue();
	GetRoom.BindDynamic(this, &APMThirdPersonCharacter::GetRoom);
	FOnSetSceneObjectValue SetRoom = FOnSetSceneObjectValue();
	SetRoom.BindDynamic(this, &APMThirdPersonCharacter::SetRoom);
	Data->SceneObjectProperties.Add(FSceneObjectPropertyConstructObject(
		0, FText::FromString("Spawn Room"), static_cast<uint8>(EInstrumentAvailableSelection::IAS_Room), GetRoom, SetRoom));
	
	FOnGetNumberValue GetCameraFOV = FOnGetNumberValue();
	GetCameraFOV.BindDynamic(this, &APMThirdPersonCharacter::GetCameraFOV);
	FOnSetNumberValue SetCameraFOV = FOnSetNumberValue();
	SetCameraFOV.BindDynamic(this, &APMThirdPersonCharacter::SetCameraFOV);
	Data->NumberProperties.Add(FNumberPropertyConstructObject(
		1, FText::FromString("Camera FOV"), false, ENumberType::NT_Float, GetCameraFOV, SetCameraFOV, 0.0f, 180.0f));
	
	return Data;
}

void APMThirdPersonCharacter::ResetStartLocationAndRotation_Implementation()
{
	auto Rooms = SavingService->CurrentSaveGame->Plan2D.Rooms;
	auto Room = Rooms.FindByPredicate([this](const FDMRoom& InRoom) { return InRoom.Id == GetCharacterSettings().RoomID; });
	if (Room)
	{
		const FVector2D Center = UVector2D_MathLib::GetCenter(Room->Points);
		GetCharacterSettings().SavedLocation = FVector(Center.X, Center.Y, 
		Room->Height + Room->HeightFromFloor + GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
		GetCharacterSettings().SavedRotation = FRotator();
	}
	else if (Rooms.Num() > 0)
	{
		const FVector2D Center = UVector2D_MathLib::GetCenter(Rooms[0].Points);
		GetCharacterSettings().SavedLocation = FVector(Center.X, Center.Y,
			Rooms[0].Height + Rooms[0].HeightFromFloor + GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
		GetCharacterSettings().SavedRotation = FRotator();
		GetCharacterSettings().RoomID = Rooms[0].Id;
		GetCharacterSettings().RoomName = Rooms[0].Name;
	}
}
