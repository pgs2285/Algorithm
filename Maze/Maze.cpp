#include <iostream>
#include "pch.h"
#include "ConsoleHelper.h"
int main()
{

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

        ConsoleHelper::SetCursorPosition(0, 0);
        ConsoleHelper::ShowConsoleCursor(false);
        ConsoleHelper::SetCursorColor(ConsoleColor::RED);


        const char* TILE = "■";

        for (int32 y = 0; y < 25; ++y)
        {
            for (int32 x = 0; x < 25; ++x)
            {
                cout << TILE;
            }
            cout << endl;
        }
    }
}

