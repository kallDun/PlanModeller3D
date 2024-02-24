// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Properties/Factory/PropertiesFactory.h"
#include "Core/CoreFunctionLib.h"
#include "Services/UI/ManagerUI.h"
#include "Widgets/Properties/BoolPropertyField.h"
#include "Widgets/Properties/MaterialPropertyField.h"
#include "Widgets/Properties/NumberPropertyField.h"
#include "Widgets/Properties/PropertiesConstructData.h"
#include "Widgets/Properties/SceneObjectPropertyField.h"
#include "Widgets/Properties/TextPropertyField.h"
#include "Widgets/Properties/Factory/PropertiesFactoryData.h"


TArray<UBasePropertyField*> UPropertiesFactory::CreateProperties(const UObject* WorldContextObject, UObject* Parent, USidePanel* SidePanel,
                                                                 const UPropertiesConstructData* Properties, UPropertiesFactoryData* Data)
{
	TArray<UBasePropertyField*> WidgetsArray = {};
	const UManagerUI* UIManager = UCoreFunctionLib::GetManagerUI(WorldContextObject);


	TArray<int> PropertiesOrder = {};
	for (auto Property : Properties->NumberProperties)
	{
		if (!PropertiesOrder.Contains(Property.Order))
		{
			PropertiesOrder.Add(Property.Order);
		}
	}
	for (auto Property : Properties->TextProperties)
	{
		if (!PropertiesOrder.Contains(Property.Order))
		{
			PropertiesOrder.Add(Property.Order);
		}
	}
	for (auto Property : Properties->BoolProperties)
	{
		if (!PropertiesOrder.Contains(Property.Order))
		{
			PropertiesOrder.Add(Property.Order);
		}
	}
	for (auto Property : Properties->SceneObjectProperties)
	{
		if (!PropertiesOrder.Contains(Property.Order))
		{
			PropertiesOrder.Add(Property.Order);
		}
	}
	for (auto Property : Properties->MaterialProperties)
	{
		if (!PropertiesOrder.Contains(Property.Order))
		{
			PropertiesOrder.Add(Property.Order);
		}
	}
	PropertiesOrder.Sort();

	
	for (const int Order : PropertiesOrder)
	{
		for (auto Property : Properties->TextProperties)
		{
			if (Property.Order == Order)
			{
				const auto Widget = UIManager->GetPanel(Data->TextPropertyName, Parent);
				if (UTextPropertyField* TextProperty = Cast<UTextPropertyField>(Widget))
				{
					TextProperty->Init(Property);
					WidgetsArray.Add(TextProperty);
				}
			}
		}
		for (auto Property : Properties->NumberProperties)
		{
			if (Property.Order == Order)
			{
				const auto Widget = UIManager->GetPanel(Data->NumberPropertyName, Parent);
				if (UNumberPropertyField* NumberProperty = Cast<UNumberPropertyField>(Widget))
				{
					NumberProperty->Init(Property);
					WidgetsArray.Add(NumberProperty);
				}
			}
		}
		for (auto Property : Properties->BoolProperties)
		{
			if (Property.Order == Order)
			{
				const auto Widget = UIManager->GetPanel(Data->BoolPropertyName, Parent);
				if (UBoolPropertyField* BoolProperty = Cast<UBoolPropertyField>(Widget))
				{
					BoolProperty->Init(Property);
					WidgetsArray.Add(BoolProperty);
				}
			}
		}
		for (auto Property : Properties->SceneObjectProperties)
		{
			if (Property.Order == Order)
			{
				const auto Widget = UIManager->GetPanel(Data->SceneObjectPropertyName, Parent);
				if (USceneObjectPropertyField* SceneObjectProperty = Cast<USceneObjectPropertyField>(Widget))
				{
					SceneObjectProperty->Init(Property);
					WidgetsArray.Add(SceneObjectProperty);
				}
			}
		}
		for (auto Property : Properties->MaterialProperties)
		{
			if (Property.Order == Order)
			{
				const auto Widget = UIManager->GetPanel(Data->MaterialPropertyName, Parent);
				if (UMaterialPropertyField* MaterialProperty = Cast<UMaterialPropertyField>(Widget))
				{
					MaterialProperty->Init(Property, SidePanel);
					WidgetsArray.Add(MaterialProperty);
				}
			}
		}
	}
	return WidgetsArray;
}
