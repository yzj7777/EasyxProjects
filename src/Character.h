#pragma once
#include <windows.h> // for POINT
#include <graphics.h>
#include "Animation.h"

/**
 * @class Character
 * @brief 角色基类，管理游戏中角色的共同属性和行为
 * 
 * 该类负责角色的位置、动画、朝向等基本属性
 */
class Character {
public:
    /**
     * @brief 构造函数
     * @param x 初始x坐标
     * @param y 初始y坐标
     */
    Character(int x, int y);
    
    /**
     * @brief 虚析构函数
     * 确保正确释放派生类资源
     */
    virtual ~Character();

    /**
     * @brief 加载角色动画资源
     * 创建向左和向右移动的动画对象
     */
    virtual void LoadAnimation() = 0;

    /**
     * @brief 更新角色状态
     * 根据当前状态更新角色位置
     */
    virtual void Update() = 0;

    /**
     * @brief 绘制角色及其阴影
     * 根据朝向绘制相应的动画
     */
    virtual void Draw() = 0;

    /**
     * @brief 获取当前位置
     * @return 角色当前坐标
     */
    POINT GetPosition() const;

protected:
    POINT position;                // 角色坐标
    Animation* anim_left;          // 左侧动画
    Animation* anim_right;         // 右侧动画
    bool facing_left;              // 朝向标志
    IMAGE img_shadow;              // 阴影图像
    DWORD last_update_time;        // 上次更新时间

    // 窗口尺寸常量
    const int WIN_WIDTH = 1280;    // 窗口宽度
    const int WIN_HEIGHT = 720;    // 窗口高度
};