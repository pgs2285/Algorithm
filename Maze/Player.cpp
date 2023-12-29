#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;
	Pos pos = _pos;
	Pos dest = board->GetExitPos();

	// 오른손의 법칙
	//RightHandOnWall(_pos, dest);
	//Bfs(pos, dest);
	AStar(_pos, dest);
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())
	{

		return;
	}
		//return;
	else {
		
		_sumTick += deltaTick;
		if (_sumTick >= _moveTick)
		{
			_sumTick = 0;

			_pos = _path[_pathIndex];
			_pathIndex++;
		}

	}
}

void Player::RightHandOnWall(Pos pos, Pos dest)
{
	Pos front[4] =
	{
		Pos { -1, 0 }, // up
		Pos { 0, -1 }, // left
		Pos { 1, 0 }, // down
		Pos { 0, 1}, // right
	};
	_path.clear();
	_path.push_back(pos);
	while (pos != dest)
	{
		// 로직 
		// 1. 현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는지 확인한다
		// 1-1. 참일시, 오른쪽 방향으로 90도 회전 후 한 보전진
		// 1-2. 거짓일시 2번으로.
		// 2. 현재 바라보는 방향 기준으로 전진할 수 있는지 확인.
		// 2-1. 참일시 앞으로 한보 전진.
		// 2-2. 거짓일시 3번으로.
		// 3. 왼쪽으로 90도 회전,
		// 이후 무한 루프.

		// 현재 enum Dir 은 순서대로 반시계방향으로 돌아가므로 아래와같이 회전
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		if (CanGo(pos + front[newDir]))	// 오른쪽 회전 후 전진
		{
			_dir = newDir;
			pos += front[newDir];
			_path.push_back(pos);
		}
		else if (CanGo(pos + front[_dir])) // 전진
		{
			pos += front[_dir];
			_path.push_back(pos);
		}
		else {	// 왼쪽으로 90도 회전
			_dir = (_dir + 1) % DIR_COUNT;
		}
	}
	stack<Pos> s;
	for (int i = 0; i < _path.size() - 1; i++)
	{
		if (s.empty() == false && s.top() == _path[i + 1])
		{
			s.pop();
		}
		else s.push(_path[i]);
	}

	if (_path.empty() == false)
	{
		s.push(_path.back());
	}

	vector<Pos> path;
	while (s.empty() == false)
	{
		path.push_back(s.top());
		s.pop();
	}
	std::reverse(path.begin(), path.end());
	_path = path;
}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);
	return tileType == TileType::EMPTY;
}

void Player::Bfs(Pos pos, Pos dest)
{
	Pos front[4] =
	{
		Pos { -1, 0 }, // up
		Pos { 0, -1 }, // left
		Pos { 1, 0 }, // down
		Pos { 0, 1}, // right
	};
	_path.clear();
	_path.push_back(pos);
	// bfs
	// 1. 처음 방문한 곳을 큐에 넣어주고 발견 check,
	// 2. 무한 루프를 돌면서 순회한다. 상하좌우 갈 수 있나 체크 
	// 2-1. 갈 수 없으면 continue.
	// 2-2. 이미 발견한 지역이면 continue.
	// 3. bfs순회 후 도착했으면 break 하고 parent를 역참조 하여 간다.
	const int32 size = _board->GetSize();
	vector<vector<bool>> discovered(size, vector<bool>(size,false));
	map<Pos, Pos> parent; // Parent[A] = [B] -> A의 부모는 B이다.
	queue<Pos> q;

	q.push(pos);  // 처음 방문넣어주고,
	discovered[pos.y][pos.x] = true;
	parent[pos] = pos;

	while (q.empty() == false)
	{
		pos = q.front();
		q.pop();

		if (pos == dest) 
			break;

		for (int dir = 0; dir < 4; dir++)
		{
			Pos nextPos = pos + front[dir];
			// 2-1 갈수 있나 체크
			if (CanGo(nextPos) == false) continue;
			// 2-2  이미 발견했나 체크
			if (discovered[nextPos.y][nextPos.x]) continue;

			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			parent[nextPos] = pos;
		}
		_path.clear();
		pos = dest;
		while (true)
		{
			_path.push_back(pos);

			if (pos == parent[pos]) break;
			pos = parent[pos];
		}
		std::reverse(_path.begin(), _path.end());
	}
}

