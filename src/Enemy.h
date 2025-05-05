#pragma once
#include <cmath>     // for sqrt
#include "Character.h"
#include "Player.h"
#include "Bullet.h"

/**
 * @class Enemy
 * @brief �����࣬������˵�״̬�ͽ�����Ϊ
 * 
 * ���ฺ����˵��ƶ�����ײ������Ⱦ
 */
class Enemy : public Character {
public:
    /**
     * @brief ���캯��
     * ��ʼ�����˵�λ�úͶ���
     */
    Enemy();
    
    /**
     * @brief ���ص��˶�����Դ
     * ��������������ƶ��Ķ�������
     */
    virtual void LoadAnimation() override;
    
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
     * @brief ���µ���״̬
     * Ŀǰ����û������ĸ����߼�
     */
    virtual void Update() override;

    /**
     * @brief ���Ƶ��˼�����Ӱ
     * @param delta ʱ������(����)�����ڶ�������
     */
    virtual void Draw() override;
    
    /**
     * @brief ���Ƶ��˼�����Ӱ����ʱ�������
     * @param delta ʱ������(����)�����ڶ�������
     */
    void Draw(int delta);

    /**
     * @brief ��������
     * �����˱��Ϊ����
     */
    void Hurt() { alive = false; }

    /**
     * @brief �������Ƿ���
     * @return ���˴��״̬
     */
    bool CheckAlive() {
        return alive;
    }

private:
    int SPEED ;               // �����ƶ��ٶ�
    const int FRAME_WIDTH = 80;        // ���˿��
    const int FRAME_HEIGHT = 80;       // ���˸߶�
    const int SHADOW_WIDTH = 48;       // ��Ӱ���

    bool alive = true;                 // ���״̬
};

