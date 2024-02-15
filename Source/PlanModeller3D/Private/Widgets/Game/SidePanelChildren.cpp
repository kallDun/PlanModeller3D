// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Game/SidePanelChildren.h"


void USidePanelChildren::SetSidePanelParent(USidePanel* SidePanel)
{
	SidePanelParent = SidePanel;
}

void USidePanelChildren::ReturnToPool_Implementation(UPoolService* Pool)
{
	SidePanelParent = nullptr;
	Super::ReturnToPool_Implementation(Pool);
}