struct PQNode
{
	bool operator<(const PQNode& other) const { return f < other.f; }
	bool operator>(const PQNode& other) const { return f > other.f; }
	int32 f;
	int32 g;
	Pos pos;
};

void Player::AStar(Pos pos, Pos dest)
{

// 점수 매기기
// F = G + H
// F = 최종점수 (작을수록 좋다)
// G = 시작점에서 해당좌표까지 이동하는데 드는 비용 (작을수록 좋다)
// H = 목적지에서 얼마나 가까운지 (작을수록 좋음)
// 1. 예약 시스템 구현
// 2. 뒤늦게 더 좋은 경로가 발견될 수 있다.
	Pos start = pos;
	Pos front[] =
	{
		Pos {-1, 0},
		Pos{0,-1},
		Pos{1,0},
		Pos{0,1},
		Pos{-1,-1},
		Pos{1,-1},
		Pos{1,1},
		Pos{-1,1}
	};

	int32 cost[] =
	{
		10,
		10,
		10,
		10,
		14,
		14,
		14,
		14
	}; // 이동하는데 드는 비용, 위 front와 match
	const int8 DIR_COUNT = 4;
	const int32 size = _board->GetSize(); 
	vector<vector<bool>> closed(size, vector<bool>(size, false));
	//best[y][x] -> 지금까지 (y,x)에 대한 가장 좋은 비용
	vector<vector<int32>> best(size, vector<int32>(size, INT32_MAX));
	// 부모 추적 용도
	map<Pos, Pos> parent;
	//openlist
	priority_queue<PQNode, vector<PQNode>, std::greater<PQNode>> pq;
	{//초기설정
		int32 g = 0; //시작할때는 0값(이동안했으니)
		int32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x)); // 임의로 정해준 h공식
		// h는 나중에 피타고라스등 여러방법으로 구해줘도 됨.
		pq.push(PQNode{ g + h, g, start });

		best[start.y][start.x] = g + h;
		parent[start] = start;
	}
	
	while (pq.empty() == false)
	{
		// 제일 좋은 후보 찾기
		PQNode node = pq.top();
		pq.pop();

		// 동일한 좌표를 여러 경로로 찾아서 더 빠른경로로 인해 이미 방문된 경우 스킵.
		if (best[node.pos.y][node.pos.x] < node.f) continue;
		if (closed[node.pos.y][node.pos.x]) continue;
		if (node.pos == dest) break;
		// 이미 방문을 했는데 더 빠른경로가 있을수는 없다.(수학적으로 증명이 되어있음)
		closed[node.pos.y][node.pos.x] = true;
		for (int i = 0; i < DIR_COUNT; ++i)
		{
			Pos nextPos = node.pos + front[i];
			//갈수있는 지역
			if (CanGo(nextPos) == false) continue;
			if (closed[nextPos.y][nextPos.x]) continue;
			int32 g = node.g + cost[i];
			int32 h = 10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));

			// 다른경로에서 더 빠른길을 찾았으면 스킵
			if (best[nextPos.y][nextPos.x] <= g + h) continue;
			best[nextPos.y][nextPos.x] = g + h;
			pq.push(PQNode{ g + h, h, nextPos });
			parent[nextPos] = node.pos;
		}

	}
	_path.clear();
	Pos __pos = dest;
	while (true)
	{
		_path.push_back(__pos);

		if (__pos == parent[__pos]) break;
		__pos = parent[__pos];
	}
	std::reverse(_path.begin(), _path.end());

}



