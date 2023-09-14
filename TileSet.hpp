// rewrite

#ifndef TILESET_H
#define TILESET_H
#include <raylib.h>
#include <filesystem>

namespace fs = std::filesystem;

class TileSet2 {
public:
	Texture2D texture; // spritesheet
	int tileX; // tile height;
	int tileY; // tile width
	int columns;
	int rows;
	int tileCount;
	TileSet2()
	{
		this->tileX = 0;
		this->tileY = 0;
		this->columns = 0;
		this->rows = 0;
		this->texture = Texture2D();
		this->tileCount = 0;
	}
	TileSet2(const char* wpath, int tileWidth, int tileHeight)
	{
		if (fs::exists(wpath))
		{
			this->texture = LoadTexture(wpath);
			tileX = tileWidth;
			tileY = tileHeight;
			columns = texture.width / tileWidth;
			rows = texture.height / tileHeight;
			tileCount = columns * rows;
		}
		else {
			TraceLog(LOG_ERROR, "Image path doesnt exist...");
		}
	}

	void DrawTile(int id, int x, int y)
	{
		int col = id % columns;
		int row = id / columns;
		Rectangle tileRect = { (float)col * this->tileX, (float)row * this->tileY, (float)this->tileX, (float)this->tileY };
		DrawTextureRec(this->texture, tileRect, { (float)x, (float)y }, WHITE);
	}


	
};

#endif