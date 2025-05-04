#include "Player.h"
#include <string>
#include <windows.h> // for AlphaBlend

#pragma comment(lib, "MSIMG32.LIB")

Player::Player(int x, int y)
    : pos{ x, y }, idx_current_anim(0)
{
}

void Player::LoadAnimation()
{
    for (size_t i = 0; i < PLAYER_ANIM_NUM; i++)
    {
        std::wstring path = L"res/img/player_left_"
            + std::to_wstring(i) + L".png";
        loadimage(&img_player_left[i], path.c_str());
    }

    for (size_t i = 0; i < PLAYER_ANIM_NUM; i++)
    {
        std::wstring path = L"res/img/player_right_"
            + std::to_wstring(i) + L".png";
        loadimage(&img_player_right[i], path.c_str());
    }
}

void Player::OnKeyDown(int vkcode)
{
    switch (vkcode)
    {
    case 'W':
    case 'w':
        is_move_up = true;
        break;
    case 'S':
    case 's':
        is_move_down = true;
        break;
    case 'A':
    case 'a':
        is_move_left = true;
        break;
    case 'D':
    case 'd':
        is_move_right = true;
        break;
    }
}

void Player::OnKeyUp(int vkcode)
{
    switch (vkcode)
    {
    case 'W':
    case 'w':
        is_move_up = false;
        break;
    case 'S':
    case 's':
        is_move_down = false;
        break;
    case 'A':
    case 'a':
        is_move_left = false;
        break;
    case 'D':
    case 'd':
        is_move_right = false;
        break;
    }
}

void Player::Update()
{
    static int counter = 0;

    if (++counter % 5 == 0)
    {
        idx_current_anim++;
        idx_current_anim %= PLAYER_ANIM_NUM;
    }

    if (is_move_up)    pos.y -= PLAYER_SPEED;
    if (is_move_down)  pos.y += PLAYER_SPEED;
    if (is_move_left)  pos.x -= PLAYER_SPEED;
    if (is_move_right) pos.x += PLAYER_SPEED;
}

void Player::Draw()
{
    putimage_alpha(pos.x, pos.y, &img_player_left[idx_current_anim]);
}

POINT Player::GetPosition() const
{
    return pos;
}

void Player::putimage_alpha(int x, int y, IMAGE* img)
{
    int w = img->getwidth();
    int h = img->getheight();
    BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
    AlphaBlend(GetImageHDC(NULL), x, y, w, h,
        GetImageHDC(img), 0, 0, w, h, blend);
}
