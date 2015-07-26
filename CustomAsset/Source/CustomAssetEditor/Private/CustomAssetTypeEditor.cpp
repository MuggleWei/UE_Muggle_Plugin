#include "CustomAssetEditorPrivatePCH.h"
#include "CustomAssetClasses.h"
#include "CustomAssetTypeEditor.h"
#include "SDockTab.h"

#define LOCTEXT_NAMESPACE "CustomAssetEditor"

const FName CustomAssetTypeEditorAppName = FName(TEXT("SpriteEditorApp"));

struct FCustomAssetEditorTabs
{
	// Tab identifiers
	static const FName TreeID;
	static const FName ViewportID;
	static const FName PropertyID;
};

const FName FCustomAssetEditorTabs::TreeID(TEXT("TreeView"));
const FName FCustomAssetEditorTabs::ViewportID(TEXT("Viewport"));
const FName FCustomAssetEditorTabs::PropertyID(TEXT("Property"));

void FCustomAssetTypeEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager)
{
	WorkspaceMenuCategory = TabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_CustomAssetEditor", "Custom Asset Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(TabManager);

	TabManager->RegisterTabSpawner(FCustomAssetEditorTabs::TreeID, FOnSpawnTab::CreateSP(this, &FCustomAssetTypeEditor::SpawnTab_Tree))
		.SetDisplayName( LOCTEXT("TreeViewTabLabel", "Tree View") )
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.ContentBrowser"));

	TabManager->RegisterTabSpawner(FCustomAssetEditorTabs::ViewportID, FOnSpawnTab::CreateSP(this, &FCustomAssetTypeEditor::SpawnTab_Viewport))
		.SetDisplayName( LOCTEXT("ViewportTab", "Viewport") )
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Viewports"));

	TabManager->RegisterTabSpawner(FCustomAssetEditorTabs::PropertyID, FOnSpawnTab::CreateSP(this, &FCustomAssetTypeEditor::SpawnTab_Property))
		.SetDisplayName( LOCTEXT("PropertyTabLabel", "Property") )
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));
}
void FCustomAssetTypeEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(TabManager);

	TabManager->UnregisterTabSpawner(FCustomAssetEditorTabs::TreeID);
	TabManager->UnregisterTabSpawner(FCustomAssetEditorTabs::ViewportID);
	TabManager->UnregisterTabSpawner(FCustomAssetEditorTabs::PropertyID);
}

FName FCustomAssetTypeEditor::GetToolkitFName() const
{
	return FName("CusttomAssetTypeEditor");
}
FText FCustomAssetTypeEditor::GetBaseToolkitName() const
{
	return LOCTEXT("CustomAssetTypeEditorAppLabel", "Custtom Asset Editor");
}
FText FCustomAssetTypeEditor::GetToolkitName() const
{
	const bool bDirtyState = CustomAssetBeingEdited->GetOutermost()->IsDirty();

	FFormatNamedArguments Args;
	Args.Add(TEXT("AssetName"), FText::FromString(CustomAssetBeingEdited->GetName()));
	Args.Add(TEXT("DirtyState"), bDirtyState ? FText::FromString( TEXT( "*" ) ) : FText::GetEmpty());
	return FText::Format(LOCTEXT("CustomAssetTypeEditorAppLabel", "{SpriteName}{DirtyState}"), Args);
}
FLinearColor FCustomAssetTypeEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}
FString FCustomAssetTypeEditor::GetWorldCentricTabPrefix() const
{
	return TEXT("CustomAssetTypeEditor");
}
FString FCustomAssetTypeEditor::GetDocumentationLink() const
{
	return TEXT("null");
}
void FCustomAssetTypeEditor::OnToolkitHostingStarted(const TSharedRef<class IToolkit>& Toolkit)
{}
void FCustomAssetTypeEditor::OnToolkitHostingFinished(const TSharedRef<class IToolkit>& Toolkit)
{}

void FCustomAssetTypeEditor::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(CustomAssetBeingEdited);
}

void FCustomAssetTypeEditor::InitEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class UCustomAssetObj* InitAssetObj)
{
	CustomAssetBeingEdited = InitAssetObj;

	TSharedPtr<FCustomAssetTypeEditor> EditorPtr = SharedThis(this);

	// Default layout
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_CustomAssetTypeEditor_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->SetHideTabWell(true)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Horizontal)
				->SetSizeCoefficient(0.9f)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.8f)
					->SetHideTabWell(true)
					->AddTab(FCustomAssetEditorTabs::ViewportID, ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewSplitter()
					->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.2f)
					->Split
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(0.75f)
						->SetHideTabWell(true)
						->AddTab(FCustomAssetEditorTabs::TreeID, ETabState::OpenedTab)
					)
					->Split
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(0.25f)
						->AddTab(FCustomAssetEditorTabs::PropertyID, ETabState::OpenedTab)
					)
				)
			)
		);

	// Initialize the asset editor
	InitAssetEditor(Mode, InitToolkitHost, CustomAssetTypeEditorAppName, StandaloneDefaultLayout, /*bCreateDefaultStandaloneMenu=*/ true, /*bCreateDefaultToolbar=*/ true, InitAssetObj);
}

TSharedRef<SDockTab> FCustomAssetTypeEditor::SpawnTab_Viewport(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.Label(LOCTEXT("ViewportTab_Title", "Viewport"))
		[
			SNew(SOverlay)
		];
}
TSharedRef<SDockTab> FCustomAssetTypeEditor::SpawnTab_Tree(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.Label(LOCTEXT("TreeViewTab_Title", "Tree"))
		[
			SNew(SOverlay)
		];
}
TSharedRef<SDockTab> FCustomAssetTypeEditor::SpawnTab_Property(const FSpawnTabArgs& Args)
{
	// Spawn the tab
	return SNew(SDockTab)
		.Label(LOCTEXT("PropertyTab_Title", "Property"))
		[
			SNew(SOverlay)
		];
}


#undef LOCTEXT_NAMESPACE