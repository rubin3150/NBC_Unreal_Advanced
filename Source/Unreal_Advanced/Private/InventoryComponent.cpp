#include "InventoryComponent.h"

void AInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	FItemData Item1;
	Item1.ItemName = TEXT("HP 포션");
	Item1.ItemID = 1;
	Item1.ItemTitle = FName(TEXT("용사"));

	FItemData Item2;
	Item2.ItemName = TEXT("MP 포션");
	Item2.ItemID = 2;
	Item2.ItemTitle = FName(TEXT("마법사"));

	FItemData Item3;
	Item3.ItemName = TEXT("분노의 물약");
	Item3.ItemID = 3;
	Item3.ItemTitle = FName(TEXT("광전사"));

	FItemData Item4;
	Item4.ItemName = TEXT("연막탄");
	Item4.ItemID = 4;
	Item4.ItemTitle = FName(TEXT("도적"));

	FItemData Item5;
	Item5.ItemName = TEXT("수리검");
	Item5.ItemID = 5;
	Item5.ItemTitle = FName(TEXT("도적"));
	
	// 최초 아이템 추가
	AddItem(Item1);
	AddItem(Item2);
	AddItem(Item3);
	AddItem(Item4);
	AddItem(Item5);
	
	// 아이템 수량 증가
	AddItem(Item2);
	AddItem(Item2);
	AddItem(Item4);
	
	UE_LOG(LogTemp, Warning, TEXT("===== 칭호 없이 사용 시도 ====="));
	CanUseItem(Item1);
	CanUseItem(Item2);
	CanUseItem(Item3);
	CanUseItem(Item4);
	CanUseItem(Item5);
	
	UE_LOG(LogTemp, Warning, TEXT("===== 칭호 획득 ====="));
	AddTitle(FName(TEXT("용사")));
	AddTitle(FName(TEXT("도적")));
	AddTitle(FName(TEXT("도적"))); // 중복으로 한번 더 시도
	
	UE_LOG(LogTemp, Warning, TEXT("===== 칭호 획득 후 사용 시도 ====="));
	CanUseItem(Item1);
	CanUseItem(Item2);
	CanUseItem(Item3);
	CanUseItem(Item4);
	CanUseItem(Item5);
	CanUseItem(Item5); // 한번 더 시도
	
	// 아이템 정보 조회
	PrintItemInfo(1);
	PrintItemInfo(2);
	PrintItemInfo(3);
	PrintItemInfo(4);
	PrintItemInfo(5);
}

void AInventoryComponent::AddItem(FItemData& Item)
{
    if (ItemMap.Contains(Item.ItemID))
    {
        ItemMap[Item.ItemID]->Count++;
        UE_LOG(LogTemp, Warning, TEXT("%s 수량 증가: 총 %d개"), *Item.ItemName, ItemMap[Item.ItemID]->Count);
        return;
    }

    TSharedPtr<FItemData> NewItem = MakeShared<FItemData>(Item);
    Inventory.Add(NewItem);
    ItemMap.Add(Item.ItemID, NewItem);
    UE_LOG(LogTemp, Warning, TEXT("아이템 추가 / 이름: %s ID: %d"), *Item.ItemName, Item.ItemID);
}

void AInventoryComponent::AddTitle(FName Title)
{
	if (ItemTitles.Contains(Title))
	{
		UE_LOG(LogTemp, Warning, TEXT("(%s)는 이미 보유한 칭호입니다. 더이상 얻을 수 없습니다."), *Title.ToString());
		return;
	}
	
	ItemTitles.Add(Title);
	UE_LOG(LogTemp, Warning, TEXT("칭호 획득: (%s)"), *Title.ToString());
}

bool AInventoryComponent::CanUseItem(FItemData& Item)
{
	bool bCan = ItemTitles.Contains(Item.ItemTitle);
	if (bCan)
	{
		if (ItemMap[Item.ItemID]->Count <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("X %s 수량이 부족합니다."), *Item.ItemName);
			return false;
		}

		ItemMap[Item.ItemID]->Count--;
		UE_LOG(LogTemp, Warning, TEXT("O %s 사용 / 남은 수량: %d개"), *Item.ItemName, ItemMap[Item.ItemID]->Count);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("X %s 사용 불가 / (%s) 칭호 필요"), *Item.ItemName, *Item.ItemTitle.ToString());
	}

	return bCan;
}

void AInventoryComponent::PrintItemInfo(int32 ItemID)
{
	if (!ItemMap.Contains(ItemID))
		return;

	TSharedPtr<FItemData> Item = ItemMap[ItemID];
	UE_LOG(LogTemp, Warning, TEXT("===== 아이템 정보 ====="));
	UE_LOG(LogTemp, Warning, TEXT("이름: %s"), *Item->ItemName);
	UE_LOG(LogTemp, Warning, TEXT("ID: %d"), Item->ItemID);
	UE_LOG(LogTemp, Warning, TEXT("필요 칭호: %s"), *Item->ItemTitle.ToString());
	UE_LOG(LogTemp, Warning, TEXT("수량: %d"), Item->Count);
}