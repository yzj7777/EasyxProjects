#pragma once
#include <graphics.h>
#include "Animation.h"

/**
 * @class Player
 * @brief ����࣬������ҵ�״̬����������Ϊ
 */
class Player {
public:
    /**
     * @brief ���캯��
     * @param x ��ʼx����
     * @param y ��ʼy����
     */
    Player(int x, int y);

    /**
     * @brief ��ʼ��������Դ
     * �����������������ƶ��Ķ���
     */
    void LoadAnimation();

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
     * @brief �������״̬���ƶ� + ������
     * ���ݵ�ǰ����״̬�������λ��
     */
    void Update();

    /**
     * @brief �������ͼ��
     * ���ݳ��������Ӧ�Ķ���
     */
    void Draw();

    /**
     * @brief ��ȡ��ǰλ��
     * @return ��ҵ�ǰ����
     */
    POINT GetPosition() const;

private:
    POINT pos;                  // �������
    static const int PLAYER_ANIM_NUM = 6;    // ��Ҷ���֡��
    static const int PLAYER_SPEED = 5;       // ����ƶ��ٶ�
    static const int ANIM_INTERVAL = 100;    // �������ʱ��(����)

    Animation* anim_left;       // ��ද��
    Animation* anim_right;      // �Ҳද��
    bool facing_left;           // �����־

    // �ƶ�״̬��־
    bool is_move_up = false;    // �Ƿ������ƶ�
    bool is_move_down = false;  // �Ƿ������ƶ�
    bool is_move_left = false;  // �Ƿ������ƶ�
    bool is_move_right = false; // �Ƿ������ƶ�

    DWORD last_update_time;     // �ϴθ���ʱ��

    IMAGE img_shadow;           // ��Ӱͼ��
    const int PLAYER_WIDTH = 80; // ��ҿ��
    const int PLAYER_HEIGHT = 80; // ��Ҹ߶�
    const int SHADOW_WIDTH = 32; // ��Ӱ���
};
