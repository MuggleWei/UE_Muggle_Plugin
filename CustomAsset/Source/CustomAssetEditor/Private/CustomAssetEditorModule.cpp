#include "CustomAssetEditorPrivatePCH.h"
#include "CustomAssetTypeActions.h"
#include "ModuleManager.h"
#include "AssetToolsModule.h"

DEFINE_LOG_CATEGORY(LogCustomAssetEditor);

#define LOCTEXT_NAMESPACE "CustomAssetEditor"

class FCustomAssetEditorModule : public ICustomAssetEditorModule
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

    EAssetTypeCategories::Type CustomAssetCategoryBit;
    TArray< TSharedPtr<IAssetTypeActions> > CreatedCustomAssetTypeActions;
};

void FCustomAssetEditorModule::StartupModule()
{
    UE_LOG(LogCustomAssetEditor, Log, TEXT("Load Module: CustomAssetEditor"));

    // Register asset types
    IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

    CustomAssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("CustomAsset")), LOCTEXT("CustomAssetCategory", "CustomAsset"));

    TSharedRef<IAssetTypeActions> action = MakeShareable(new FCustomAssetTypeActions(CustomAssetCategoryBit));
    AssetTools.RegisterAssetTypeActions(action);
    CreatedCustomAssetTypeActions.Add(action);
}
void FCustomAssetEditorModule::ShutdownModule()
{
    UE_LOG(LogCustomAssetEditor, Log, TEXT("Unload Module: CustomAssetEditor"));

    // Unregister all the asset types that we registered
    if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
    {
        IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
        for (int32 Index = 0; Index < CreatedCustomAssetTypeActions.Num(); ++Index)
        {
            AssetTools.UnregisterAssetTypeActions(CreatedCustomAssetTypeActions[Index].ToSharedRef());
        }
    }
    CreatedCustomAssetTypeActions.Empty();
}

IMPLEMENT_MODULE( FCustomAssetEditorModule, CustomAssetEditor )

#undef LOCTEXT_NAMESPACE