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
	RightHandOnWall(_pos, dest);
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
}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);
	return tileType == TileType::EMPTY;
}
