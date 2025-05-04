#include "Player.h"
#include "Animation.h"
#include <string>
#include <windows.h> // for AlphaBlend

Player::Player(int x, int y)
    : pos{ x, y }, facing_left(true), last_update_time(0)
{
    anim_left = nullptr;
    anim_right = nullptr;
}

void Player::LoadAnimation()
{
    anim_left = new Animation(L"res/img/player_left_", PLAYER_ANIM_NUM, ANIM_INTERVAL);
    anim_right = new Animation(L"res/img/player_right_", PLAYER_ANIM_NUM, ANIM_INTERVAL);
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
        facing_left = true;
        break;
    case 'D':
    case 'd':
        is_move_right = true;
        facing_left = false;
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
    DWORD current_time = GetTickCount();
    DWORD delta_time = current_time - last_update_time;
    last_update_time = current_time;

    if (is_move_up)    pos.y -= PLAYER_SPEED;
    if (is_move_down)  pos.y += PLAYER_SPEED;
    if (is_move_left)  pos.x -= PLAYER_SPEED;
    if (is_move_right) pos.x += PLAYER_SPEED;
}

void Player::Draw()
{
    DWORD delta_time = GetTickCount() - last_update_time;
    
    if (facing_left)
        anim_left->Play(pos.x, pos.y, delta_time);
    else
        anim_right->Play(pos.x, pos.y, delta_time);
}

POINT Player::GetPosition() const
{
    return pos;
}
