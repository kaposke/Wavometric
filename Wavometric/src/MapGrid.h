#pragma once
#include <vector>
#include "ofMain.h"
#include "TileHandler.h"

using std::vector;

class MapGrid
{
private:
	int rows;
	int columns;
	float width;
	float height;

	vector< vector<int> > grid;
public:
	MapGrid(int rows, int columns, float width, float height);

	void setTile(int x,int y,int tile);

	void draw(TileHandler tilehandler);

	int getRows();
	int getColumns();

	int getTile(int x, int y);
};