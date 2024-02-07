// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "OpenSidePanelChildrenAction.generated.h"

class UPanelUI;

DECLARE_DYNAMIC_DELEGATE_OneParam(FOpenSidePanelChildrenAction, UPanelUI*, SidePanelChildren);

UCLASS()
class PLANMODELLER3D_API UOpenSidePanelChildrenAction : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FName SidePanelChildrenName;

	UPROPERTY()
	FOpenSidePanelChildrenAction OpenSidePanelChildrenAction;
};
