#pragma once
#include <graphics.h>

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
    int idx_current_anim;       // ��ǰ����֡����
    static const int PLAYER_ANIM_NUM = 6;
    static const int PLAYER_SPEED = 5;

    IMAGE img_player_left[PLAYER_ANIM_NUM];   // ��߶���֡
    IMAGE img_player_right[PLAYER_ANIM_NUM];  // �ұ߶���֡

    bool is_move_up = false;
    bool is_move_down = false;
    bool is_move_left = false;
    bool is_move_right = false;

    // �������������ƴ�͸��ͨ����ͼ��
    void putimage_alpha(int x, int y, IMAGE* img);

};
