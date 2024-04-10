// Fill out your copyright notice in the Description page of Project Settings.

#include "NaviWidgetSubsystem.h"

DEFINE_LOG_CATEGORY(NaviWidgetLog);

void UNaviWidgetSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("NavigateableWidgetSubsystem: Initialized"));

}

void UNaviWidgetSubsystem::Deinitialize()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("NavigateableWidgetSubsystem: Deinitialized"));
}

void UNaviWidgetSubsystem::NavigateTo(UNaviWidget* NewTargetNaviWidget)
{
	NavigationQueue.Add(NewTargetNaviWidget);
	if(bNavigationInProgress)
		return;
	bNavigationInProgress = true;



	while(NavigationQueue.Num() > 0)
	{
		UNaviWidget* TargetNaviWidget = NavigationQueue[0];
		NavigationQueue.RemoveAt(0);
		if(!IsValid(TargetNaviWidget))
			continue;
		if (!IsValid(CurrentNaviWidget))
		{
			CurrentNaviWidget = TargetNaviWidget;
			TArray<UNaviWidget*> NewNaviWidgetPath = TargetNaviWidget->GetNaviWidgetsFromRootToThis();

			for (auto NaviWidget : NewNaviWidgetPath)
			{
				if(NaviWidget == TargetNaviWidget)
					NaviWidget->OnNavigatedTo();
				else
					NaviWidget->OnNavigatedIn();
			}
		}
		else
		{
			TArray<UNaviWidget*> PrevNaviWidgetPath = CurrentNaviWidget->GetNaviWidgetsFromRootToThis();
			TArray<UNaviWidget*> NewNaviWidgetPath = TargetNaviWidget->GetNaviWidgetsFromRootToThis();
			CurrentNaviWidget = TargetNaviWidget;
		
			for(int i = PrevNaviWidgetPath.Num()-1; i>=0; i--)
			{
				if(NewNaviWidgetPath.Num()>i)
				{
					if(PrevNaviWidgetPath[i] != NewNaviWidgetPath[i])
					{
						PrevNaviWidgetPath[i]->OnNavigatedOut();
					}
				}else
				{
					PrevNaviWidgetPath[i]->OnNavigatedOut();
				}
			}

			for(int i = 0; i < NewNaviWidgetPath.Num()-1; i++)
			{
				if(PrevNaviWidgetPath.Num()>i)
				{
					if(PrevNaviWidgetPath[i] != NewNaviWidgetPath[i])
					{
						NewNaviWidgetPath[i]->OnNavigatedIn();
					}
				}else
				{
					NewNaviWidgetPath[i]->OnNavigatedIn();
				}
			}
			TargetNaviWidget->OnNavigatedTo();
		}
	}
	bNavigationInProgress = false;
}

void UNaviWidgetSubsystem::InputSubmit()
{
	if(!IsValid(CurrentNaviWidget))
	{
		ShowMessageInvalidCurrentNaviWidget();
		return;
	}
	
	UNaviWidget* NaviWidgetI = CurrentNaviWidget;
	bool bBubbleUpAction;
	NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_Submit, bBubbleUpAction);
	NaviWidgetI->OnInputSubmit();
	while(bBubbleUpAction && NaviWidgetI->HasParentNaviWidget())
	{
		NaviWidgetI = NaviWidgetI->GetParentNaviWidget();
		NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_Submit, bBubbleUpAction);
		NaviWidgetI->OnInputSubmit();
	}
}

void UNaviWidgetSubsystem::InputCancel()
{
	if(!IsValid(CurrentNaviWidget))
	{
		ShowMessageInvalidCurrentNaviWidget();
		return;
	}
	
	UNaviWidget* NaviWidgetI = CurrentNaviWidget;
	bool bBubbleUpAction;
	NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_Cancel, bBubbleUpAction);
	NaviWidgetI->OnInputCancel();
	while(bBubbleUpAction && NaviWidgetI->HasParentNaviWidget())
	{
		NaviWidgetI = NaviWidgetI->GetParentNaviWidget();
		NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_Cancel, bBubbleUpAction);
		NaviWidgetI->OnInputCancel();
	}
}

void UNaviWidgetSubsystem::InputUp()
{
	if(!IsValid(CurrentNaviWidget))
	{
		ShowMessageInvalidCurrentNaviWidget();
		return;
	}

	UNaviWidget* NaviWidgetI = CurrentNaviWidget;
	bool bBubbleUpAction;
	NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_Up, bBubbleUpAction);
	NaviWidgetI->OnInputUp();
	while(bBubbleUpAction && NaviWidgetI->HasParentNaviWidget())
	{
		NaviWidgetI = NaviWidgetI->GetParentNaviWidget();
		NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_Up, bBubbleUpAction);
		NaviWidgetI->OnInputUp();
	}
}

