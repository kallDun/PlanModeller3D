// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Game/SidePanel.h"
#include "Components/WidgetSwitcher.h"
#include "Core/CoreFunctionLib.h"
#include "Services/UI/ManagerUI.h"
#include "Services/UI/PanelUI.h"
#include "Widgets/Game/OpenSidePanelChildrenAction.h"
#include "Widgets/Game/SidePanelChildren.h"

void USidePanel::NativeConstruct()
{
	Super::NativeConstruct();
	ManagerUI = UCoreFunctionLib::GetManagerUI(this);
}

void USidePanel::OpenChildren(const FName SidePanelChildrenName, const int Index,
	const FOpenSidePanelChildrenAction OpenChildrenAction)
{
	UOpenSidePanelChildrenAction* Action = NewObject<UOpenSidePanelChildrenAction>();
	Action->SidePanelChildrenName = SidePanelChildrenName;
	Action->OpenSidePanelChildrenAction = OpenChildrenAction;
	Action->Index = Index;

	CloseLastChildrenInThePool(false);
	ChildrenPool.Add(Action);
	OpenLastChildrenInThePool();
}

void USidePanel::CloseLast()
{
	if (ChildrenPool.Num() > 1)
	{
		CloseLastChildrenInThePool(true);
		ChildrenPool.Pop();
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
		CloseLastChildrenInThePool(true);
		ChildrenPool.Pop();
		OpenLastChildrenInThePool();
	}
}

void USidePanel::CloseLastChildrenInThePool(const bool HideFromScene)
{
	if (ChildrenPool.Num() > 0)
	{
		UOpenSidePanelChildrenAction* Action = ChildrenPool.Last();
		if (Action->SidePanelChildren)
		{
			if (HideFromScene)
			{
				Action->SidePanelChildren->Close();
				Action->SidePanelChildren = nullptr;
			}
			else
			{
				Action->SidePanelChildren->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
	}
}

void USidePanel::OpenLastChildrenInThePool()
{
	if (ChildrenPool.Num() > 0)
	{
		UOpenSidePanelChildrenAction* Action = ChildrenPool.Last();
		if (Action->SidePanelChildren)
		{
			Action->SidePanelChildren->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			const auto Panel = ManagerUI->GetPanel(Action->SidePanelChildrenName, ChildrenContainer);
			if (UPanelUI* SidePanel = Cast<UPanelUI>(Panel))
			{
				Action->OpenSidePanelChildrenAction.ExecuteIfBound(SidePanel, Action->Index);
			}
			if (USidePanelChildren* SidePanelChildren = Cast<USidePanelChildren>(Panel))
			{
				SidePanelChildren->SetSidePanelParent(this);
			}
			Action->SidePanelChildren = Panel;
		}

		const int Index = ChildrenContainer->GetChildIndex(Action->SidePanelChildren);
		ChildrenContainer->SetActiveWidgetIndex(Index);
	}
}
