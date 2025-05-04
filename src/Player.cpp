#include "Player.h"
#include "Animation.h"
#include <string>
#include <windows.h> // for AlphaBlend

/**
 * @brief Player类构造函数
 * @param x 初始x坐标
 * @param y 初始y坐标
 */
Player::Player(int x, int y)
    : pos{ x, y }, facing_left(true), last_update_time(0)
{
    // 初始化动画指针为空
    anim_left = nullptr;
    anim_right = nullptr;
}

/**
 * @brief 加载玩家动画资源
 * 创建向左和向右移动的动画对象
 */
void Player::LoadAnimation()
{
    loadimage(&img_shadow, _T("res/img/shadow_player.png"));

    // 加载向左移动的动画
    anim_left = new Animation(L"res/img/player_left_", PLAYER_ANIM_NUM, ANIM_INTERVAL);
    // 加载向右移动的动画
    anim_right = new Animation(L"res/img/player_right_", PLAYER_ANIM_NUM, ANIM_INTERVAL);
}

/**
 * @brief 处理按键按下事件
 * @param vkcode 虚拟键码
 */
void Player::OnKeyDown(int vkcode)
{
    // 根据按下的键设置相应的移动状态
    switch (vkcode)
    {
    case 'W':
    case 'w':
        is_move_up = true;  // 向上移动
        break;
    case 'S':
    case 's':
        is_move_down = true;  // 向下移动
        break;
    case 'A':
    case 'a':
        is_move_left = true;  // 向左移动
        facing_left = true;   // 设置朝向为左
        break;
    case 'D':
    case 'd':
        is_move_right = true;  // 向右移动
        facing_left = false;   // 设置朝向为右
        break;
    }
}

/**
 * @brief 处理按键释放事件
 * @param vkcode 虚拟键码
 */
void Player::OnKeyUp(int vkcode)
{
    // 根据释放的键重置相应的移动状态
    switch (vkcode)
    {
    case 'W':
    case 'w':
        is_move_up = false;  // 停止向上移动
        break;
    case 'S':
    case 's':
        is_move_down = false;  // 停止向下移动
        break;
    case 'A':
    case 'a':
        is_move_left = false;  // 停止向左移动
        break;
    case 'D':
    case 'd':
        is_move_right = false;  // 停止向右移动
        break;
    }
}

/**
 * @brief 更新玩家状态
 * 根据当前移动状态更新玩家位置
 */
void Player::Update()
{
    // 获取当前时间和时间差
    DWORD current_time = GetTickCount();
    DWORD delta_time = current_time - last_update_time;
    last_update_time = current_time;

    // 根据移动状态更新位置
    if (is_move_up)    pos.y -= PLAYER_SPEED;  // 向上移动
    if (is_move_down)  pos.y += PLAYER_SPEED;  // 向下移动
    if (is_move_left)  pos.x -= PLAYER_SPEED;  // 向左移动
    if (is_move_right) pos.x += PLAYER_SPEED;  // 向右移动
}

/**
 * @brief 绘制玩家
 * 根据朝向绘制相应的动画
 */
void Player::Draw()
{

    int pos_shadow_x = pos.x + (PLAYER_WIDTH / 2 - SHADOW_WIDTH / 2);
    int pos_shadow_y = pos.y + PLAYER_HEIGHT - 8;
    putimage_alpha(pos_shadow_x, pos_shadow_y, &img_shadow);

    // 计算时间差用于动画更新
    DWORD delta_time = GetTickCount() - last_update_time;

    if (pos.x < 0) pos.x = 0;
    if (pos.y < 0) pos.y = 0;
    if (pos.x + PLAYER_WIDTH > 1280) pos.x = 1280 - PLAYER_WIDTH;
    if (pos.y + PLAYER_HEIGHT > 720) pos.y = 720 - PLAYER_HEIGHT;
    
    // 根据朝向选择并播放相应的动画
    if (facing_left)
        anim_left->Play(pos.x, pos.y, delta_time);
    else
        anim_right->Play(pos.x, pos.y, delta_time);
}

/**
 * @brief 获取玩家当前位置
 * @return 玩家坐标
 */
POINT Player::GetPosition() const
{
    return pos;
}
