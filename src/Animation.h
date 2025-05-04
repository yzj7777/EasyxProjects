#pragma once
#include <graphics.h>
#include <vector>

class Animation {
public:
    // 构造函数：加载动画帧
    Animation(LPCTSTR path, int num, int interval);

    // 析构函数：释放资源
    ~Animation();

    void Play(int x, int y, int delta);

private:
    int timer = 0;              // 动画计时器
    int idx_frame = 0;          // 动画帧索引
    int interval_ms = 0;
    std::vector<IMAGE*> frame_list;
};

// 图像绘制函数
#pragma comment(lib, "MSIMG32.LIB")

inline void putimage_alpha(int x, int y, IMAGE* img);