// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameUserSettings.h"

UMyGameUserSettings::UMyGameUserSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AudioVolumeEffects = 1.0f;
	AudioVolumeMusic = 1.0f;
	AudioVolumeMaster = 1.0f;
}

UMyGameUserSettings* UMyGameUserSettings::GetMyGameUserSettings()
{
	return Cast<UMyGameUserSettings>(UGameUserSettings::GetGameUserSettings());
}

void UMyGameUserSettings::SetAudioVolumeMaster(float NewValue)
{
	AudioVolumeMaster = NewValue;
}

void UMyGameUserSettings::SetAudioVolumeMusic(float NewValue)
{
	AudioVolumeMusic = NewValue;
}

void UMyGameUserSettings::SetAudioVolumeEffects(float NewValue)
{
	AudioVolumeEffects = NewValue;
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
