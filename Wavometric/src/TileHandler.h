#pragma once
#include "ofMain.h"
#include <vector>

class TileHandler
{
private:
	vector<ofImage> tiles;
public:
	TileHandler();

	void addTiles(ofImage tileMap, int horizontalTiles, int verticalTiles);

	ofImage getTile(int tile);

	int getTilesAmount();
};