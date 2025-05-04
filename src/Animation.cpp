#include "Animation.h"

inline void putimage_alpha(int x, int y, IMAGE* img)
{
    int w = img->getwidth();
    int h = img->getheight();
    AlphaBlend(GetImageHDC(NULL), x, y, w, h,
        GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
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