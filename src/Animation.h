#pragma once
#include <graphics.h>
#include <vector>

/**
 * @class Animation
 * @brief �����࣬���ڹ���Ͳ���֡����
 * 
 * ���ฺ����ء��洢�Ͳ���һϵ��ͼ��֡���γɶ���Ч��
 */
class Animation {
public:
    /**
     * @brief ���캯��������ָ������֡
     * @param path ����֡ͼƬ·��ǰ׺
     * @param num ����֡����
     * @param interval ֡���ʱ��(����)
     */
    Animation(LPCTSTR path, int num, int interval);

    /**
     * @brief �����������ͷ���Դ
     */
    ~Animation();

    /**
     * @brief ���Ŷ���
     * @param x ��ʾλ�õ�x����
     * @param y ��ʾλ�õ�y����
     * @param delta �����ϴε��õ�ʱ����(����)
     */
    void Play(int x, int y, int delta);

private:
    int timer = 0;              // ��ʱ��ʱ��
    int idx_frame = 0;          // ��ǰ֡����
    int interval_ms = 0;        // ֡���ʱ��(����)
    std::vector<IMAGE*> frame_list;  // �洢���ж���֡��ͼ��
};

// ͼ����ƺ���
#pragma comment(lib, "MSIMG32.LIB")  // ����AlphaBlend��������Ŀ�

/**
 * @brief ��͸��ͨ����ͼ����ƺ���
 * @param x ����λ�õ�x����
 * @param y ����λ�õ�y����
 * @param img Ҫ���Ƶ�ͼ��ָ��
 */
inline void putimage_alpha(int x, int y, IMAGE* img);