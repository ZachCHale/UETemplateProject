// Fill out your copyright notice in the Description page of Project Settings.


#include "NavigateableWidgetsSubsystem.h"

void UNavigateableWidgetsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("NavigateableWidgetSubsystem: Initialized"));

}

void UNavigateableWidgetsSubsystem::Deinitialize()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("NavigateableWidgetSubsystem: Deinitialized"));
}

void UNavigateableWidgetsSubsystem::NavigateTo(UNaviWidget* TargetNaviWidget)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Navigate to %s"), *TargetNaviWidget->GetName()));


	if (!IsValid(CurrentNaviWidget))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("FIRST NAV"));

		CurrentNaviWidget = TargetNaviWidget;
		TArray<UNaviWidget*> NewNaviWidgetPath = TargetNaviWidget->GetNaviWidgetsFromRootToThis();

		for (auto NaviWidget : NewNaviWidgetPath)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("a"));

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
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Previous"));

		for (auto NaviWidgetPath : PrevNaviWidgetPath)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *NaviWidgetPath->GetName()));
		}
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("New"));

		for (auto NaviWidgetPath : NewNaviWidgetPath)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *NaviWidgetPath->GetName()));

		}

		
		for(int i = PrevNaviWidgetPath.Num()-1; i>=0; i--)
		{
			if(NewNaviWidgetPath.Num()>i)
			{
				if(PrevNaviWidgetPath[i] != NewNaviWidgetPath[i])
				{
					PrevNaviWidgetPath[i]->OnNavigatedOut();
					//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *PrevNaviWidgetPath[i]->GetName()));
					//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *NewNaviWidgetPath[i]->GetName()));


				}
			}else
			{
				PrevNaviWidgetPath[i]->OnNavigatedOut();
			//	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("2"));

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

void UNavigateableWidgetsSubsystem::InputSubmit()
{
	if(!IsValid(CurrentNaviWidget))
	{
		ShowMessageInvalidCurrentNaviWidget();
		return;
	}
	
	UNaviWidget* NaviWidgetI = CurrentNaviWidget;
	NaviWidgetI->OnInputSubmit();
	bool bBubbleUpAction;
	NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_Submit, bBubbleUpAction);
	while(bBubbleUpAction && NaviWidgetI->HasParentNaviWidget())
	{
		NaviWidgetI = NaviWidgetI->GetParentNaviWidget();
		NaviWidgetI->OnInputSubmit();
		NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_Submit, bBubbleUpAction);
	}
}

void UNavigateableWidgetsSubsystem::InputCancel()
{
	if(!IsValid(CurrentNaviWidget))
	{
		ShowMessageInvalidCurrentNaviWidget();
		return;
	}
	
	UNaviWidget* NaviWidgetI = CurrentNaviWidget;
	NaviWidgetI->OnInputCancel();
	bool bBubbleUpAction;
	NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_Cancel, bBubbleUpAction);
	while(bBubbleUpAction && NaviWidgetI->HasParentNaviWidget())
	{
		NaviWidgetI = NaviWidgetI->GetParentNaviWidget();
		NaviWidgetI->OnInputCancel();
		NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_Cancel, bBubbleUpAction);
	}
}

void UNavigateableWidgetsSubsystem::InputUp()
{
	if(!IsValid(CurrentNaviWidget))
	{
		ShowMessageInvalidCurrentNaviWidget();
		return;
	}

	UNaviWidget* NaviWidgetI = CurrentNaviWidget;
	NaviWidgetI->OnInputUp();
	bool bBubbleUpAction;
	NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_Up, bBubbleUpAction);
	while(bBubbleUpAction && NaviWidgetI->HasParentNaviWidget())
	{
		NaviWidgetI = NaviWidgetI->GetParentNaviWidget();
		NaviWidgetI->OnInputUp();
		NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_Up, bBubbleUpAction);
	}
}

void UNavigateableWidgetsSubsystem::InputDown()
{
	if(!IsValid(CurrentNaviWidget))
	{
		ShowMessageInvalidCurrentNaviWidget();
		return;
	}
	
	UNaviWidget* NaviWidgetI = CurrentNaviWidget;
	NaviWidgetI->OnInputDown();
	bool bBubbleUpAction;
	NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_Down, bBubbleUpAction);
	while(bBubbleUpAction && NaviWidgetI->HasParentNaviWidget())
	{
		NaviWidgetI = NaviWidgetI->GetParentNaviWidget();
		NaviWidgetI->OnInputDown();
		NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_Down, bBubbleUpAction);
	}
}

void UNavigateableWidgetsSubsystem::InputLeft()
{
	if(!IsValid(CurrentNaviWidget))
	{
		ShowMessageInvalidCurrentNaviWidget();
		return;
	}
	
	UNaviWidget* NaviWidgetI = CurrentNaviWidget;
	NaviWidgetI->OnInputLeft();
	bool bBubbleUpAction;
	NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_Left, bBubbleUpAction);
	while(bBubbleUpAction && NaviWidgetI->HasParentNaviWidget())
	{
		NaviWidgetI = NaviWidgetI->GetParentNaviWidget();
		NaviWidgetI->OnInputLeft();
		NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_Left, bBubbleUpAction);
	}
}

void UNavigateableWidgetsSubsystem::InputRight()
{
	if(!IsValid(CurrentNaviWidget))
	{
		ShowMessageInvalidCurrentNaviWidget();
		return;
	}
	
	UNaviWidget* NaviWidgetI = CurrentNaviWidget;
	NaviWidgetI->OnInputRight();
	bool bBubbleUpAction;
	NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_Right, bBubbleUpAction);
	while(bBubbleUpAction && NaviWidgetI->HasParentNaviWidget())
	{
		NaviWidgetI = NaviWidgetI->GetParentNaviWidget();
		NaviWidgetI->OnInputRight();
		NaviWidgetI->DoesActionBubbleUp(ENaviWidgetActionType::ENWAT_Right, bBubbleUpAction);
	}
}


void UNavigateableWidgetsSubsystem::ShowMessageInvalidCurrentNaviWidget()
{
	if (!IsValid(CurrentNaviWidget))
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("NavigateableWidgetSubsystem: No Current Widget Set. Call NavigateTo() to set the initial widget in focus."));
}




