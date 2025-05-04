#pragma once
#include <windows.h> // for POINT
#include <cmath>     // for sqrt
#include "Animation.h" 
#include "Player.h"
#include "Bullet.h"

/**
 * @class Enemy
 * @brief �����࣬������˵�״̬����������Ϊ
 * 
 * ���ฺ����˵��ƶ�����ײ������Ⱦ
 */
class Enemy {
public:
    /**
     * @brief ���캯��
     * ��ʼ�����˵�λ�úͶ���
     */
    Enemy();
    
    /**
     * @brief ��������
     * �ͷŶ�����Դ
     */
    ~Enemy();

    /**
     * @brief ������ӵ�����ײ
     * @param bullet �ӵ�����
     * @return �Ƿ�����ײ
     */
    bool CheckBulletCollision(const Bullet& bullet);
    
    /**
     * @brief �������ҵ���ײ
     * @param player ��Ҷ���
     * @return �Ƿ�����ײ
     */
    bool CheckPlayerCollision(const Player& player);

    /**
     * @brief �ƶ����˳������
     * @param player ��Ҷ�����Ϊ�ƶ�Ŀ��
     */
    void Move(const Player& player);

    /**
     * @brief ���Ƶ��˼�����Ӱ
     * @param delta ʱ������(����)�����ڶ�������
     */
    void Draw(int delta);

    void Hurt(){alive = false; }

    bool CheckAlive() {
        return alive;
    }

private:
    const int SPEED = 2;               // �����ƶ��ٶ�
    const int FRAME_WIDTH = 80;        // ���˿��
    const int FRAME_HEIGHT = 80;       // ���˸߶�
    const int SHADOW_WIDTH = 48;       // ��Ӱ���

    IMAGE img_shadow;                  // ��Ӱͼ��
    Animation* anim_left;              // �����ƶ��Ķ���
    Animation* anim_right;             // �����ƶ��Ķ���
    POINT position = { 0, 0 };         // ����λ��
    bool facing_left = false;          // ���˳���(�Ƿ���)

    const int WIN_WIDTH = 1280;        // ���ڿ��
    const int WIN_HEIGHT = 720;        // ���ڸ߶�

    bool alive = true;
};

