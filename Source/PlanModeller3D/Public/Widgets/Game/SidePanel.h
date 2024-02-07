// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OpenSidePanelChildrenAction.h"
#include "Blueprint/UserWidget.h"
#include "SidePanel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSidePanelClose);

class UManagerUI;
class USidePanelChildren;

UCLASS(Abstract, Blueprintable, BlueprintType)
class PLANMODELLER3D_API USidePanel : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<UOpenSidePanelChildrenAction*> ChildrenPool = {};

	UPROPERTY()
	UPanelUI* CurrentChildren = nullptr;

	UPROPERTY()
	UManagerUI* ManagerUI;

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnSidePanelClose OnPanelClose;
    	
	UFUNCTION(BlueprintCallable)
	void OpenChildren(FName SidePanelChildrenName, FOpenSidePanelChildrenAction OpenChildrenAction);

	UFUNCTION(BlueprintCallable)
	void CloseLast();

	UFUNCTION(BlueprintCallable)
	void CloseAll();

	UFUNCTION(BlueprintCallable)
	void CloseCurrentChildren();

private:
	UFUNCTION()
	void OpenLastChildrenInThePool();
};
