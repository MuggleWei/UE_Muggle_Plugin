#pragma once
#include "ModuleManager.h"

class ICustomAssetEditorModule : public IModuleInterface
{
public:
	static inline ICustomAssetEditorModule& Get()
	{
		return FModuleManager::LoadModuleChecked< ICustomAssetEditorModule >( "CustomAssetEditor" );
	}
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded( "CustomAssetEditor" );
	}
};