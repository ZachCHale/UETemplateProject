// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "NaviWidget.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "NavigateableWidgetsSubsystem.generated.h"


/**
 * 
 */
UCLASS()
class MYPROJECT_API UNavigateableWidgetsSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable)
	void NavigateTo(UNaviWidget* TargetNaviWidget);
	
	UFUNCTION(BlueprintCallable)
	void InputSubmit();
	UFUNCTION(BlueprintCallable)
	void InputCancel();
	UFUNCTION(BlueprintCallable)
	void InputUp();
	UFUNCTION(BlueprintCallable)
	void InputDown();
	UFUNCTION(BlueprintCallable)
	void InputLeft();
	UFUNCTION(BlueprintCallable)
	void InputRight();

	void Construct();

private:
	UPROPERTY()
	UNaviWidget* CurrentNaviWidget;
	void ShowMessageInvalidCurrentNaviWidget();
};
