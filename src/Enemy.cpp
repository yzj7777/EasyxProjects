#include "Enemy.h"
#include "Player.h"
#include <graphics.h>
#include <cstdlib>  // for rand()
#include <ctime>    // for time()

/** 
 * @brief Enemy�๹�캯��
 * ��ʼ�����˵�λ�úͶ���
 */
Enemy::Enemy() {
    // ���ص�����Ӱͼ��
    loadimage(&img_shadow, _T("res/img/shadow_enemy.png"));
    
    // ��������������ƶ��Ķ���
    anim_left = new Animation(_T("res/img/enemy_left_"), 6, 45);
    anim_right = new Animation(_T("res/img/enemy_right_"), 6, 45);

    // �������ɱ߽�ö��
    enum class SpawnEdge
    {
        Up = 0,
        Down,
        Left,
        Right
    };

    // ���ѡ��������ɵı߽�λ��
    SpawnEdge edge = (SpawnEdge)(rand() % 4);
    
    // ����ѡ��ı߽����õ��˵ĳ�ʼλ��
    switch (edge)
    {
    case SpawnEdge::Up:
        position.x = rand() % WIN_WIDTH;
        position.y = -FRAME_HEIGHT;
        break;
    case SpawnEdge::Down:
        position.x = rand() % WIN_WIDTH;
        position.y = WIN_HEIGHT;
        break;      
    case SpawnEdge::Left:
        position.x = -FRAME_WIDTH;
        position.y = rand() % WIN_HEIGHT;
        break;
    case SpawnEdge::Right:
        position.x = WIN_WIDTH;
        position.y = rand() % WIN_HEIGHT;
        break;
    default:
        break;
    }
}

/**
 * @brief Enemy����������
 * �ͷŶ�����Դ
 */
Enemy::~Enemy() {
    delete anim_left;
    delete anim_right;
}

/**
 * @brief ������ӵ�����ײ
 * @param bullet �ӵ�����
 * @return �Ƿ�����ײ
 */
bool Enemy::CheckBulletCollision(const Bullet& bullet) {
    // ���ӵ���ЧΪ�㣬�жϵ��Ƿ��ڵ��˾�����
    bool is_overlap_x = bullet.position.x >= position.x && bullet.position.x <= position.x + FRAME_WIDTH;
    bool is_overlap_y = bullet.position.y >= position.y && bullet.position.y <= position.y + FRAME_HEIGHT;
    return is_overlap_x && is_overlap_y;
}

/**
 * @brief �������ҵ���ײ
 * @param player ��Ҷ���
 * @return �Ƿ�����ײ
 */
bool Enemy::CheckPlayerCollision(const Player& player) {
    // ����������λ�õ�ЧΪ�㣬�жϵ��Ƿ�����Ҿ�����
    POINT check_position = { position.x + FRAME_WIDTH / 2, position.y + FRAME_HEIGHT / 2 };

    // ��ȡ��ҵľ��η�Χ
    const POINT& player_position = player.GetPosition();


    // �жϵ��������Ƿ�����Ҿ�����
    bool is_overlap_x = check_position.x >= player_position.x &&
        check_position.x <= player_position.x + player.PLAYER_WIDTH;
    bool is_overlap_y = check_position.y >= player_position.y &&
        check_position.y <= player_position.y + player.PLAYER_HEIGHT;

    return is_overlap_x && is_overlap_y;
}

/**
 * @brief �ƶ����˳������
 * @param player ��Ҷ�����Ϊ�ƶ�Ŀ��
 */
void Enemy::Move(const Player& player)
{
    // ��ȡ���λ��
    const POINT& player_position = player.GetPosition();
    
    // ���㷽������
    int dir_x = player_position.x - position.x;
    int dir_y = player_position.y - position.y;
    
    // ���㷽����������
    double len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);
    
    // ������Ȳ�Ϊ�㣬�����滯���ƶ�
    if (len_dir != 0)
    {
        // ���滯��������
        double normalized_x = dir_x / len_dir;
        double normalized_y = dir_y / len_dir;
        
        // ���µ���λ��
        position.x += (int)(SPEED * normalized_x);
        position.y += (int)(SPEED * normalized_y);
        
        // ���µ��˳���
        facing_left = (dir_x < 0);
    }
}

/**
 * @brief ���Ƶ��˼�����Ӱ
 * @param delta ʱ������(����)�����ڶ�������
 */
void Enemy::Draw(int delta)
{
    // ������Ӱλ��
    int pos_shadow_x = position.x + (FRAME_WIDTH / 2 - SHADOW_WIDTH / 2);
    int pos_shadow_y = position.y + FRAME_HEIGHT - 35;
    
    // ������Ӱ
    putimage_alpha(pos_shadow_x, pos_shadow_y, &img_shadow);

    // ���ݳ��������Ӧ�Ķ���
    if (facing_left)
        anim_left->Play(position.x, position.y, delta);
    else
        anim_right->Play(position.x, position.y, delta);
}
