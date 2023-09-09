#include "MainMenuScene.hpp"
#include "TextureAtlas.h"
#include "LayoutManager.h"
TextureAtlasManager* TextureAtlasManager::instance = nullptr;



/*GUIButton playBtn = GUIButton({300,150}, {100, 100}, "Start", BLUE, []() {
		
	});*/
void MainMenuScene::Load()
{
	//loading logic here
	TraceLog(LOG_DEBUG, __FUNCTION__);
	
	//LayoutManager::GetInstance()->AddElement(&playBtn);
	
}

void MainMenuScene::Update()
{
	// Update logic here
	
	
}

void MainMenuScene::Draw()
{
	// Draw logic here

	DrawText("GameName", 300, 100, 20, LIGHTGRAY);
	
	
	
	
}

void MainMenuScene::Unload()
{
	// Unload logic here
	TraceLog(LOG_DEBUG, "MainMenuScene::Unload");
}