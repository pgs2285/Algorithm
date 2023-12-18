#include "pch.h"
#include "ConsoleHelper.h"
#include "Board.h"

Board::Board()
{
}

Board::~Board()
{
}

void Board::Init(int32 size)
{
    _size = size;

    GenerateMap();
    Render();
}

void Board::Render()
{

    ConsoleHelper::SetCursorPosition(0, 0);
    ConsoleHelper::ShowConsoleCursor(false);



    const char* TILE = "��";

    for (int32 y = 0; y < _size; ++y)
    {
        for (int32 x = 0; x < _size; ++x)
        {
            ConsoleColor color = GetTileColor(Pos{ y,x });
            ConsoleHelper::SetCursorColor(color);
            cout << TILE;
        }
        cout << endl;
    }
}

void Board::GenerateMap()
{
    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {
            if (x == 0 || x == _size - 1 || y == 0; || y == _size - 1)
            {
                _tile[y][x] = TileType::WALL;
            }
            else _tile[y][x] = TileType::EMPTY;
        }
    }
}

TileType Board::GetTileType(Pos pos)
{
    if (pos.x < 0 || pos.x >= _size)
        return TileType::NONE;
    if (pos.y < 0 || pos.y >= _size)
        return TileType::NONE;

    return _tile[pos.y][pos.x]
}

ConsoleColor Board::GetTileColor(Pos pos)
{
    TileType tileType = GetTileType(pos);

    switch (tileType)
    {
    case TileType::NONE:
        return ConsoleColor::GREEN;

    case TileType::WALL:
        return ConsoleColor::RED;

    }

    return ConsoleColor::WHITE;
}
