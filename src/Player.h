#pragma once
#include <graphics.h>
#include "Animation.h"

class Player {
public:
    // 构造函数
    Player(int x, int y);

    // 初始化动画资源
    void LoadAnimation();

    // 处理按键按下事件
    void OnKeyDown(int vkcode);

    // 处理按键释放事件
    void OnKeyUp(int vkcode);

    // 更新玩家状态（移动 + 动画）
    void Update();

    // 绘制玩家图像
    void Draw();

    // 获取当前位置
    POINT GetPosition() const;

private:
    POINT pos;                  // 玩家坐标
    static const int PLAYER_ANIM_NUM = 6;
    static const int PLAYER_SPEED = 5;
    static const int ANIM_INTERVAL = 100;  // 动画间隔时间(毫秒)

    Animation* anim_left;       // 左侧动画
    Animation* anim_right;      // 右侧动画
    bool facing_left;           // 朝向标志

    bool is_move_up = false;
    bool is_move_down = false;
    bool is_move_left = false;
    bool is_move_right = false;

    DWORD last_update_time;     // 上次更新时间
};
