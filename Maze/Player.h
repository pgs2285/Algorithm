#pragma once

class Board;

class Player
{
public:
	void Init(Board* board);
	void Update(uint64 deltaTick);
	void SetPos(Pos pos) { _pos = pos; }
	Pos GetPos() { return _pos; }

	void RightHandOnWall(Pos _pos, Pos dest);
	bool CanGo(Pos pos);
private:
	Pos _pos = {};
	int32 _dir = DIR_UP;
	Board* _board = nullptr;

	vector<Pos> _path;
	int32 _pathIndex = 0;

	int32 _moveTick = 100;
	uint64 _sumTick = 0;
	
};