void UNaviWidgetSubsystem::InputDown()
{
	if(!IsValid(CurrentNaviWidget))
	{
		ShowMessageInvalidCurrentNaviWidget();
		return;
	}
	
	UNaviWidget* NaviWidgetI = CurrentNaviWidget;
	bool bBubbleUpAction;
	NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_Down, bBubbleUpAction);
	NaviWidgetI->OnInputDown();
	while(bBubbleUpAction && NaviWidgetI->HasParentNaviWidget())
	{
		NaviWidgetI = NaviWidgetI->GetParentNaviWidget();
		NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_Down, bBubbleUpAction);
		NaviWidgetI->OnInputDown();
	}
}

void UNaviWidgetSubsystem::InputLeft()
{
	if(!IsValid(CurrentNaviWidget))
	{
		ShowMessageInvalidCurrentNaviWidget();
		return;
	}
	
	UNaviWidget* NaviWidgetI = CurrentNaviWidget;
	bool bBubbleUpAction;
	NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_Left, bBubbleUpAction);
	NaviWidgetI->OnInputLeft();
	while(bBubbleUpAction && NaviWidgetI->HasParentNaviWidget())
	{
		NaviWidgetI = NaviWidgetI->GetParentNaviWidget();
		NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_Left, bBubbleUpAction);
		NaviWidgetI->OnInputLeft();
	}
}

void UNaviWidgetSubsystem::InputRight()
{
	if(!IsValid(CurrentNaviWidget))
	{
		ShowMessageInvalidCurrentNaviWidget();
		return;
	}
	
	UNaviWidget* NaviWidgetI = CurrentNaviWidget;
	bool bBubbleUpAction;
	NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_Right, bBubbleUpAction);
	NaviWidgetI->OnInputRight();
	while(bBubbleUpAction && NaviWidgetI->HasParentNaviWidget())
	{
		NaviWidgetI = NaviWidgetI->GetParentNaviWidget();
		NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_Right, bBubbleUpAction);
		NaviWidgetI->OnInputRight();
	}
}

void UNaviWidgetSubsystem::InputPageLeft()
{
	if(!IsValid(CurrentNaviWidget))
	{
		ShowMessageInvalidCurrentNaviWidget();
		return;
	}
	
	UNaviWidget* NaviWidgetI = CurrentNaviWidget;
	bool bBubbleUpAction;
	NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_PageLeft, bBubbleUpAction);
	NaviWidgetI->OnInputPageLeft();
	while(bBubbleUpAction && NaviWidgetI->HasParentNaviWidget())
	{
		NaviWidgetI = NaviWidgetI->GetParentNaviWidget();
		NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_PageLeft, bBubbleUpAction);
		NaviWidgetI->OnInputPageLeft();
	}
}

void UNaviWidgetSubsystem::InputPageRight()
{
	if(!IsValid(CurrentNaviWidget))
	{
		ShowMessageInvalidCurrentNaviWidget();
		return;
	}
	
	UNaviWidget* NaviWidgetI = CurrentNaviWidget;
	bool bBubbleUpAction;
	NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_PageRight, bBubbleUpAction);
	NaviWidgetI->OnInputPageRight();
	while(bBubbleUpAction && NaviWidgetI->HasParentNaviWidget())
	{
		NaviWidgetI = NaviWidgetI->GetParentNaviWidget();
		NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_PageRight, bBubbleUpAction);
		NaviWidgetI->OnInputPageRight();
	}
}

void UNaviWidgetSubsystem::DisplayCurrentNaviWidgetName()
{
	UE_LOG(NaviWidgetLog, Display, TEXT("Current Navi Widget: %s"), *CurrentNaviWidget->GetName());
}

void UNaviWidgetSubsystem::DisplayCurrentNaviWidgetPath()
{
	UE_LOG(NaviWidgetLog, Display, TEXT("%s"), *CurrentNaviWidget->GetName());
	UNaviWidget* Current = CurrentNaviWidget;
	while (Current->HasParentNaviWidget())
	{
		Current = Current->GetParentNaviWidget();
		UE_LOG(NaviWidgetLog, Display, TEXT("%s"), *Current->GetName());
	}
}


void UNaviWidgetSubsystem::ShowMessageInvalidCurrentNaviWidget()
{
	if (!IsValid(CurrentNaviWidget))
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("NavigateableWidgetSubsystem: No Current Widget Set. Call NavigateTo() to set the initial widget in focus."));
}




