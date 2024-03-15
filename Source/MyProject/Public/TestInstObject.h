// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TestInstObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType,DefaultToInstanced, EditInlineNew)
class MYPROJECT_API UTestInstObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText MyText;
};
