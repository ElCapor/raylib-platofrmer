#include "MainMenuScene.hpp"
#include "TextureAtlas.h"
#include "LayoutManager.h"
TextureAtlasManager* TextureAtlasManager::instance = nullptr;


GUIButton playBtn;

void MainMenuScene::Load()
{
	//loading logic here
	TraceLog(LOG_DEBUG, __FUNCTION__);
	playBtn = GUIButton({ 300,150 }, { 160, 49 }, "Start", BLUE, [](GUIButton* self) {
		TraceLog(LOG_INFO, "I was clicked");
		});
	LayoutManager::GetInstance()->AddElement(&playBtn);
	
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