#include "CustomAssetPrivatePCH.h"

DEFINE_LOG_CATEGORY(LogCustomAsset);

#define LOCTEXT_NAMESPACE "CustomAsset"

class FCustomAssetModule : public ICustomAssetModule
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

void FCustomAssetModule::StartupModule()
{
	UE_LOG(LogCustomAsset, Log, TEXT("Load Module: CustomAsset"));
}
void FCustomAssetModule::ShutdownModule()
{
	UE_LOG(LogCustomAsset, Log, TEXT("Unload Module: CustomAsset"));
}

IMPLEMENT_MODULE( FCustomAssetModule, ICustomAssetModule )

#undef LOCTEXT_NAMESPACE