#include "TileHandler.h"

TileHandler::TileHandler()
{
}

void TileHandler::addTiles(ofImage tileMap, int horizontalTiles, int verticalTiles)
{
	float horizontalTileSize = tileMap.getWidth() / horizontalTiles;
	float verticalTileSize = tileMap.getHeight() / verticalTiles;
	ofImage currentTile;
	for (int y = 0; y < verticalTiles; y++)
	{
		for (int x = 0; x < horizontalTiles; x++)
		{
			currentTile.cropFrom(tileMap, x * horizontalTileSize, y * verticalTileSize, horizontalTileSize, verticalTileSize);
			tiles.push_back(currentTile);
		}
	}
}

ofImage TileHandler::getTile(int tile)
{
	return tiles[tile];
}

int TileHandler::getTilesAmount()
{
	return tiles.size();
}
