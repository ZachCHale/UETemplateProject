// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSettingsSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameUserSettings.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY(GameSettingsLog);


void UGameSettingsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CreateResolutionKeyMappings();
	UMyGameUserSettings* UserSettings = UMyGameUserSettings::GetMyGameUserSettings();
	LastConfirmedResolution = UserSettings->GetLastConfirmedScreenResolution();
	LastConfirmedWindowMode = UserSettings->GetLastConfirmedFullscreenMode();
}

void UGameSettingsSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UGameSettingsSubsystem::SetResolutionByKey(FString Key)
{
	if(!ResolutionMap.Contains(Key))
		return;
	SetResolution(*ResolutionMap.Find(Key));
}

TMap<FString, FIntPoint> UGameSettingsSubsystem::GetResolutionOptions()
{
	return ResolutionMap;
}

FIntPoint UGameSettingsSubsystem::GetCurrentResolution()
{
	return UMyGameUserSettings::GetMyGameUserSettings()->GetScreenResolution();
}

void UGameSettingsSubsystem::SetDisplaySettingsToDefault()
{
	UMyGameUserSettings* UserSettings = UMyGameUserSettings::GetMyGameUserSettings();
	UserSettings->SetFullscreenMode(UserSettings->GetDefaultWindowMode());
	UserSettings->SetScreenResolution(UserSettings->GetDefaultResolution());
	UserSettings->SetVSyncEnabled(UserSettings->GetDefaultVSync());
	UserSettings->ValidateSettings();

	OnSettingsUINeedsRedraw.Broadcast();
}

void UGameSettingsSubsystem::ApplyDisplaySettings()
{
	UMyGameUserSettings* UserSettings = UMyGameUserSettings::GetMyGameUserSettings();
	UserSettings->ApplyNonResolutionSettings();
	UserSettings->ApplyResolutionSettings(false);
	bHasUnsavedDisplayChanges = false;
}

bool UGameSettingsSubsystem::DoesDisplaySettingsNeedConfirmation()
{
	UMyGameUserSettings* UserSettings = UMyGameUserSettings::GetMyGameUserSettings();
	FIntPoint CurResolution = UserSettings->GetScreenResolution();
	EWindowMode::Type CurScreenMode = UserSettings->GetFullscreenMode();
	FIntPoint ConfirmedResolution = LastConfirmedResolution;
	EWindowMode::Type ConfirmedScreenMode = LastConfirmedWindowMode;
	return CurResolution != ConfirmedResolution || CurScreenMode != ConfirmedScreenMode;
}

void UGameSettingsSubsystem::RevertDisplayToLastConfirmed()
{
	UMyGameUserSettings* UserSettings = UMyGameUserSettings::GetMyGameUserSettings();
	UserSettings->SetFullscreenMode(LastConfirmedWindowMode);
	UserSettings->SetScreenResolution(LastConfirmedResolution);
	UserSettings->ApplyResolutionSettings(false);
	UserSettings->SaveSettings();
	OnSettingsUINeedsRedraw.Broadcast();
}

void UGameSettingsSubsystem::ConfirmDisplaySettings()
{
	UMyGameUserSettings* UserSettings = UMyGameUserSettings::GetMyGameUserSettings();
	UserSettings->ConfirmVideoMode();
	UserSettings->SaveSettings();
	LastConfirmedWindowMode = UserSettings->GetLastConfirmedFullscreenMode();
	LastConfirmedResolution = UserSettings->GetLastConfirmedScreenResolution();
}

EWindowMode::Type UGameSettingsSubsystem::GetCurrentWindowMode()
{
	UMyGameUserSettings* UserSettings = UMyGameUserSettings::GetMyGameUserSettings();
	return UserSettings->GetFullscreenMode();
}

void UGameSettingsSubsystem::SaveSettings()
{
	UMyGameUserSettings* UserSettings = UMyGameUserSettings::GetMyGameUserSettings();
	UserSettings->SaveSettings();
}

FIntPoint UGameSettingsSubsystem::GetMaxResolution()
{
	UMyGameUserSettings* UserSettings = UMyGameUserSettings::GetMyGameUserSettings();

	TArray<FIntPoint> SupportedResolutions;
	bool suc = UKismetSystemLibrary::GetSupportedFullscreenResolutions(SupportedResolutions);
	if(!suc || SupportedResolutions.Num() == 0)
	{
		return UserSettings->GetDefaultResolution();
	}
	FIntPoint MaxRes = SupportedResolutions[0];
	for (auto Resolution : SupportedResolutions)
	{
		if(Resolution.Size() > MaxRes.Size())
			MaxRes = Resolution;
	}
	return MaxRes;
}

