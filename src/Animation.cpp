#include "Animation.h"
#include <string>

inline void putimage_alpha(int x, int y, IMAGE* img)
{
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(GetImageHDC(NULL), x, y, w, h,
        GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

Animation::Animation(LPCTSTR path, int num, int interval)
    : interval_ms(interval)
{
    for (int i = 0; i < num; i++)
    {
        IMAGE* img = new IMAGE();
        std::wstring full_path = path + std::to_wstring(i) + L".png";
        loadimage(img, full_path.c_str());
        frame_list.push_back(img);
    }
}

Animation::~Animation()
{
    for (size_t i = 0; i < frame_list.size(); i++)
        delete frame_list[i];
}

void Animation::Play(int x, int y, int delta)
{
    timer += delta;
    if (timer >= interval_ms)
    {
        idx_frame = (idx_frame + 1) % frame_list.size();
        timer = 0;
    }

    putimage_alpha(x, y, frame_list[idx_frame]);
}