#include "CustomAssetEditorPrivatePCH.h"
#include "CustomAssetTypeActions.h"
#include "CustomAssetObj.h"
#include "CustomAssetTypeEditor.h"

#define LOCTEXT_NAMESPACE "CustomAssetEditor"

FCustomAssetTypeActions::FCustomAssetTypeActions(EAssetTypeCategories::Type InAssetCategory)
	: MyAssetCategory(InAssetCategory)
{
}

FText FCustomAssetTypeActions::GetName() const
{
	return LOCTEXT("FCustomAssetTypeActionsName", "Custom Asset");
}

FColor FCustomAssetTypeActions::GetTypeColor() const
{
	return FColor(129, 196, 115);
}

UClass* FCustomAssetTypeActions::GetSupportedClass() const
{
	return UCustomAssetObj::StaticClass();
}

void FCustomAssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		if (UCustomAssetObj* customAssetObj = Cast<UCustomAssetObj>(*ObjIt))
		{
			TSharedRef<FCustomAssetTypeEditor> NewCustomAssetEditor(new FCustomAssetTypeEditor());
			NewCustomAssetEditor->InitEditor(Mode, EditWithinLevelEditor, customAssetObj);
		}
	}
}

uint32 FCustomAssetTypeActions::GetCategories()
{
	return MyAssetCategory;
}

#undef LOCTEXT_NAMESPACE