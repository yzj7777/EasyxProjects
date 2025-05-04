#pragma once
#include <graphics.h>
#include <vector>

class Animation {
public:
    // ���캯�������ض���֡
    Animation(LPCTSTR path, int num, int interval);

    // �����������ͷ���Դ
    ~Animation();

    void Play(int x, int y, int delta);

private:
    int timer = 0;              // ������ʱ��
    int idx_frame = 0;          // ����֡����
    int interval_ms = 0;
    std::vector<IMAGE*> frame_list;
};

// ͼ����ƺ���
#pragma comment(lib, "MSIMG32.LIB")

inline void putimage_alpha(int x, int y, IMAGE* img);