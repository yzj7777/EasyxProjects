#pragma once
#include "Character.h"

/**
 * @class Player
 * @brief 玩家类，管理玩家的状态和交互行为
 */
class Player : public Character {
public:
    /**
     * @brief 构造函数
     * @param x 初始x坐标
     * @param y 初始y坐标
     */
    Player(int x, int y);

    /**
     * @brief 加载玩家动画资源
     * 创建向左和向右移动的动画对象
     */
    virtual void LoadAnimation() override;

    /**
     * @brief 处理按键按下事件
     * @param vkcode 虚拟键码
     */
    void OnKeyDown(int vkcode);

    /**
     * @brief 处理按键释放事件
     * @param vkcode 虚拟键码
     */
    void OnKeyUp(int vkcode);

    /**
     * @brief 更新玩家状态，移动 + 边界检查
     * 根据当前按键状态更新玩家位置
     */
    virtual void Update() override;

    /**
     * @brief 绘制玩家图像
     * 根据朝向绘制相应的动画
     */
    virtual void Draw() override;

public:
    const int PLAYER_WIDTH = 80;  // 玩家宽度
    const int PLAYER_HEIGHT = 80; // 玩家高度
    const int SHADOW_WIDTH = 32;  // 阴影宽度

private:
    static const int PLAYER_ANIM_NUM = 6;    // 玩家动画帧数
    static const int PLAYER_SPEED = 5;       // 玩家移动速度
    static const int ANIM_INTERVAL = 100;    // 动画间隔时间(毫秒)

    // 移动状态标志
    bool is_move_up = false;    // 是否向上移动
    bool is_move_down = false;  // 是否向下移动
    bool is_move_left = false;  // 是否向左移动
    bool is_move_right = false; // 是否向右移动
};
