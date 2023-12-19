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
}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);
	return tileType == TileType::EMPTY;
}
