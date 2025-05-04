#pragma once
#include <graphics.h>
#include "Animation.h"

/**
 * @class Player
 * @brief 玩家类，管理玩家的状态、动画和行为
 */
class Player {
public:
    /**
     * @brief 构造函数
     * @param x 初始x坐标
     * @param y 初始y坐标
     */
    Player(int x, int y);

    /**
     * @brief 初始化动画资源
     * 加载玩家向左和向右移动的动画
     */
    void LoadAnimation();

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
     * @brief 更新玩家状态（移动 + 动画）
     * 根据当前按键状态更新玩家位置
     */
    void Update();

    /**
     * @brief 绘制玩家图像
     * 根据朝向绘制相应的动画
     */
    void Draw();

    /**
     * @brief 获取当前位置
     * @return 玩家当前坐标
     */
    POINT GetPosition() const;

private:
    POINT pos;                  // 玩家坐标
    static const int PLAYER_ANIM_NUM = 6;    // 玩家动画帧数
    static const int PLAYER_SPEED = 5;       // 玩家移动速度
    static const int ANIM_INTERVAL = 100;    // 动画间隔时间(毫秒)

    Animation* anim_left;       // 左侧动画
    Animation* anim_right;      // 右侧动画
    bool facing_left;           // 朝向标志

    // 移动状态标志
    bool is_move_up = false;    // 是否向上移动
    bool is_move_down = false;  // 是否向下移动
    bool is_move_left = false;  // 是否向左移动
    bool is_move_right = false; // 是否向右移动

    DWORD last_update_time;     // 上次更新时间

    IMAGE img_shadow;           // 阴影图像
    const int PLAYER_WIDTH = 80; // 玩家宽度
    const int PLAYER_HEIGHT = 80; // 玩家高度
    const int SHADOW_WIDTH = 32; // 阴影宽度
};
