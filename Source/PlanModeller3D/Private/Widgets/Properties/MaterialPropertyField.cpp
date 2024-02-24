// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Properties/MaterialPropertyField.h"
#include "Components/Button.h"
#include "Components/RichTextBlock.h"
#include "Core/CoreFunctionLib.h"
#include "Managers/Material/MaterialsManager.h"
#include "Widgets/Properties/MaterialPropertyConstructObject.h"


void UMaterialPropertyField::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ChangeMaterialButton->OnClicked.AddDynamic(this, &UMaterialPropertyField::OnChangeMaterialButtonClicked);
}

void UMaterialPropertyField::Init(const FMaterialPropertyConstructObject InConstructObject, USidePanel* InSidePanel)
{
	BaseInit(InConstructObject.Name);
	SidePanel = InSidePanel;
	GetValueDelegate = InConstructObject.GetValue;
	SetValueDelegate = InConstructObject.SetValue;
	OnRevertButtonClicked();
}

void UMaterialPropertyField::OnApplyButtonClicked()
{
	Super::OnApplyButtonClicked();
	SetValueDelegate.Execute(MaterialID);
	SetButtonsVisibility(false);	
}

void UMaterialPropertyField::OnRevertButtonClicked()
{
	Super::OnRevertButtonClicked();
	MaterialChangedEventHandler(GetValueDelegate.Execute());
	SetValueDelegate.Execute(MaterialID);
	SetButtonsVisibility(false);
}

void UMaterialPropertyField::MaterialChangedEventHandler(FName ID)
{
	SetValueDelegate.Execute(ID);
	MaterialID = ID;
	const FStoredMaterialData Data = UCoreFunctionLib::GetMaterialsManager(this)->GetMaterialData(ID);
	OnMaterialChanged(Data);
}

void UMaterialPropertyField::OnMaterialChanged_Implementation(const FStoredMaterialData MaterialData)
{
	MaterialName->SetText(FText::FromString(MaterialData.Name.ToString()));
}
