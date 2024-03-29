// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaviWidget.h"
#include "UObject/Object.h"
#include "NaviWidgetListNavigator.generated.h"

UENUM(BlueprintType)
enum class ENaviWidgetNavigatorDefaultBehavior : uint8
{
	NWNDB_DefaultToFirst,
	NWNDB_DefaultToLast,
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class MYPROJECT_API UNaviWidgetListNavigator : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	ENaviWidgetNavigatorDefaultBehavior DefaultBehavior;

	UFUNCTION(BlueprintCallable)
	void ResetToDefaultWidget();

	UFUNCTION(BlueprintCallable)
	int GetDefaultIndex();

	UFUNCTION(BlueprintCallable)
	UNaviWidget* GetDefaultItem();

	UFUNCTION(BlueprintCallable)
	void NavigateUp();

	UFUNCTION(BlueprintCallable)
	void NavigateDown();

	UFUNCTION(BlueprintCallable)
	void AddItem(UNaviWidget* NewItem);

	UFUNCTION(BlueprintCallable)
	void AddItems(TArray<UNaviWidget*> NewItems);

	UFUNCTION(BlueprintCallable)
	void ClearItems();
	
private:
	UPROPERTY()
	TArray<UNaviWidget*> Items;
	UPROPERTY()
	UNaviWidget* SelectedItem;
	UPROPERTY()
	int SelectedIndex;
	
	void Navigate(bool bDirection);

	UFUNCTION()
	void HandleExternalNavigation(UNaviWidget* NavigatedItem);

	
};
