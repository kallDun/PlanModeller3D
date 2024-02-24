// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FoundationActor.h"
#include "Models/Plan/DMDoorWindow.h"
#include "Models/Plan/DMWall.h"
#include "Models/Plan3D/MWall.h"
#include "WallActor.generated.h"


struct FVector2DArray;

UCLASS(Abstract, Blueprintable, BlueprintType)
class PLANMODELLER3D_API AWallActor : public AFoundationActor 
{
	GENERATED_BODY()

public:
	AWallActor() = default;

	UPROPERTY(BlueprintReadOnly)
	int MaterialsCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDMWall	DMWall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMWall MWall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDMRoom> DMRooms = {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDMDoorWindow> DMDoors = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDMDoorWindow> DMWindows = {};

private:
	UPROPERTY()
	int CurrentIndex;
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetMaterialIndexForDoorWindow()
	{
		CurrentIndex++;
		return CurrentIndex;
	}
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init(FDMWall Wall);

	virtual UPropertiesConstructData* GetProperties_Implementation() override;

protected:
	UFUNCTION(BlueprintCallable)
	void InitializeMaterialVerticesForRooms();
	
	UFUNCTION(BlueprintImplementableEvent)
	void InitMaterialForRoom(FVector2DArray Pts, int Index);

	UFUNCTION()
	void InitMaterials();
	
};
