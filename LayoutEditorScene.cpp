#define NEZ_FLEXRECT_IMPLEMENTATION
#include "LayoutEditorScene.hpp"
#include "TextureAtlas.h"
#include "LayoutManager.h"
#include "flexrect.h"

//todo : rewrite flexrect in oop



NezRect_i rect;

FlexRect* windowRect; // main window
FlexRect* flexChild1; // side bar
FlexRect* button1Rect; // maybe load button ?
FlexRect* button2Rect; // maybe save button ?
FlexRect* lineSep; // simple verical bar ? Perhaps category separator ?

void LayoutEditorScene::Load()
{
	//loading logic here
	TraceLog(LOG_DEBUG, __FUNCTION__);
	rect = { 0, 0, 800, 450 };
	windowRect = FlexRectNew(&rect, 0.0f, 0.0f, 1.0f, 1.0f, 0, 0, 0, 0, 0, 0);
	flexChild1 = FlexRectCreateChild(windowRect, 0.0f, 0.0f, 0.4f, 1.0f, 0, 0, 0, 0, 50, 300);
	button1Rect = FlexRectCreateChild(flexChild1, 0.0f, 0.0f, 0.5f, 0.1f, 10, 10, 10, 10, 50, 30);
	button2Rect = FlexRectCreateChild(flexChild1, 0.5f, 0.0f, 1.0f, 0.1f, 10, 10, 10, 10, 50, 30);
	lineSep = FlexRectCreateChild(flexChild1, 0.0f, 0.1f, 1.0f, 0.0001f, 0, 20, 0, 20, 50, 30);


}

void LayoutEditorScene::Update()
{
	// Update logic here


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



	}




}

void LayoutEditorScene::Unload()
{
	// Unload logic here
	TraceLog(LOG_DEBUG, "LayoutEditorScene::Unload");
}