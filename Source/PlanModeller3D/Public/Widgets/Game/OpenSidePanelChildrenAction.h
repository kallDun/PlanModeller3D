// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "OpenSidePanelChildrenAction.generated.h"

class UPanelUI;

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOpenSidePanelChildrenAction, UPanelUI*, SidePanelChildren, int, Index);

UCLASS()
class PLANMODELLER3D_API UOpenSidePanelChildrenAction : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FName SidePanelChildrenName;

	UPROPERTY()
	int Index;
	
	UPROPERTY()
	FOpenSidePanelChildrenAction OpenSidePanelChildrenAction;
};
