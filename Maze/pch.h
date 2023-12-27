#pragma once

#include <windows.h>
#include <iostream>
#include <vector>
#include <stack>
#include "Types.h"
#include <queue>
#include <map>
using namespace std;

struct Pos {

	// 연산자 오버로드를 통해 보다 편하게 좌표값을 비교, 계산할 수 있게 만든다.

	bool operator==(Pos& other)
	{
		return y == other.y && x == other.x;
	}

	bool operator!=(Pos& other)
	{
		return !(*this == other);
	}

	Pos operator+(Pos& other)
	{
		Pos ret;
		ret.x = x + other.x;
		ret.y = y + other.y;
		return ret;
	}

	Pos& operator+=(Pos& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	bool operator<(const Pos& other) const
	{
		if (y != other.y) return y < other.y;
		return x < other.x;
	}

	int32 y = 0;
	int32 x = 0;
};

enum Dir
{
	DIR_UP = 0,
	DIR_LEFT = 1,
	DIR_DOWN = 2,
	DIR_RIGHT = 3,
	DIR_COUNT = 4
};