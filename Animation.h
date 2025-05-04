#pragma once
#include <graphics.h>
#include <vector>

class Animation {
public:
    // ���캯�������ض���֡
    Animation(LPCTSTR path, int num, int interval);

    // �����������ͷ���Դ
    ~Animation();

private:
    int interval_ms = 0;           // ����֡���ʱ�䣨���룩
    std::vector<IMAGE*> frame_list; // ����֡�б�
};
