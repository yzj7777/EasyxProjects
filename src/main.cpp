#include <graphics.h>
#include "Player.h"

int main()
{
    initgraph(1280, 720);
    bool running = true;
    ExMessage msg;

    IMAGE img_background;
    loadimage(&img_background, _T("res/img/background.png"));

    Player player(500, 500);
    player.LoadAnimation();

    BeginBatchDraw();

    while (running)
    {
        DWORD start_time = GetTickCount();

        while (peekmessage(&msg))
        {
            if (msg.message == WM_KEYDOWN)
            {
                player.OnKeyDown(msg.vkcode);
            }
            else if (msg.message == WM_KEYUP)
            {
                player.OnKeyUp(msg.vkcode);
            }
        }

        player.Update();

        cleardevice();
        putimage(0, 0, &img_background);
        player.Draw();

        FlushBatchDraw();

        DWORD end_time = GetTickCount();
        DWORD delta_time = end_time - start_time;

        if (delta_time < 1000 / 144)
        {
            Sleep(1000 / 144 - delta_time);
        }
    }

    EndBatchDraw();
    closegraph();
    return 0;
}