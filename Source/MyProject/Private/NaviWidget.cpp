// Fill out your copyright notice in the Description page of Project Settings.


#include "NaviWidget.h"

#include "NavigateableWidgetsSubsystem.h"
#include "Components/PanelWidget.h"

void UNaviWidget::DoesActionBubbleUp_Implementation(ENaviWidgetActionType ActionType, bool& bDoesBubbleUp)
{
	bDoesBubbleUp = false;
}

void UNaviWidget::OnNavigatedTo()
{
	OnNavigatedToBP();
	if(OnNavigatedToFinished.IsBound())
		OnNavigatedToFinished.Broadcast(this);
}

void UNaviWidget::OnNavigatedIn()
{
	OnNavigatedInBP();
	if(OnNavigatedInFinished.IsBound())
		OnNavigatedInFinished.Broadcast(this);
}

void UNaviWidget::OnNavigatedOut()
{
	OnNavigatedOutBP();
	if(OnNavigatedOutFinished.IsBound())
		OnNavigatedOutFinished.Broadcast(this);
}

bool UNaviWidget::HasParentNaviWidget()
{
	return IsValid(ParentNaviWidget);
}

UNaviWidget* UNaviWidget::GetParentNaviWidget()
{
	if(IsValid(ParentNaviWidget))
		return ParentNaviWidget;
	return nullptr;
}

TArray<UNaviWidget*> UNaviWidget::GetNaviWidgetsFromRootToThis()
{
	TArray<UNaviWidget*> naviWidgets;
	UNaviWidget* current = this;
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("%s"), *this->GetName()));

	naviWidgets.Insert(current, 0);
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Magenta, FString::Printf(TEXT("Added %s"), *current->GetName()));
	while (current->HasParentNaviWidget()) {
		current = current->GetParentNaviWidget();
		naviWidgets.Insert(current, 0);
		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Magenta, FString::Printf(TEXT("Added %s"), *current->GetName()));
	}

	for (auto NaviWidget : naviWidgets)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, FString::Printf(TEXT("Added %s"), *NaviWidget->GetName()));
	}


	return naviWidgets;
}

void UNaviWidget::SetParentNaviWidgetExplicit(UNaviWidget* NewParent)
{
	if(bIsParentSetExplicitly)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, FString::Printf(TEXT("SetParentNaviWidgetExplicit is called multiple times on %s. This is not recommended, input will only bubble up the last set parent."), *this->GetName()));
	}
	bIsParentSetExplicitly = true;
	ParentNaviWidget = NewParent;
}

void UNaviWidget::NavigateTo()
{
	GetWorld()->GetSubsystem<UNavigateableWidgetsSubsystem>()->NavigateTo(this);
}

void UNaviWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(bIsParentSetExplicitly)
		return;
	UObject* ParentObject = GetOuter();
	while (IsValid(ParentObject))
	{
		if(ParentObject->IsA(UNaviWidget::StaticClass()))
		{
			ParentNaviWidget = Cast<UNaviWidget>(ParentObject);
			break;
		}
		ParentObject = ParentObject->GetOuter();
	}
}

