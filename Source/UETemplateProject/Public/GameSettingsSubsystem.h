﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "GameSettingsSubsystem.generated.h"


UENUM(BlueprintType)
enum class ESoundClassCategory : uint8
{
	ESCC_Master,
	ESCC_Music,
	ESCC_Effects,
};

DECLARE_LOG_CATEGORY_EXTERN(GameSettingsLog, Log, All);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSettingsUINeedsRedrawDelegate);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScreenModeChangedDelegate, EWindowMode::Type, NewScreenMode);

/**
 * 
 */
UCLASS()
class UETEMPLATEPROJECT_API UGameSettingsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable)
	void SetResolutionByKey(FString Key);
	UFUNCTION(BlueprintCallable)
	TMap<FString, FIntPoint> GetResolutionOptions();
	UFUNCTION(BlueprintCallable)
	FIntPoint GetCurrentResolution();
	UFUNCTION(BlueprintCallable)
	void SetDisplaySettingsToDefault();
	UFUNCTION(BlueprintCallable)
	void ApplyDisplaySettings();
	UFUNCTION(BlueprintCallable)
	bool DoesDisplaySettingsNeedConfirmation();
	UFUNCTION(BlueprintCallable)
	void RevertDisplayToLastConfirmed();
	UFUNCTION(BlueprintCallable)
	void ConfirmDisplaySettings();
	UFUNCTION(BlueprintCallable)
	EWindowMode::Type GetCurrentWindowMode();
	UFUNCTION(BlueprintCallable)
	void SaveSettings();
	UFUNCTION(BlueprintCallable)
	FIntPoint GetMaxResolution();
	
	UFUNCTION(BlueprintCallable)
	void SetAudioSettingsToDefault();
	UFUNCTION(BlueprintCallable)
	void ApplyAudioSettings();
	UFUNCTION(BlueprintCallable)
	void SetScreenMode(EWindowMode::Type WindowMode);
	UFUNCTION(BlueprintCallable)
	void ReloadLastSavedSettings();
	
	UFUNCTION(BlueprintCallable)
	void SetAudioVolume(USoundMix* SoundMix, USoundClass* SoundClass, float Volume, ESoundClassCategory SoundClassCategory);
	UFUNCTION(BlueprintCallable)
	float GetCurrentAudioVolume(ESoundClassCategory SoundClassCategory);

	UFUNCTION(BlueprintCallable)
	void SetCurrentLanguage(FString LanguageKey);

	UFUNCTION(BlueprintCallable)
	FString GetCurrentLanguage();

	UFUNCTION(BlueprintCallable)
	void SetCurrentLanguageToDefault();

	UFUNCTION(BlueprintCallable)
	TMap<FString, FString> GetLanguageOptions();

	UFUNCTION(BlueprintCallable)
	void SetVSyncEnabled(bool bIsEnabled);

	UFUNCTION(BlueprintCallable)
	bool GetIsVSyncEnabled();

	UFUNCTION(BlueprintCallable)
	void SetFramerateLimit(float NewLimit);
	
	UFUNCTION(BlueprintCallable)
	float GetFramerateLimit();
	
	UPROPERTY(BlueprintAssignable)
	FSettingsUINeedsRedrawDelegate OnSettingsUINeedsRedraw;

	//UFUNCTION(BlueprintCallable)
	//void ChangeKeyBind(UEnhancedInputUserSettings* InputUserSettings);

	//UPROPERTY(BlueprintAssignable)
	//FScreenModeChangedDelegate OnScreenModeChanged;
private:
	void SetResolution(FIntPoint NewResolution);
	void CreateResolutionKeyMappings();
	void CreateLanguageKeyMappings();


	TMap<FString, FIntPoint> ResolutionMap;

	TMap<FString, FString> LanguageMap;
	
	FIntPoint LastConfirmedResolution;
	EWindowMode::Type LastConfirmedWindowMode;

	bool bHasUnsavedDisplayChanges;
};