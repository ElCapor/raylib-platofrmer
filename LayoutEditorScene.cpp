#define NEZ_FLEXRECT_IMPLEMENTATION
#define RAYGUI_IMPLEMENTATION
#pragma warning(disable:4996)
#include "LayoutEditorScene.hpp"
#include "TextureAtlas.h"
#include "LayoutManager.h"
#include "flexrect.h"
#define NEZ_TILEMAP_IMPLEMENTATION
#define NEZ_TILESET_IMPLEMENTATION
#include "tilemap.h"
//todo : rewrite flexrect in oop
#include "raygui.h"


NezRect_i rect;

FlexRect* windowRect; // main window
FlexRect* flexChild1; // side bar
FlexRect* button1Rect; // maybe load button ?
FlexRect* button2Rect; // maybe save button ?
FlexRect* lineSep; // simple verical bar ? Perhaps category separator ?
FlexRect* lineSepLabel; // trick to center the label a bit more	
FlexRect* tileSetFlex; // the one containing the tiles
FlexRect* flexDrawSpace;// draw space for the map

TextureAtlas atlas;


TileSet* tileSet;
TileMap* tileMap;
void LayoutEditorScene::Load()
{
	//loading logic here
	TraceLog(LOG_DEBUG, __FUNCTION__);
	rect = { 0, 0, 800, 450 };
	windowRect = FlexRectNew(&rect, 0.0f, 0.0f, 1.0f, 1.0f, 0, 0, 0, 0, 0, 0);
	flexChild1 = FlexRectCreateChild(windowRect, 0.0f, 0.0f, 0.4f, 1.0f, 0, 0, 0, 0, 50, 300);
	flexDrawSpace = FlexRectCreateChild(windowRect, 0.4f, 0.0f, 1.0f, 1.0f, 10, 10, 10, 10, 150, 300);
	button1Rect = FlexRectCreateChild(flexChild1, 0.0f, 0.0f, 0.5f, 0.1f, 10, 10, 10, 10, 50, 30);
	button2Rect = FlexRectCreateChild(flexChild1, 0.5f, 0.0f, 1.0f, 0.1f, 10, 10, 10, 10, 50, 30);
	lineSep = FlexRectCreateChild(flexChild1, 0.0f, 0.1f, 1.0f, 0.0001f, 0, 20, 0, 20, 50, 30);
	lineSepLabel = FlexRectCreateChild(lineSep, 0.25f, 0.0f, 0.75f, 0, 0, 0, 0, 0, 50, 30);
	tileSetFlex = FlexRectCreateChild(flexChild1, 0.0f, 0.2f, 1.0f, 1.0f, 10, 10, 10, 10, 50, 30);

	atlas = TextureAtlasManager::GetInstance()->GetTexureAtlas("blueSheet");


	tileSet = TileSetNewInitFromFile("assets/tilemap_packed.png", 16, 16, NULL, 0);
	tileMap = TileMapNew();
	tileMap->tileSet = tileSet;
	tileMap->x = flexDrawSpace->r.x;
	tileMap->y = flexDrawSpace->r.y;
	TileMapInitSize(tileMap, flexDrawSpace->r.h, flexDrawSpace->r.w);
}

void LayoutEditorScene::Update()
{
	// Update logic here


}

Rectangle NezRect_iToRectangle(NezRect_i nezRect) {
	Rectangle raylibRect;
	raylibRect.x = (float)nezRect.x;
	raylibRect.y = (float)nezRect.y;
	raylibRect.width = (float)nezRect.w;
	raylibRect.height = (float)nezRect.h;
	return raylibRect;
}

void LayoutEditorScene::Draw()
{
	// Draw logic here

	if (windowRect) {
		DrawRectangleLines(windowRect->r.x, windowRect->r.y, windowRect->r.w, windowRect->r.h, RED);
		DrawRectangleLines(flexChild1->r.x, flexChild1->r.y, flexChild1->r.w, flexChild1->r.h, RED);
		DrawRectangleLines(button1Rect->r.x, button1Rect->r.y, button1Rect->r.w, button1Rect->r.h, RED);
		DrawRectangleLines(button2Rect->r.x, button2Rect->r.y, button2Rect->r.w, button2Rect->r.h, RED);
		DrawRectangleLines(lineSep->r.x, lineSep->r.y, lineSep->r.w, lineSep->r.h, RED);
		DrawRectangleLines(tileSetFlex->r.x, tileSetFlex->r.y, tileSetFlex->r.w, tileSetFlex->r.h, RED);
		DrawRectangleLines(flexDrawSpace->r.x, flexDrawSpace->r.y, flexDrawSpace->r.w, flexDrawSpace->r.h, RED);


		//DrawRectangleLines(lineSepLabel->r.x, lineSepLabel->r.y, lineSepLabel->r.w, lineSepLabel->r.h, RED);

	}
	if (GuiButton(NezRect_iToRectangle(button1Rect->r), "Load"))
	{
		
	}

	if (GuiButton(NezRect_iToRectangle(button2Rect->r), "Save"))
	{

	}

	if (GuiLabel(NezRect_iToRectangle(lineSepLabel->r), "Layout Editor"))
	{

	}

	TileMapDrawGrid(tileMap, BLACK);

	


}

void LayoutEditorScene::Unload()
{
	// Unload logic here
	TraceLog(LOG_DEBUG, "LayoutEditorScene::Unload");
}