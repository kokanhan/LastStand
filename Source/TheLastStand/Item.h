#pragma once

#include "CoreMinimal.h"
#include "Item.generated.h"

USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(BlueprintReadOnly)
	int id;
	UPROPERTY(BlueprintReadOnly)
	FString name;
	UPROPERTY(BlueprintReadOnly)
	int type;
	UPROPERTY(BlueprintReadOnly)
	int count;
	UPROPERTY(BlueprintReadOnly)
	FString url;
};