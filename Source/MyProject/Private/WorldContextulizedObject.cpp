// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldContextulizedObject.h"

UWorld* UWorldContextulizedObject::GetWorld() const {
    UObject* outer = GetOuter();
    if (outer && (outer->IsA<AActor>() || outer->IsA<UWidget>() || outer->IsA<UWorldContextulizedObject>()) && !outer->HasAnyFlags(RF_ClassDefaultObject)) {
        return outer->GetWorld();
    }
    return nullptr;
}