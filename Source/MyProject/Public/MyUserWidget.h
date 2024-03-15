// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestInstObject.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class MYPROJECT_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(Instanced, BlueprintReadWrite, EditAnywhere)
	TArray<TObjectPtr<UTestInstObject>> testArray;
};
