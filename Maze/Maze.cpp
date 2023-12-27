#include <iostream>
#include "pch.h"
#include "ConsoleHelper.h"
#include "Board.h"
#include "Player.h"

Board board;
Player player;
int main()
{
    ::srand(static_cast<unsigned>(time(nullptr)));
    board.Init(25, &player);
    player.Init(&board);

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
        player.Update(deltaTick);


    }
}

