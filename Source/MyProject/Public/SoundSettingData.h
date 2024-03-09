// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Sound/SoundMix.h"
#include "SoundSettingData.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API USoundSettingData : public UDataAsset
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	FString SaveSlotKey;
	UPROPERTY(EditAnywhere)
	USoundClass* SoundClass;
	UPROPERTY(EditAnywhere)
	USoundMix* SoundMix;
	
};
