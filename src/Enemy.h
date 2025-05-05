#pragma once
#include <cmath>     // for sqrt
#include "Character.h"
#include "Player.h"
#include "Bullet.h"

/**
 * @class Enemy
 * @brief 敌人类，管理敌人的状态和交互行为
 * 
 * 该类负责敌人的移动、碰撞检测和渲染
 */
class Enemy : public Character {
public:
    /**
     * @brief 构造函数
     * 初始化敌人的位置和动画
     */
    Enemy();
    
    /**
     * @brief 加载敌人动画资源
     * 创建向左和向右移动的动画对象
     */
    virtual void LoadAnimation() override;
    
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
     * @param player 玩家对象作为移动目标
     */
    void Move(const Player& player);

    /**
     * @brief 更新敌人状态
     * 目前敌人没有特殊的更新逻辑
     */
    virtual void Update() override;

    /**
     * @brief 绘制敌人及其阴影
     * @param delta 时间增量(毫秒)，用于动画更新
     */
    virtual void Draw() override;
    
    /**
     * @brief 绘制敌人及其阴影（带时间参数）
     * @param delta 时间增量(毫秒)，用于动画更新
     */
    void Draw(int delta);

    /**
     * @brief 敌人受伤
     * 将敌人标记为死亡
     */
    void Hurt() { alive = false; }

    /**
     * @brief 检查敌人是否存活
     * @return 敌人存活状态
     */
    bool CheckAlive() {
        return alive;
    }

private:
    int SPEED ;               // 敌人移动速度
    const int FRAME_WIDTH = 80;        // 敌人宽度
    const int FRAME_HEIGHT = 80;       // 敌人高度
    const int SHADOW_WIDTH = 48;       // 阴影宽度

    bool alive = true;                 // 存活状态
};

