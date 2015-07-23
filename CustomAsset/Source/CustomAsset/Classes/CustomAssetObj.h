#pragma once

#include "CustomAssetObj.generated.h"

UCLASS(Blueprintable)
class CUSTOMASSET_API UCustomAssetObj : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Properties")
	FString Name;
};