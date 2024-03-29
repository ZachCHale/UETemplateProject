// Fill out your copyright notice in the Description page of Project Settings.


#include "NaviWidget.h"

#include "NaviWidgetSubsystem.h"
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

	naviWidgets.Insert(current, 0);
	while (current->HasParentNaviWidget()) {
		current = current->GetParentNaviWidget();
		naviWidgets.Insert(current, 0);
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
	SetParent(NewParent);
}

void UNaviWidget::NavigateTo()
{
	GetWorld()->GetSubsystem<UNaviWidgetSubsystem>()->NavigateTo(this);
}

void UNaviWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(bIsParentSetExplicitly)
		return;
	
	UObject* Parent = GetParent();
	UObject* Outer = GetOuter();
	if(IsValid(Parent))
	{
		TryParentingTo(Parent);
	}else if(IsValid(Parent))
	{
		TryParentingTo(Outer);
	}
}

void UNaviWidget::DisplayNaviPath()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("|Display NaviPath|"));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, FString::Printf(TEXT(" ^ %s"), *this->GetName()));
	UNaviWidget* CurrentParent = GetParentNaviWidget();
	while (IsValid(CurrentParent))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Orange, FString::Printf(TEXT(" ^ %s"), *CurrentParent->GetName()));
		CurrentParent = CurrentParent->GetParentNaviWidget();
	}

}

void UNaviWidget::DisplayAutomatedNaviPath()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("|Display AutomatedNaviPath|"));
	DisplayFullPath(this);

}

void UNaviWidget::DisplayFullPath(UObject* Object)
{
	UWidget* AsWidget = Cast<UWidget>(Object);
	UObject* nextParent = nullptr;
	UObject* nextOuter = Object->GetOuter();
	if(IsValid(AsWidget))
	{
		UNaviWidget* AsNaviWidget = Cast<UNaviWidget>(Object);
		if(IsValid(AsNaviWidget))
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT(" !^! NW:  %s"), *Object->GetName()));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, FString::Printf(TEXT("  ^  UW:  %s"), *Object->GetName()));
		}
		nextParent = AsWidget->GetParent();
	}else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("^ UO: %s"), *Object->GetName()));
	}
	if(IsValid(nextParent))
	{
		DisplayFullPath(nextParent);
	}else if(IsValid(nextOuter))
	{
		DisplayFullPath(nextOuter);
	}
}

void UNaviWidget::TryParentingTo(UObject* Object)
{
	UWidget* AsWidget = Cast<UWidget>(Object);
	UObject* nextParent = nullptr;
	UObject* nextOuter = Object->GetOuter();
	if(IsValid(AsWidget))
	{
		UNaviWidget* AsNaviWidget = Cast<UNaviWidget>(Object);
		if(IsValid(AsNaviWidget))
		{
			SetParent(AsNaviWidget);
			return;
		}
		nextParent = AsWidget->GetParent();
	}
	if(IsValid(nextParent))
	{
		TryParentingTo(nextParent);
	}else if(IsValid(nextOuter))
	{
		TryParentingTo(nextOuter);
	}
}

void UNaviWidget::SetParent(UNaviWidget* Parent)
{
	//TODO: Add check to make sure there are no NaviWidget Loops then display error.
	
	ParentNaviWidget = Parent;
}



