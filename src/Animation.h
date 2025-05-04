#pragma once
#include <graphics.h>
#include <vector>

/**
 * @class Animation
 * @brief 动画类，用于管理和播放帧动画
 * 
 * 该类负责加载、存储和播放一系列图像帧，形成动画效果
 */
class Animation {
public:
    /**
     * @brief 构造函数，加载指定动画帧
     * @param path 动画帧图片路径前缀
     * @param num 动画帧数量
     * @param interval 帧间隔时间(毫秒)
     */
    Animation(LPCTSTR path, int num, int interval);

    /**
     * @brief 析构函数，释放资源
     */
    ~Animation();

    /**
     * @brief 播放动画
     * @param x 显示位置的x坐标
     * @param y 显示位置的y坐标
     * @param delta 距离上次调用的时间间隔(毫秒)
     */
    void Play(int x, int y, int delta);

private:
    int timer = 0;              // 计时器时间
    int idx_frame = 0;          // 当前帧索引
    int interval_ms = 0;        // 帧间隔时间(毫秒)
    std::vector<IMAGE*> frame_list;  // 存储所有动画帧的图像
};

// 图像绘制函数
#pragma comment(lib, "MSIMG32.LIB")  // 链接AlphaBlend函数所需的库

/**
 * @brief 带透明通道的图像绘制函数
 * @param x 绘制位置的x坐标
 * @param y 绘制位置的y坐标
 * @param img 要绘制的图像指针
 */
inline void putimage_alpha(int x, int y, IMAGE* img);