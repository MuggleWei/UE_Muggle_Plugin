#include "CustomAssetEditorPrivatePCH.h"
#include "CustomAssetObjFactory.h"
#include "CustomAssetClasses.h"

#define LOCTEXT_NAMESPACE "CustomAssetEditor"

UCustomAssetObjFactory::UCustomAssetObjFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UCustomAssetObj::StaticClass();
}

UObject* UCustomAssetObjFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
    UCustomAssetObj* NewObjectAsset = NewObject<UCustomAssetObj>(InParent, Class, Name, Flags | RF_Transactional);
	return NewObjectAsset;
}

#undef LOCTEXT_NAMESPACE