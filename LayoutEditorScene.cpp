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

#include "TileMap.hpp"
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

TileMap* tileMapRender;

int selectedTileIndex = -1;

TileMap2 tm;
TileSet2 ts;

Viewport viewport;
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
	tileSetFlex = FlexRectCreateChild(flexChild1, 0.0f, 0.6f, 1.0f, 1.0f, 10, 10, 10, 10, 50, 30);

	atlas = TextureAtlasManager::GetInstance()->GetTexureAtlas("blueSheet");


	tileSet = TileSetNewInitFromFile("assets/tilemap_packed.png", 18, 18, NULL, 0);
	tileMap = TileMapNew();
	tileMap->tileSet = tileSet;
	tileMap->x = tileSetFlex->r.x;
	tileMap->y = tileSetFlex->r.y;

	tileMapRender = TileMapNew();
	tileMapRender->tileSet = tileSet;
	tileMapRender->x = flexDrawSpace->r.x;
	tileMapRender->y = flexDrawSpace->r.y;

	TileMapInitSize(tileMapRender, flexDrawSpace->r.w / 18, flexDrawSpace->r.h / 18);

	TileMapInitSize(tileMap, tileSetFlex->r.w/18, tileSetFlex->r.h/18);
	int tilesPerRow = 16; // Number of tiles per row in the tileset
	int tileindex = 0;
	for (int i = 0; i < tileMap->width * tileMap->height; i++) {
		if (tileindex < tileMap->tileSet->tileCount)
		{
			
			tileMap->grid[i] = tileindex;
			tileindex++;
		}
	}
	viewport = {
		0,
		0,
		flexDrawSpace->r.w / 18,
		flexDrawSpace->r.h / 18
	};
	ts = TileSet2("assets/tilemap_packed.png", 18, 18);
	tm = TileMap2(flexDrawSpace->r.x, flexDrawSpace->r.y, 200, flexDrawSpace->r.h / 18,  flexDrawSpace->r.w /18, flexDrawSpace->r.h /18,&ts, &viewport);
	
	for (int x = 0; x < tm.width ; x++)
	{
		for (int y = 0; y < tm.height; y++)
		{
			tm.grid[x][y] = GetRandomValue(0, 126);
		}
	}

}

void LayoutEditorScene::Update()
{
	// Update logic here
	// Check if the left mouse button was pressed
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		// Get the mouse coordinates
		int mouseX = GetMouseX();
		int mouseY = GetMouseY();

		// Calculate the grid position based on the mouse coordinates and tile size
		int tileX = (mouseX - tileMap->x) / tileSet->tileX;
		int tileY = (mouseY - tileMap->y) / tileSet->tileY;

		// Check if the click is within the bounds of the tilemap
		if (tileX >= 0 && tileX < tileMap->width && tileY >= 0 && tileY < tileMap->height)
		{
			// The user clicked on the tile at (tileX, tileY)
			// You can now perform actions based on this click.
			int gridIndex = tileY * tileMap->width + tileX;
			int tileIndex = tileMap->grid[gridIndex];
			// Perform actions with tileIndex or gridIndex as needed.
			TraceLog(LOG_INFO, "GridIndex %d , tileIndex %d", gridIndex, tileIndex);
			selectedTileIndex = tileIndex;
		}
	}
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		// Get the mouse coordinates
		int mouseX = GetMouseX();
		int mouseY = GetMouseY();

		// Calculate the grid position based on the mouse coordinates and tile size
		int tileX = (mouseX - tileMapRender->x) / tileSet->tileX;
		int tileY = (mouseY - tileMapRender->y) / tileSet->tileY;

		// Check if the click is within the bounds of the tilemap
		if (tileX >= 0 && tileX < tileMapRender->width && tileY >= 0 && tileY < tileMapRender->height)
		{
			// The user clicked on the tile at (tileX, tileY)
			// You can now perform actions based on this click.
			int gridIndex = tileY * tileMapRender->width + tileX;
			int tileIndex = tileMapRender->grid[gridIndex];
			// Perform actions with tileIndex or gridIndex as needed.
			TraceLog(LOG_INFO, "GridIndex %d , tileIndex %d", gridIndex, tileIndex);
			tileMapRender->grid[gridIndex] = selectedTileIndex;
		}
	}

	if (IsKeyDown(KEY_RIGHT))
	{
		if (viewport.x + viewport.width < tm.width)
		{
			viewport.x += 1;
		}
	}
	if (IsKeyDown(KEY_LEFT))
	{
		if (viewport.x > 0)
		{
			viewport.x -= 1;

		}
	}
	if (IsKeyDown(KEY_DOWN))
	{
		if (viewport.y + viewport.height < tm.height)
		{
			viewport.y += 1;
		}
	}
	if (IsKeyDown(KEY_UP))
	{
		if (viewport.y > 0)
		{
			viewport.y -= 1;
		}
	}

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
		//DrawRectangleLines(flexDrawSpace->r.x, flexDrawSpace->r.y, flexDrawSpace->r.w, flexDrawSpace->r.h, BLUE);


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
	TileMapDrawExWorld(tileMap, (int)tileSetFlex->r.x, (int)tileSetFlex->r.y, tileSetFlex->r.w, tileSetFlex->r.h);
	//TileMapDrawGrid(tileMapRender, BLACK);
	//TileMapDrawExWorld(tileMapRender, (int)flexDrawSpace->r.x, (int)flexDrawSpace->r.y, flexDrawSpace->r.w, flexDrawSpace->r.h);
	//DrawRectangleLines(cam.x, cam.y, cam.w, cam.h, GREEN);
	tm.DrawGrid(BLACK);
	tm.Draw();


}

void LayoutEditorScene::Unload()
{
	// Unload logic here
	TraceLog(LOG_DEBUG, "LayoutEditorScene::Unload");
}

