#include "Animation.h"
#include <windows.h> // for _stprintf_s

// ���캯�������ض���֡
Animation::Animation(LPCTSTR path, int num, int interval)
    : interval_ms(interval)
{
    TCHAR path_file[256];
    for (size_t i = 0; i < num; i++)
    {
        _stprintf_s(path_file, 256, path, i); // ��ʽ���ļ�·��

        IMAGE* frame = new IMAGE();           // �����µ� IMAGE ����
        loadimage(frame, path_file);          // ����ͼ��
        frame_list.push_back(frame);          // ��֡��ӵ��б���
    }
}

// �����������ͷ���Դ
Animation::~Animation()
{
    for (size_t i = 0; i < frame_list.size(); i++)
    {
        delete frame_list[i]; // �ͷ�ÿ�� IMAGE ����
    }
}