#pragma once
#include <graphics.h>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

/**
 * @class GameManager
 * @brief 游戏管理器类，负责管理游戏的主要逻辑和资源
 */
class GameManager {
public:
    /**
     * @brief 构造函数
     * 初始化游戏管理器
     */
    GameManager();

    /**
     * @brief 析构函数
     * 释放游戏资源
     */
    ~GameManager();

    /**
     * @brief 初始化游戏
     * 加载资源并设置初始状态
     */
    void Initialize();

    /**
     * @brief 运行游戏
     * 开始游戏主循环
     */
    void Run();

private:
    /**
     * @brief 处理用户输入
     */
    void HandleInput();

    /**
     * @brief 更新游戏状态
     */
    void Update();

    /**
     * @brief 渲染游戏画面
     */
    void Render();

    /**
     * @brief 尝试生成新的敌人
     */
    void TryGenerateEnemy();

    /**
     * @brief 更新子弹位置
     */
    void UpdateBullets();

    /**
     * @brief 检测碰撞
     */
    void CheckCollisions();

    /**
     * @brief 绘制玩家得分
     */
    void DrawPlayerScore();

private:
    // 游戏状态
    bool running;
    int score;

    // 游戏对象
    Player* player;
    std::vector<Enemy*> enemy_list;
    std::vector<Bullet> bullet_list;

    // 资源
    IMAGE img_background;

    // 消息结构体
    ExMessage msg;

    // 常量
    const int WIN_WIDTH = 1280;
    const int WIN_HEIGHT = 720;
    const int ENEMY_SPAWN_INTERVAL = 100;
    static int enemy_spawn_counter;
};