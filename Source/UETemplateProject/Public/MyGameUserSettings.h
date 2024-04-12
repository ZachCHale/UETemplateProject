// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "MyGameUserSettings.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAudioUINeedsRedrawDelegate);

/**
 * 
 */
UCLASS()
class UETEMPLATEPROJECT_API UMyGameUserSettings : public UGameUserSettings
{
	GENERATED_UCLASS_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static UMyGameUserSettings* GetMyGameUserSettings();
	
	UFUNCTION(BlueprintPure)
	float GetAudioVolumeMaster() const;
	UFUNCTION(BlueprintPure)
	float GetAudioVolumeMusic() const;
	UFUNCTION(BlueprintPure)
	float GetAudioVolumeEffects() const;
	UFUNCTION(BlueprintCallable)
	void SetAudioVolumeMaster(float NewValue);
	UFUNCTION(BlueprintCallable)
	void SetAudioVolumeMusic(float NewValue);
	UFUNCTION(BlueprintCallable)
	void SetAudioVolumeEffects(float NewValue);
	UFUNCTION(BlueprintCallable)
	void SetAudioVolumesToDefault();
	
	UPROPERTY(BlueprintAssignable)
	FAudioUINeedsRedrawDelegate OnAudioUINeedsRedraw;
	
	FIntPoint GetDefaultResolution();

	bool GetDefaultVSync();

protected:
	UPROPERTY(Config)
	float AudioVolumeMaster;
	UPROPERTY(Config)
	float AudioVolumeMusic;
	UPROPERTY(Config)
	float AudioVolumeEffects;
	UPROPERTY(Config)
	int32 DefaultResolutionX;
	UPROPERTY(Config)
	int32 DefaultResolutionY;
	UPROPERTY(Config)
	bool bDefaultVSync;

};
