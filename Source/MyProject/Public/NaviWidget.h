// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NaviWidget.generated.h"

UENUM(BlueprintType)
enum class ENaviWidgetActionType : uint8
{
	ENWAT_Submit,
	ENWAT_Cancel,
	ENWAT_Up,
	ENWAT_Down,
	ENWAT_Left,
	ENWAT_Right,
	//ENWAT_PageLeft, //BumperButtons
	//ENWAT_PageRight,
	//ENWAT_MiscAction1, //Other face buttons
	//ENWAT_MiscAction2,
	//ENWAT_SpecialLeft,	//Start And Select. Should name these after actions and not the button. (ex: Home - Info - Details)
	//ENWAT_SpecialRight,
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNavigatedToDelegate, class UNaviWidget*, NaviWidget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNavigatedInDelegate, class UNaviWidget*, NaviWidget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNavigatedOutDelegate, class UNaviWidget*, NaviWidget);
/**
 * 
 */
UCLASS()
class MYPROJECT_API UNaviWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnInputUp();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnInputDown();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnInputLeft();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnInputRight();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnInputSubmit();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnInputCancel();
	/**
	* Triggers whenever the widget is directly Navigated to, regardless of coming from a descendant or some other NaviWidget
	*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, DisplayName="On Navigated To")
	void OnNavigatedToBP();
	void OnNavigatedTo();
	/**
	* Triggers when navigating to another NaviWidget that is not a descendent of this NaviWidget
	*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, DisplayName="On Navigated Out")
	void OnNavigatedOutBP();
	void OnNavigatedOut();
	/**
	* Triggers when navigating from another NaviWidget, that is not a descendent of this NaviWidget, directly into a descendant NaviWidget.
	*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, DisplayName="On Navigated In")
	void OnNavigatedInBP();
	void OnNavigatedIn();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DoesActionBubbleUp(ENaviWidgetActionType ActionType, bool &bDoesBubbleUp);
	UFUNCTION(BlueprintCallable)
	bool HasParentNaviWidget();
	UFUNCTION(BlueprintCallable)
	UNaviWidget* GetParentNaviWidget();
	UFUNCTION(BlueprintCallable)
	TArray<UNaviWidget*> GetNaviWidgetsFromRootToThis();
	/**
	* NaviWidgets Automatically Set their parents by traversing up their container UObjects using GetOuter()/
	* You may set the parent manually using SetParentNaviWidgetExplicit.
	* This has no affect on the hierarchy of the UserWidget, this only effects how input is passed up from a NaviWidget to its "container" NaviWidgets.
	*/
	UFUNCTION(BlueprintCallable)
	void SetParentNaviWidgetExplicit(UNaviWidget* NewParent);

	UFUNCTION(BlueprintCallable)
	void NavigateTo();

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintAssignable)
	FNavigatedInDelegate OnNavigatedInFinished;
	UPROPERTY(BlueprintAssignable)
	FNavigatedToDelegate OnNavigatedToFinished;
	UPROPERTY(BlueprintAssignable)
	FNavigatedOutDelegate OnNavigatedOutFinished;

	UFUNCTION(BlueprintCallable)
	void DisplayNaviPath();
	UFUNCTION(BlueprintCallable)
	void DisplayAutomatedNaviPath();
	void DisplayFullPath(UObject* Object);

private:
	UPROPERTY()
	UNaviWidget* ParentNaviWidget;
	bool bIsParentSetExplicitly;
	void TryParentingTo(UObject* Object);
	void SetParent(UNaviWidget* Parent);

};
