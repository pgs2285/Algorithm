#include "pch.h"
#include "Player.h"
#include "ConsoleHelper.h"
#include "DisjointSet.h"
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
    GenerateMap_Prim();
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

// Binary Tree �̷� ���� �˰���
void Board::GenerateMap_Kruskal()
{
    struct CostEdge
    {
        int cost;
        Pos u;
        Pos v;

        bool operator<(CostEdge& other)
        {
            return cost < other.cost;
        }
    };
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
    std::vector<CostEdge> edges;
    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {
            if (x % 2 == 0 || y % 2 == 0)
                continue;
            if (x < _size - 2)
            {
                const int32 randomValue = ::rand() % 100;
                edges.push_back(CostEdge{ randomValue, Pos{y, x}, Pos{y, x + 2} });
            }
            if (y < _size - 2)
            {
                const int32 randomValue = ::rand() % 100;
                edges.push_back(CostEdge{ randomValue, Pos{y, x}, Pos{y + 2, x} });
            }

        }
    }
        std::sort(edges.begin(), edges.end());

        DisjointSet sets(_size * _size);
        for (CostEdge& edge : edges)
        {
            int u = edge.u.y * _size + edge.u.x; // 2���� xy�� 1���� ���� 
            int v = edge.v.y * _size + edge.v.x;
            if(sets.Find(u) == sets.Find(v))
                continue;
            sets.Merge(u,v);
            int _y = (edge.u.y + edge.v.y) / 2;
            int x = (edge.v.x + edge.u.x) / 2;
            _tile[_y][x] = TileType::EMPTY;
        }
    }
void Board::GenerateMap_Prim()
{
    struct CostEdge
    {
        int cost;
        Pos vtx;

        bool operator<(const CostEdge& other) const
        {
            return cost < other.cost;
        }
    };

    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {
            if (x % 2 == 0 || y % 2 == 0)
            {
                _tile[y][x] = TileType::WALL;
            }
            else _tile[y][x] = TileType::EMPTY;
        }
    }

    map<Pos, vector<CostEdge>> edges;
    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {
            if (x % 2 == 0 || y % 2 == 0)
                continue;
            if (x < _size - 2)
            {
                const int32 randomValue = ::rand() % 100;
                Pos u = Pos{ y,x };
                Pos v = Pos{ y, x + 2 };
                edges[u].push_back(CostEdge{ randomValue, v });
                edges[v].push_back(CostEdge{ randomValue, u });
            }
            if (y < _size - 2)
            {
                const int32 randomValue = ::rand() % 100;
                Pos u = Pos{ y,x };
                Pos v = Pos{ y + 2, x };
                edges[u].push_back(CostEdge{ randomValue, v });
                edges[v].push_back(CostEdge{ randomValue, u });
            }

        }
    } // �����ĺ� ����

    // �ش� ������ Ʈ���� ���ԵǾ� �ִ°�
    map<Pos, bool> added;
    //� ������ ������ ���� ����Ǿ� �ִ°�
    map<Pos, Pos> parent;
    // ����� �ִ� Ʈ���� ������ ���� ��, ��� ������ ��� �ּ� ������ ����
    map<Pos, int32> best;

    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {
            best[Pos{ y,x }] = INT32_MAX;
            added[Pos{ y,x }] = false;
        }
    }

    priority_queue<CostEdge> pq;
    const Pos startPos = Pos{ 1,1 };// ��������
    pq.push(CostEdge{ 0, startPos });
    best[startPos] = 0;
    parent[startPos] = startPos;

    while (pq.empty() == false)
    {
        CostEdge bestEdge = pq.top();
        pq.pop();

        //���� ����� ����
        Pos v = bestEdge.vtx;
        if (added[v])
            continue;
        added[v] = true;
        {
            int y = (parent[v].y + v.y) / 2;
            int x = (parent[v].x + v.x) / 2;
            _tile[y][x] == TileType::EMPTY;
        }

        for (CostEdge& edge : edges[v]) // pop�� ������ ��� ���� �˻�
        {
            if (added[edge.vtx])
                continue; // ����Ŭ ����
            if (edge.cost > best[edge.vtx])
                continue;

            best[edge.vtx] = edge.cost;
            parent[edge.vtx] = v;
            pq.push(edge);
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
