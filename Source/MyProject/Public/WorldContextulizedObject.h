#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/Widget.h"
#include "WorldContextulizedObject.generated.h"

/**
 * UWorldContextualizedObjects have access to libraries that require implementation of the GetWorld Function.
 * For example, a blueprint inheriting from UWorldContextulizedObject can use GetGameInstance.
 * The owner must be an Actor or a Widget or another valid UWorldContextulizedObject.
 */
UCLASS(BlueprintType, Blueprintable)
class MYPROJECT_API UWorldContextulizedObject : public UObject {
	GENERATED_BODY()
protected:
	/** Event when instance is created from class. */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Initialization"))
	void OnInit();
public:
	UWorldContextulizedObject() {
		OnInit();
	}
	UWorld* GetWorld() const;
};
