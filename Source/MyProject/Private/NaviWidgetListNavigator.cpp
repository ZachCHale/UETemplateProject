// Fill out your copyright notice in the Description page of Project Settings.


#include "NaviWidgetListNavigator.h"

void UNaviWidgetListNavigator::ResetToDefaultWidget()
{
	SelectedIndex = GetDefaultIndex();
	SelectedItem = GetDefaultItem();
}

int UNaviWidgetListNavigator::GetDefaultIndex()
{
	if(Items.IsEmpty())
		return 0;

	switch (DefaultBehavior) {
	case ENaviWidgetNavigatorDefaultBehavior::NWNDB_DefaultToFirst:
		return 0;
	case ENaviWidgetNavigatorDefaultBehavior::NWNDB_DefaultToLast:
		return Items.Num()-1;
	default :
		return 0;
	}
	
}

UNaviWidget* UNaviWidgetListNavigator::GetDefaultItem()
{
	if(Items.IsEmpty())
		return nullptr;

	return Items[GetDefaultIndex()];
}

void UNaviWidgetListNavigator::NavigateUp()
{
	Navigate(true);
}

void UNaviWidgetListNavigator::NavigateDown()
{
	Navigate(false);
}

void UNaviWidgetListNavigator::AddItem(UNaviWidget* NewItem)
{
	if(Items.Contains(NewItem))
		return;

	Items.Add(NewItem);
	NewItem->OnNavigatedToFinished.AddDynamic(this, &UNaviWidgetListNavigator::HandleExternalNavigation);
	NewItem->OnNavigatedInFinished.AddDynamic(this, &UNaviWidgetListNavigator::HandleExternalNavigation);
}

void UNaviWidgetListNavigator::AddItems(TArray<UNaviWidget*> NewItems)
{
	for (auto Item : NewItems)
	{
		AddItem(Item);	
	}
}

void UNaviWidgetListNavigator::ClearItems()
{
	for (auto Item : Items)
	{
		Item->OnNavigatedToFinished.RemoveDynamic(this,  &UNaviWidgetListNavigator::HandleExternalNavigation);
		Item->OnNavigatedInFinished.RemoveDynamic(this,  &UNaviWidgetListNavigator::HandleExternalNavigation);
	}
	Items.Empty();
}

void UNaviWidgetListNavigator::Navigate(bool bDirection)
{
	if(Items.IsEmpty())
		return;

	if(!IsValid(SelectedItem))
		ResetToDefaultWidget();

	int PreviousIndex = SelectedIndex;
	int NextIndex = bDirection ? PreviousIndex + 1 : PreviousIndex - 1;

	if(!Items.IsValidIndex(NextIndex))
		return;

	SelectedIndex = NextIndex;
	SelectedItem = Items[NextIndex];

	SelectedItem->NavigateTo();
}

void UNaviWidgetListNavigator::HandleExternalNavigation(UNaviWidget* NavigatedItem)
{
	
	if(!Items.Contains(NavigatedItem))
		return;
	SelectedItem = NavigatedItem;
	SelectedIndex = Items.Find(NavigatedItem);
	
}

