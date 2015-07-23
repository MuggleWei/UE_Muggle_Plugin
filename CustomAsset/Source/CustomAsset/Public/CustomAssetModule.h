#pragma once
#include "ModuleManager.h"

class ICustomAssetModule : public IModuleInterface
{
public:
	static inline ICustomAssetModule& Get()
	{
		return FModuleManager::LoadModuleChecked< ICustomAssetModule >( "CustomAsset" );
	}
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded( "CustomAsset" );
	}
};