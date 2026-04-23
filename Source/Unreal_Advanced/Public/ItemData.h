#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString ItemName;

	UPROPERTY(EditAnywhere)
	int32 ItemID;

	UPROPERTY(EditAnywhere)
	FName ItemTitle;
	
	UPROPERTY(EditAnywhere)
	int32 Count = 1;
};