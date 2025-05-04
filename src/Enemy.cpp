#include "Enemy.h"
#include "Player.h"
#include <graphics.h>
#include <cstdlib>  // for rand()
#include <ctime>    // for time()

/** 
 * @brief Enemy类构造函数
 * 初始化敌人的位置和动画
 */
Enemy::Enemy() {
    // 加载敌人阴影图像
    loadimage(&img_shadow, _T("res/img/shadow_enemy.png"));
    
    // 创建向左和向右移动的动画
    anim_left = new Animation(_T("res/img/enemy_left_"), 6, 45);
    anim_right = new Animation(_T("res/img/enemy_right_"), 6, 45);

    // 定义生成边界枚举
    enum class SpawnEdge
    {
        Up = 0,
        Down,
        Left,
        Right
    };

    // 随机选择敌人生成的边界位置
    SpawnEdge edge = (SpawnEdge)(rand() % 4);
    
    // 根据选择的边界设置敌人的初始位置
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
 * @brief Enemy类析构函数
 * 释放动画资源
 */
Enemy::~Enemy() {
    delete anim_left;
    delete anim_right;
}

/**
 * @brief 检测与子弹的碰撞
 * @param bullet 子弹对象
 * @return 是否发生碰撞
 */
bool Enemy::CheckBulletCollision(const Bullet& bullet) {
    // 将子弹等效为点，判断点是否在敌人矩形内
    bool is_overlap_x = bullet.position.x >= position.x && bullet.position.x <= position.x + FRAME_WIDTH;
    bool is_overlap_y = bullet.position.y >= position.y && bullet.position.y <= position.y + FRAME_HEIGHT;
    return is_overlap_x && is_overlap_y;
}

/**
 * @brief 检测与玩家的碰撞
 * @param player 玩家对象
 * @return 是否发生碰撞
 */
bool Enemy::CheckPlayerCollision(const Player& player) {
    // 将敌人中心位置等效为点，判断点是否在玩家矩形内
    POINT check_position = { position.x + FRAME_WIDTH / 2, position.y + FRAME_HEIGHT / 2 };

    // 获取玩家的矩形范围
    const POINT& player_position = player.GetPosition();


    // 判断敌人中心是否在玩家矩形内
    bool is_overlap_x = check_position.x >= player_position.x &&
        check_position.x <= player_position.x + player.PLAYER_WIDTH;
    bool is_overlap_y = check_position.y >= player_position.y &&
        check_position.y <= player_position.y + player.PLAYER_HEIGHT;

    return is_overlap_x && is_overlap_y;
}

/**
 * @brief 移动敌人朝向玩家
 * @param player 玩家对象，作为移动目标
 */
void Enemy::Move(const Player& player)
{
    // 获取玩家位置
    const POINT& player_position = player.GetPosition();
    
    // 计算方向向量
    int dir_x = player_position.x - position.x;
    int dir_y = player_position.y - position.y;
    
    // 计算方向向量长度
    double len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);
    
    // 如果长度不为零，则正规化并移动
    if (len_dir != 0)
    {
        // 正规化方向向量
        double normalized_x = dir_x / len_dir;
        double normalized_y = dir_y / len_dir;
        
        // 更新敌人位置
        position.x += (int)(SPEED * normalized_x);
        position.y += (int)(SPEED * normalized_y);
        
        // 更新敌人朝向
        facing_left = (dir_x < 0);
    }
}

/**
 * @brief 绘制敌人及其阴影
 * @param delta 时间增量(毫秒)，用于动画更新
 */
void Enemy::Draw(int delta)
{
    // 计算阴影位置
    int pos_shadow_x = position.x + (FRAME_WIDTH / 2 - SHADOW_WIDTH / 2);
    int pos_shadow_y = position.y + FRAME_HEIGHT - 35;
    
    // 绘制阴影
    putimage_alpha(pos_shadow_x, pos_shadow_y, &img_shadow);

    // 根据朝向绘制相应的动画
    if (facing_left)
        anim_left->Play(position.x, position.y, delta);
    else
        anim_right->Play(position.x, position.y, delta);
}
