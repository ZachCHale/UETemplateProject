// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TestInstObject.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct MYPROJECT_API FTestInstObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText MyText;
};
