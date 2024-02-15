// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/UI/PanelUI.h"
#include "SidePanelChildren.generated.h"

class USidePanel;

UCLASS(Abstract, BlueprintType, Blueprintable)
class PLANMODELLER3D_API USidePanelChildren : public UPanelUI
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USidePanel* SidePanelParent;

	UFUNCTION()
	void SetSidePanelParent(USidePanel* SidePanel);

	virtual void ReturnToPool_Implementation(UPoolService* Pool) override;
};
