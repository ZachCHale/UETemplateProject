// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameUserSettings.h"

#include "Kismet/BlueprintTypeConversions.h"
#include "Kismet/KismetSystemLibrary.h"

UMyGameUserSettings::UMyGameUserSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AudioVolumeEffects = 1.0f;
	AudioVolumeMusic = 1.0f;
	AudioVolumeMaster = 1.0f;
	
	TArray<FIntPoint> SupportedResolutions;
	bool suc = UKismetSystemLibrary::GetSupportedFullscreenResolutions(SupportedResolutions);
	if(!suc || SupportedResolutions.Num() == 0)
	{
		DefaultResolutionX = 1920;
		DefaultResolutionY = 1080;
		return;
	}
	FIntPoint MaxRes = SupportedResolutions[0];
	for (auto Resolution : SupportedResolutions)
	{
		if(Resolution.Size() > MaxRes.Size())
			MaxRes = Resolution;
	}
	DefaultResolutionX = MaxRes.X;
	DefaultResolutionY = MaxRes.Y;
}

UMyGameUserSettings* UMyGameUserSettings::GetMyGameUserSettings()
{
	return Cast<UMyGameUserSettings>(UGameUserSettings::GetGameUserSettings());
}

void UMyGameUserSettings::SetAudioVolumeMaster(float NewValue)
{
	AudioVolumeMaster = NewValue;
	if(OnAudioUINeedsRedraw.IsBound())
		OnAudioUINeedsRedraw.Broadcast();
}

void UMyGameUserSettings::SetAudioVolumeMusic(float NewValue)
{
	AudioVolumeMusic = NewValue;
	if(OnAudioUINeedsRedraw.IsBound())
		OnAudioUINeedsRedraw.Broadcast();
}

void UMyGameUserSettings::SetAudioVolumeEffects(float NewValue)
{
	AudioVolumeEffects = NewValue;
	if(OnAudioUINeedsRedraw.IsBound())
		OnAudioUINeedsRedraw.Broadcast();
}

void UMyGameUserSettings::SetAudioVolumesToDefault()
{
	AudioVolumeEffects = 1.0f;
	AudioVolumeMusic = 1.0f;
	AudioVolumeMaster = 1.0f;
	if(OnAudioUINeedsRedraw.IsBound())
		OnAudioUINeedsRedraw.Broadcast();
}

FIntPoint UMyGameUserSettings::GetDefaultResolution()
{
	return FIntPoint(DefaultResolutionX, DefaultResolutionY);
}

float UMyGameUserSettings::GetAudioVolumeMaster() const
{
	return  AudioVolumeMaster;
}

float UMyGameUserSettings::GetAudioVolumeMusic() const
{
	return AudioVolumeMusic;
}

float UMyGameUserSettings::GetAudioVolumeEffects() const
{
	return AudioVolumeEffects;
}
