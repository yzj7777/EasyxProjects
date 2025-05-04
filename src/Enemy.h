#pragma once
#include <windows.h> // for POINT
#include <cmath>     // for sqrt
#include "Animation.h" 
#include "Player.h"
#include "Bullet.h"

/**
 * @class Enemy
 * @brief 敌人类，管理敌人的状态、动画和行为
 * 
 * 该类负责敌人的移动、碰撞检测和渲染
 */
class Enemy {
public:
    /**
     * @brief 构造函数
     * 初始化敌人的位置和动画
     */
    Enemy();
    
    /**
     * @brief 析构函数
     * 释放动画资源
     */
    ~Enemy();

    /**
     * @brief 检测与子弹的碰撞
     * @param bullet 子弹对象
     * @return 是否发生碰撞
     */
    bool CheckBulletCollision(const Bullet& bullet);
    
    /**
     * @brief 检测与玩家的碰撞
     * @param player 玩家对象
     * @return 是否发生碰撞
     */
    bool CheckPlayerCollision(const Player& player);

    /**
     * @brief 移动敌人朝向玩家
     * @param player 玩家对象，作为移动目标
     */
    void Move(const Player& player);

    /**
     * @brief 绘制敌人及其阴影
     * @param delta 时间增量(毫秒)，用于动画更新
     */
    void Draw(int delta);

    void Hurt(){alive = false; }

    bool CheckAlive() {
        return alive;
    }

private:
    const int SPEED = 2;               // 敌人移动速度
    const int FRAME_WIDTH = 80;        // 敌人宽度
    const int FRAME_HEIGHT = 80;       // 敌人高度
    const int SHADOW_WIDTH = 48;       // 阴影宽度

    IMAGE img_shadow;                  // 阴影图像
    Animation* anim_left;              // 向左移动的动画
    Animation* anim_right;             // 向右移动的动画
    POINT position = { 0, 0 };         // 敌人位置
    bool facing_left = false;          // 敌人朝向(是否朝左)

    const int WIN_WIDTH = 1280;        // 窗口宽度
    const int WIN_HEIGHT = 720;        // 窗口高度

    bool alive = true;
};

