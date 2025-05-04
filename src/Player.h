#pragma once
#include <graphics.h>

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
    int idx_current_anim;       // 当前动画帧索引
    static const int PLAYER_ANIM_NUM = 6;
    static const int PLAYER_SPEED = 5;

    IMAGE img_player_left[PLAYER_ANIM_NUM];   // 左边动画帧
    IMAGE img_player_right[PLAYER_ANIM_NUM];  // 右边动画帧

    bool is_move_up = false;
    bool is_move_down = false;
    bool is_move_left = false;
    bool is_move_right = false;

    // 辅助函数：绘制带透明通道的图像
    void putimage_alpha(int x, int y, IMAGE* img);

};
