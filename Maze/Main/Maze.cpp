#include <iostream>
#include "pch.h"
#include "ConsoleHelper.h"
#include "Board.h"

Board board;
int main()
{
    board.Init(25);

    uint64 lastTick = 0;
    while (true)
    {
#pragma region 프레임관리
        const uint64 currentTick = ::GetTickCount64();
        const uint64 deltaTick = currentTick - lastTick;
        lastTick = currentTick;
        // 입력
#pragma endregion
        // 로직

        // 렌더링
        board.Render();

    }
}

