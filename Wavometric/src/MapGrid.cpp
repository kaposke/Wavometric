#include "MapGrid.h"

MapGrid::MapGrid(int rows, int columns, float width, float height)
{
	this->rows = rows;
	this->columns = columns;
	this->width = width;
	this->height = height;

	grid.resize(columns, vector<int>(rows, -1));
}

void MapGrid::setTile(int x,int y,int tile)
{
	grid.at(y).at(x) = tile;
}

void MapGrid::draw(TileHandler tilehandler)
{
	float horizontalSize = width / columns;
	float verticalSize = height / rows;
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < columns; x++)
		{
			if(grid.at(y).at(x) != -1)
				tilehandler.getTile(grid.at(y).at(x)).draw(horizontalSize * x, verticalSize * y, horizontalSize, verticalSize);;
		}
	}
}

int MapGrid::getRows()
{
	return rows;
}

int MapGrid::getColumns()
{
	return columns;
}

int MapGrid::getTile(int x, int y)
{
	return grid.at(y).at(x);
}
