#pragma once
#include "Character.h"

/**
 * @class Player
 * @brief ����࣬������ҵ�״̬�ͽ�����Ϊ
 */
class Player : public Character {
public:
    /**
     * @brief ���캯��
     * @param x ��ʼx����
     * @param y ��ʼy����
     */
    Player(int x, int y);

    /**
     * @brief ������Ҷ�����Դ
     * ��������������ƶ��Ķ�������
     */
    virtual void LoadAnimation() override;

    /**
     * @brief �����������¼�
     * @param vkcode �������
     */
    void OnKeyDown(int vkcode);

    /**
     * @brief �������ͷ��¼�
     * @param vkcode �������
     */
    void OnKeyUp(int vkcode);

    /**
     * @brief �������״̬���ƶ� + �߽���
     * ���ݵ�ǰ����״̬�������λ��
     */
    virtual void Update() override;

    /**
     * @brief �������ͼ��
     * ���ݳ��������Ӧ�Ķ���
     */
    virtual void Draw() override;

public:
    const int PLAYER_WIDTH = 80;  // ��ҿ��
    const int PLAYER_HEIGHT = 80; // ��Ҹ߶�
    const int SHADOW_WIDTH = 32;  // ��Ӱ���

private:
    static const int PLAYER_ANIM_NUM = 6;    // ��Ҷ���֡��
    static const int PLAYER_SPEED = 5;       // ����ƶ��ٶ�
    static const int ANIM_INTERVAL = 100;    // �������ʱ��(����)

    // �ƶ�״̬��־
    bool is_move_up = false;    // �Ƿ������ƶ�
    bool is_move_down = false;  // �Ƿ������ƶ�
    bool is_move_left = false;  // �Ƿ������ƶ�
    bool is_move_right = false; // �Ƿ������ƶ�
};
