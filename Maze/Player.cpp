#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;
	Pos pos = _pos;
	Pos dest = board->GetExitPos();

	// �������� ��Ģ
	//RightHandOnWall(_pos, dest);
	Bfs(pos, dest);
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())
		return;
	else {

		_sumTick += deltaTick;
		if (_sumTick >= _moveTick)
		{
			_sumTick = 0;

			_pos = _path[_pathIndex];
			cout <<"BFS / X : " << _pos.x << " Y : " << _pos.y;
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
		// ���� 
		// 1. ���� �ٶ󺸴� ������ �������� ���������� �� �� �ִ��� Ȯ���Ѵ�
		// 1-1. ���Ͻ�, ������ �������� 90�� ȸ�� �� �� ������
		// 1-2. �����Ͻ� 2������.
		// 2. ���� �ٶ󺸴� ���� �������� ������ �� �ִ��� Ȯ��.
		// 2-1. ���Ͻ� ������ �Ѻ� ����.
		// 2-2. �����Ͻ� 3������.
		// 3. �������� 90�� ȸ��,
		// ���� ���� ����.

		// ���� enum Dir �� ������� �ݽð�������� ���ư��Ƿ� �Ʒ��Ͱ��� ȸ��
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		if (CanGo(pos + front[newDir]))	// ������ ȸ�� �� ����
		{
			_dir = newDir;
			pos += front[newDir];
			_path.push_back(pos);
		}
		else if (CanGo(pos + front[_dir])) // ����
		{
			pos += front[_dir];
			_path.push_back(pos);
		}
		else {	// �������� 90�� ȸ��
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
	// 1. ó�� �湮�� ���� ť�� �־��ְ� �߰� check,
	// 2. ���� ������ ���鼭 ��ȸ�Ѵ�. �����¿� �� �� �ֳ� üũ 
	// 2-1. �� �� ������ continue.
	// 2-2. �̹� �߰��� �����̸� continue.
	// 3. bfs��ȸ �� ���������� break �ϰ� parent�� ������ �Ͽ� ����.
	const int32 size = _board->GetSize();
	vector<vector<bool>> discovered(size, vector<bool>(size,false));
	map<Pos, Pos> parent; // Parent[A] = [B] -> A�� �θ�� B�̴�.
	queue<Pos> q;

	q.push(pos);  // ó�� �湮�־��ְ�,
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
			// 2-1 ���� �ֳ� üũ
			if (CanGo(nextPos) == false) continue;
			// 2-2  �̹� �߰��߳� üũ
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
