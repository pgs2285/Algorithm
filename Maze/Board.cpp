#include "pch.h"
#include "Player.h"
#include "ConsoleHelper.h"
#include "Board.h"



class Player;
Board::Board()
{
}

Board::~Board()
{
}

void Board::Init(int32 size, Player* player)
{
    _size = size;
    _player = player;
    GenerateMap();
    Render();
}

void Board::Render()
{

    ConsoleHelper::SetCursorPosition(0, 0);
    ConsoleHelper::ShowConsoleCursor(false);

    const char* TILE = "■";
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

// Binary Tree 미로 생성 알고리즘
void Board::GenerateMap()
{
    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {
            if (x % 2 == 0 || y % 2 == 0 )
            {
                _tile[y][x] = TileType::WALL;
            }
            else _tile[y][x] = TileType::EMPTY;
        }
    }

    // 랜덤으로 우측 혹은 아래로 길을 뚫는 작업.
    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {
            if (x % 2 == 0 || y % 2 == 0) continue;

            if (y == _size - 2 && x == _size - 2) continue;
                

            if (x == _size - 2) // 맨 밑줄 에서 한칸 띈것과 오른쪽한칸 띈곳은 길을 뚫도록
            {
                _tile[y + 1][x] = TileType::EMPTY;
                continue;
            }
            if (y == _size - 2)
            {
                _tile[y][x + 1] = TileType::EMPTY;
                continue;
            }
            
            int randValue = ::rand() % 2;
            if (randValue == 0)
            {
                _tile[y][x + 1] = TileType::EMPTY;
            }
            else {
                _tile[y + 1][x] = TileType::EMPTY;
            }
        }
    }
}

TileType Board::GetTileType(Pos pos)
{
    if (pos.x < 0 || pos.x >= _size)
        return TileType::NONE;
    if (pos.y < 0 || pos.y >= _size)
        return TileType::NONE;

    return _tile[pos.y][pos.x];
}

ConsoleColor Board::GetTileColor(Pos pos)
{
    if (_player && _player->GetPos() == pos)
        return ConsoleColor::YELLOW;

    if (GetExitPos() == pos) return ConsoleColor::BLUE;
    TileType tileType = GetTileType(pos);

    switch (tileType)
    {
    case TileType::EMPTY:
        return ConsoleColor::GREEN;

    case TileType::WALL:
        return ConsoleColor::RED;

    }

    return ConsoleColor::WHITE;
}
