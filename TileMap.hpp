// C++ Rewrite
// major change : the grid is treated as a 2d array
#ifndef TILEMAP_HPP
#define TILEMAP_HPP
#include <raylib.h>
#include "TileSet.hpp"


// should i consider x and y as grid indices or of world pos ?
typedef struct {
	int x;
	int y;
	int width;
	int height;
} Viewport; //abstract class to render grid

class Grid {
	int** self;

	Grid()
	{
		self = nullptr;
	}

	Grid(int width, int height)
	{
		self = new int* [width];
		for (int i = 0; i < width; ++i) {
			self[i] = new int[height];
		}
	}
};

// working on a breaking change now
// trying to use viewport to render a part of the grid , which's size can be
// bigger than the flex layout
class TileMap2 {
public:
	int** grid;
	TileSet2* tileSet;
	int x;
	int y;
	int width;
	int height;
	int gridH;
	int gridW;
	

	Viewport* view;

	TileMap2()
	{
		width = 0;
		height = 0;
		x = 0;
		y = 0;
		grid = nullptr;
		view = nullptr;
		tileSet = nullptr;
	}

	TileMap2(int x, int y, int width, int height, int W, int H, TileSet2* tileSet, Viewport* viewport)
	{
		this->width = width;
		this->height = height;
		// 2d grid
		grid = new int* [width];
		for (int i = 0; i < width; ++i) {
			grid[i] = new int[height];
		}
		this->x = x;
		this->y = y;
		this->tileSet = tileSet;
		this->view = viewport;
		gridW = W;
		gridH = H;
	}

	void DrawGrid(Color color)
	{
		int x = this->x;
		int y = this->y;
		int w = this->gridW;
		int h = this->gridH;
		int sx = this->tileSet->tileX;
		int sy = this->tileSet->tileY;
		int lenX = w * sx;
		int lenY = h * sy;
		// horizontal lines
		for (int i = 0; i < h + 1; i++)
		{
			DrawLine(x, y + sy * i, x + lenX, y + sy * i, color);
		}
		// vertical lines
		for (int i = 0; i < w + 1; i++)
		{
			DrawLine(x + sx * i, y, x + sx * i, y + lenY, color);
		}
	}


	void Draw()
	{
		int w = this->view->width;
		int h = this->view->height;
		int px = this->x;
		int py = this->y;
		int sx = this->tileSet->tileX;
		int sy = this->tileSet->tileY;
		int xoffset = view->x;
		int yoffset = view->y;
		for (int ty = 0; ty < h; ty++)
		{
			for (int tx = 0; tx < w; tx++)
			{
				int id = this->grid[tx + xoffset][ty + yoffset];
				if (id > -1)
				{
					//TileSetDrawTile(this->tileSet, id, px + x * sx, py + y * sy);
					this->tileSet->DrawTile(id, px + tx * sx, py + ty * sy);
				}
			}
		}
	}

	int**& Grid()
	{
		return grid;
	}
	
	int GetTile(int gridX, int gridY)
	{
		if (gridX < 0 || gridY < 0 || gridX > width - 1 || gridY > height - 1)
		{
			return -1;
		}
		return grid[gridX][gridY];

	}
};
#endif // !TILEMAP_HPP
