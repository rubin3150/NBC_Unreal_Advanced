#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemData.h"
#include "InventoryComponent.generated.h"

UCLASS()
class UNREAL_ADVANCED_API AInventoryComponent : public AActor
{
	GENERATED_BODY()

public:
	TArray<TSharedPtr<FItemData>> Inventory;
	TMap<int32, TSharedPtr<FItemData>> ItemMap;
	TSet<FName> ItemTitles;

	void AddItem(FItemData& Item);
	void AddTitle(FName Title);
	bool CanUseItem(FItemData& Item);
	void PrintItemInfo(int32 ItemID);

protected:
	virtual void BeginPlay() override;
};