#pragma once

#include "UnrealEd.h"
#include "CustomAssetObjFactory.generated.h"

UCLASS()
class UCustomAssetObjFactory : public UFactory
{
	GENERATED_UCLASS_BODY()

	// UFactory interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	// End of UFactory interface
};