void UGameSettingsSubsystem::SetAudioSettingsToDefault()
{
	UMyGameUserSettings* UserSettings = UMyGameUserSettings::GetMyGameUserSettings();
	UserSettings->SetAudioVolumesToDefault();

	OnSettingsUINeedsRedraw.Broadcast();
}

void UGameSettingsSubsystem::ApplyAudioSettings()
{
	SaveSettings();
}

void UGameSettingsSubsystem::SetScreenMode(EWindowMode::Type WindowMode)
{
	bHasUnsavedDisplayChanges = true;
	UMyGameUserSettings* UserSettings = UMyGameUserSettings::GetMyGameUserSettings();
	UserSettings->SetFullscreenMode(WindowMode);

	OnSettingsUINeedsRedraw.Broadcast();
}

void UGameSettingsSubsystem::ReloadLastSavedSettings()
{
	UMyGameUserSettings* UserSettings = UMyGameUserSettings::GetMyGameUserSettings();
	UserSettings->LoadSettings();
	bHasUnsavedDisplayChanges = false;

	OnSettingsUINeedsRedraw.Broadcast();
}

void UGameSettingsSubsystem::SetAudioVolume(USoundMix* SoundMix, USoundClass* SoundClass, float Volume, ESoundClassCategory SoundClassCategory)
{
	UGameplayStatics::SetSoundMixClassOverride(this, SoundMix, SoundClass, Volume, 1, 0, true);
	UGameplayStatics::PushSoundMixModifier(this, SoundMix);
	UMyGameUserSettings* UserSettings = UMyGameUserSettings::GetMyGameUserSettings();
	switch(SoundClassCategory)
	{
	case ESoundClassCategory::ESCC_Master:
		UserSettings->SetAudioVolumeMaster(Volume);
		break;
	case ESoundClassCategory::ESCC_Music:
		UserSettings->SetAudioVolumeMusic(Volume);
		break;
	case ESoundClassCategory::ESCC_Effects:
		UserSettings->SetAudioVolumeEffects(Volume);
		break;
	}
}

float UGameSettingsSubsystem::GetCurrentAudioVolume(ESoundClassCategory SoundClassCategory)
{
	UMyGameUserSettings* UserSettings = UMyGameUserSettings::GetMyGameUserSettings();
	switch( SoundClassCategory) {
	case ESoundClassCategory::ESCC_Master:
		return UserSettings->GetAudioVolumeMaster();
		break;
	case ESoundClassCategory::ESCC_Music:
		return UserSettings->GetAudioVolumeMusic();
		break;
	case ESoundClassCategory::ESCC_Effects:
		return UserSettings->GetAudioVolumeEffects();
		break;
	default:
		return 0.0f;
	}
	
}

void UGameSettingsSubsystem::SetVSyncEnabled(bool bIsEnabled)
{
	UMyGameUserSettings* UserSettings = UMyGameUserSettings::GetMyGameUserSettings();
	UserSettings->SetVSyncEnabled(bIsEnabled);
	OnSettingsUINeedsRedraw.Broadcast();
}

bool UGameSettingsSubsystem::GetIsVSyncEnabled()
{
	return UMyGameUserSettings::GetMyGameUserSettings()->IsVSyncEnabled();
}

void UGameSettingsSubsystem::SetResolution(FIntPoint NewResolution)
{
	bHasUnsavedDisplayChanges = true;
	UMyGameUserSettings::GetMyGameUserSettings()->SetScreenResolution(NewResolution);
	
	OnSettingsUINeedsRedraw.Broadcast();
}

void UGameSettingsSubsystem::CreateResolutionKeyMappings()
{
	TArray<FIntPoint> SupportedResolutions;
	bool suc = UKismetSystemLibrary::GetSupportedFullscreenResolutions(SupportedResolutions);
	if(!suc)
	{
		UE_LOG(GameSettingsLog, Error, TEXT("Failed to gather supported resolutions"));
		return;
	}
	ResolutionMap.Empty();
	for (auto SupportedResolution : SupportedResolutions)
	{
		FString NewKey = FString::Printf(TEXT("%i X %i"), SupportedResolution.X, SupportedResolution.Y);
		ResolutionMap.Add(NewKey, SupportedResolution);
	}
}
