#include "Character.h"

/**
 * @brief Character类构造函数
 * @param x 初始x坐标
 * @param y 初始y坐标
 */
Character::Character(int x, int y)
    : position{ x, y }, facing_left(true), last_update_time(0)
{
    // 初始化动画指针为空
    anim_left = nullptr;
    anim_right = nullptr;
}

/**
 * @brief Character类析构函数
 * 释放动画资源
 */
Character::~Character()
{
    delete anim_left;
    delete anim_right;
}

/**
 * @brief 获取当前位置
 * @return 角色当前坐标
 */
POINT Character::GetPosition() const
{
    return position;
}