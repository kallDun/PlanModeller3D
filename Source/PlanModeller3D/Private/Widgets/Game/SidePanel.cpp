// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Game/SidePanel.h"

#include "Components/CanvasPanel.h"
#include "Core/CoreFunctionLib.h"
#include "Services/UI/ManagerUI.h"
#include "Services/UI/PanelUI.h"
#include "Widgets/Game/OpenSidePanelChildrenAction.h"

void USidePanel::NativeConstruct()
{
	Super::NativeConstruct();
	ManagerUI = UCoreFunctionLib::GetManagerUI(this);
}

void USidePanel::OpenChildren(const FName SidePanelChildrenName, const FOpenSidePanelChildrenAction OpenChildrenAction)
{
	const auto Action = NewObject<UOpenSidePanelChildrenAction>();
	Action->SidePanelChildrenName = SidePanelChildrenName;
	Action->OpenSidePanelChildrenAction = OpenChildrenAction;
	ChildrenPool.Add(Action);
	OpenLastChildrenInThePool();
}

void USidePanel::CloseLast()
{
	if (ChildrenPool.Num() > 0)
	{
		OpenLastChildrenInThePool();
	}
	else
	{
		OnPanelClose.Broadcast();
	}
}

void USidePanel::CloseAll()
{
	while (ChildrenPool.Num() > 0)
	{
		OpenLastChildrenInThePool();
	}
	if (CurrentChildren)
	{
		CurrentChildren->Close();
		CurrentChildren = nullptr;
	}
}

void USidePanel::OpenLastChildrenInThePool()
{
	if (CurrentChildren)
	{
		CurrentChildren->Close();
		CurrentChildren = nullptr;
	}
	if (ChildrenPool.Num() > 0)
	{
		const auto Action = ChildrenPool.Last();
		const auto Panel = ManagerUI->GetPanel(Action->SidePanelChildrenName, ChildrenContainer);
		if (UPanelUI* SidePanel = Cast<UPanelUI>(Panel))
		{
			Action->OpenSidePanelChildrenAction.ExecuteIfBound(SidePanel);
		}
	}
}
