#pragma once
#include <graphics.h>
#include <vector>

class Animation {
public:
    // 构造函数：加载动画帧
    Animation(LPCTSTR path, int num, int interval);

    // 析构函数：释放资源
    ~Animation();

private:
    int interval_ms = 0;           // 动画帧间隔时间（毫秒）
    std::vector<IMAGE*> frame_list; // 动画帧列表
};
