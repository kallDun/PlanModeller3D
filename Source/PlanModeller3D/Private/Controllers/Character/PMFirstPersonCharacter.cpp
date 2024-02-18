// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Character/PMFirstPersonCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Models/SaveData/PlanModellerSaveData.h"
#include "Services/Save/SavingService.h"
#include "Utils/Vector2D_MathLib.h"
#include "Widgets/Properties/NumberPropertyConstructObject.h"
#include "Widgets/Properties/PropertiesConstructData.h"


UPropertiesConstructData* APMFirstPersonCharacter::GetProperties_Implementation()
{
	UPropertiesConstructData* Data = Super::GetProperties_Implementation();
	
	FOnGetNumberValue GetCameraFOV = FOnGetNumberValue();
	GetCameraFOV.BindDynamic(this, &APMFirstPersonCharacter::GetCameraFOV);
	FOnSetNumberValue SetCameraFOV = FOnSetNumberValue();
	SetCameraFOV.BindDynamic(this, &APMFirstPersonCharacter::SetCameraFOV);
	Data->NumberProperties.Add(FNumberPropertyConstructObject(
		0, FText::FromString("Camera FOV"), false, ENumberType::NT_Float, GetCameraFOV, SetCameraFOV, 0.0f, 180.0f));
	
	return Data;
}

void APMFirstPersonCharacter::ResetStartLocationAndRotation_Implementation()
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
	}
}
