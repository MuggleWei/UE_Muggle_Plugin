#include "CustomAssetEditorPrivatePCH.h"

DEFINE_LOG_CATEGORY(LogCustomAssetEditor);

#define LOCTEXT_NAMESPACE "CustomAssetEditor"

class FCustomAssetEditorModule : public ICustomAssetEditorModule
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

void FCustomAssetEditorModule::StartupModule()
{
    UE_LOG(LogCustomAssetEditor, Log, TEXT("Load Module: CustomAssetEditor"));
}
void FCustomAssetEditorModule::ShutdownModule()
{
    UE_LOG(LogCustomAssetEditor, Log, TEXT("Unload Module: CustomAssetEditor"));
}

IMPLEMENT_MODULE( FCustomAssetEditorModule, ICustomAssetEditorModule )

#undef LOCTEXT_NAMESPACE