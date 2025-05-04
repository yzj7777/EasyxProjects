#pragma once
#include <graphics.h>
#include "Animation.h"

class Player {
public:
    // ���캯��
    Player(int x, int y);

    // ��ʼ��������Դ
    void LoadAnimation();

    // �����������¼�
    void OnKeyDown(int vkcode);

    // �������ͷ��¼�
    void OnKeyUp(int vkcode);

    // �������״̬���ƶ� + ������
    void Update();

    // �������ͼ��
    void Draw();

    // ��ȡ��ǰλ��
    POINT GetPosition() const;

private:
    POINT pos;                  // �������
    static const int PLAYER_ANIM_NUM = 6;
    static const int PLAYER_SPEED = 5;
    static const int ANIM_INTERVAL = 100;  // �������ʱ��(����)

    Animation* anim_left;       // ��ද��
    Animation* anim_right;      // �Ҳද��
    bool facing_left;           // �����־

    bool is_move_up = false;
    bool is_move_down = false;
    bool is_move_left = false;
    bool is_move_right = false;

    DWORD last_update_time;     // �ϴθ���ʱ��
};
