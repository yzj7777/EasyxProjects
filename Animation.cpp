#include "Animation.h"
#include <windows.h> // for _stprintf_s

// 构造函数：加载动画帧
Animation::Animation(LPCTSTR path, int num, int interval)
    : interval_ms(interval)
{
    TCHAR path_file[256];
    for (size_t i = 0; i < num; i++)
    {
        _stprintf_s(path_file, 256, path, i); // 格式化文件路径

        IMAGE* frame = new IMAGE();           // 创建新的 IMAGE 对象
        loadimage(frame, path_file);          // 加载图像
        frame_list.push_back(frame);          // 将帧添加到列表中
    }
}

// 析构函数：释放资源
Animation::~Animation()
{
    for (size_t i = 0; i < frame_list.size(); i++)
    {
        delete frame_list[i]; // 释放每个 IMAGE 对象
    }
}