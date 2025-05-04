#include "Animation.h"
#include <string>  // 用于std::wstring

/**
 * @brief 带透明通道的图像绘制函数实现
 * @param x 绘制位置的x坐标
 * @param y 绘制位置的y坐标
 * @param img 要绘制的图像指针
 */
inline void putimage_alpha(int x, int y, IMAGE* img)
{
    // 获取图像宽高
    int w = img->getwidth();
    int h = img->getheight();
    
    // 使用Windows GDI的AlphaBlend函数实现透明混合
    AlphaBlend(GetImageHDC(NULL), x, y, w, h,
        GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

/**
 * @brief Animation类构造函数
 * @param path 动画帧图片路径前缀
 * @param num 动画帧数量
 * @param interval 帧间隔时间(毫秒)
 */
Animation::Animation(LPCTSTR path, int num, int interval)
    : interval_ms(interval)  // 初始化帧间隔时间
{
    // 加载所有动画帧
    for (int i = 0; i < num; i++)
    {
        // 为每一帧创建图像对象
        IMAGE* img = new IMAGE();
        
        // 构建完整的文件路径：前缀 + 索引 + .png
        std::wstring full_path = path + std::to_wstring(i) + L".png";
        
        // 加载图像
        loadimage(img, full_path.c_str());
        
        // 将图像添加到帧列表
        frame_list.push_back(img);
    }
}

/**
 * @brief Animation类析构函数
 * 释放所有动态分配的图像资源
 */
Animation::~Animation()
{
    // 释放所有动画帧的内存
    for (size_t i = 0; i < frame_list.size(); i++)
        delete frame_list[i];
}

/**
 * @brief 播放动画
 * @param x 显示位置的x坐标
 * @param y 显示位置的y坐标
 * @param delta 距离上次调用的时间间隔(毫秒)
 */
void Animation::Play(int x, int y, int delta)
{
    // 累加时间
    timer += delta;
    
    // 如果达到或超过帧间隔时间，切换到下一帧
    if (timer >= interval_ms)
    {
        // 循环切换帧索引
        idx_frame = (idx_frame + 1) % frame_list.size();
        // 重置计时器
        timer = 0;
    }

    // 绘制当前帧
    putimage_alpha(x, y, frame_list[idx_frame]);
}