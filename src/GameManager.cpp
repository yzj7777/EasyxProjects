#include "GameManager.h"
#include <cmath>
#include <mmsystem.h>    // 添加这行，用于mciSendString
#pragma comment(lib, "MSIMG32.LIB")
#pragma comment(lib, "winmm.lib")  // 添加这行，链接Windows多媒体库

// 初始化静态成员变量
int GameManager::enemy_spawn_counter = 0;

/**
 * @brief GameManager构造函数
 */
GameManager::GameManager()
    : running(false), score(0), player(nullptr)
{
}

/**
 * @brief GameManager析构函数
 * 释放游戏资源
 */
GameManager::~GameManager()
{
    // 释放玩家资源
    if (player != nullptr) {
        delete player;
        player = nullptr;
    }

    // 释放敌人资源
    for (Enemy* enemy : enemy_list) {
        delete enemy;
    }
    enemy_list.clear();
}

/**
 * @brief 初始化游戏
 * 加载资源并设置初始状态
 */
void GameManager::Initialize()
{
    // 初始化图形窗口
    initgraph(WIN_WIDTH, WIN_HEIGHT);
    
    // 加载背景图像
    loadimage(&img_background, _T("res/img/background.png"));

    mciSendString(_T("open res/mus/bgm.mp3 alias bgm"), NULL, 0, NULL);
    mciSendString(_T("open res/mus/hit.wav alias hit"), NULL, 0, NULL);
    mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);

    // 创建玩家对象并初始化
    player = new Player(500, 500);
    player->LoadAnimation();

    // 初始化子弹列表
    bullet_list.resize(3);

    // 初始化游戏状态
    running = true;
    score = 0;

    // 开始批量绘制，提高绘图效率
    BeginBatchDraw();
}

/**
 * @brief 运行游戏
 * 开始游戏主循环
 */
void GameManager::Run()
{
    while (running) {
        // 记录当前帧开始时间
        DWORD start_time = GetTickCount();

        // 处理用户输入
        HandleInput();

        // 更新游戏状态
        Update();

        // 渲染游戏画面
        Render();

        // 计算当前帧耗时
        DWORD end_time = GetTickCount();
        DWORD delta_time = end_time - start_time;

        // 帧率控制，限制最高144FPS
        if (delta_time < 1000 / 144) {
            Sleep(1000 / 144 - delta_time);
        }
    }

    // 结束批量绘制
    EndBatchDraw();
    
    // 关闭图形窗口
    closegraph();
}

/**
 * @brief 处理用户输入
 */
void GameManager::HandleInput()
{
    // 处理所有待处理的消息
    while (peekmessage(&msg)) {
        // 处理按键按下事件
        if (msg.message == WM_KEYDOWN) {
            player->OnKeyDown(msg.vkcode);
        }
        // 处理按键释放事件
        else if (msg.message == WM_KEYUP) {
            player->OnKeyUp(msg.vkcode);
        }
    }
}

/**
 * @brief 更新游戏状态
 */
void GameManager::Update()
{
    // 更新玩家状态
    player->Update();
    
    // 更新子弹位置
    UpdateBullets();

    // 尝试生成新的敌人
    TryGenerateEnemy();
    
    // 更新敌人状态
    for (Enemy* enemy : enemy_list) {
        enemy->Move(*player);
    }

    // 检测碰撞
    CheckCollisions();
}

/**
 * @brief 渲染游戏画面
 */
void GameManager::Render()
{
    // 清空屏幕准备绘制新帧
    cleardevice();
    
    // 绘制背景
    putimage(0, 0, &img_background);
    
    // 绘制游戏对象
    player->Draw();
    for (Enemy* enemy : enemy_list) {
        enemy->Draw(1000/144);
    }
    for (const Bullet& bullet : bullet_list) {
        bullet.Draw();
    }
    
    // 绘制玩家得分
    DrawPlayerScore();

    // 将缓冲区内容刷新到屏幕
    FlushBatchDraw();
}

/**
 * @brief 尝试生成新的敌人
 */
void GameManager::TryGenerateEnemy()
{
    if ((++enemy_spawn_counter) % ENEMY_SPAWN_INTERVAL == 0) {
        Enemy* enemy = new Enemy();
        enemy_list.push_back(enemy);
    }
}

/**
 * @brief 更新子弹位置
 */
void GameManager::UpdateBullets()
{
    const double RADIAL_SPEED = 0.0045;          // 径向波动速度
    const double TANGENT_SPEED = 0.0055;         // 切向波动速度
    double radian_interval = 2 * 3.14159 / bullet_list.size(); // 子弹之间的弧度间隔
    POINT player_position = player->GetPosition();
    double radius = 100 + 25 * sin(GetTickCount() * RADIAL_SPEED);
    
    for (size_t i = 0; i < bullet_list.size(); i++) {
        double radian = GetTickCount() * TANGENT_SPEED + radian_interval * i; // 当前子弹所在弧度值
        bullet_list[i].position.x = player_position.x + player->PLAYER_WIDTH / 2 + (int)(radius * sin(radian));
        bullet_list[i].position.y = player_position.y + player->PLAYER_HEIGHT / 2 + (int)(radius * cos(radian));
    }
}

/**
 * @brief 检测碰撞
 */
void GameManager::CheckCollisions()
{
    // 检测敌人和玩家的碰撞
    for (Enemy* enemy : enemy_list) {
        if (enemy->CheckPlayerCollision(*player)) {
            static TCHAR text[128];
            _stprintf_s(text, _T("%d"), score);
            MessageBox(GetHWnd(), text, _T("game end"), MB_OK);
            running = false;
            break;
        }
    }

    // 检测子弹和敌人的碰撞
    for (Enemy* enemy : enemy_list) {
        for (const Bullet& bullet : bullet_list) {
            if (enemy->CheckBulletCollision(bullet)) {
                mciSendString(_T("play hit from 0"), NULL, 0, NULL);
                enemy->Hurt();
                score++;
            }
        }
    }

    // 移除生命值归零的敌人
    for (size_t i = 0; i < enemy_list.size(); i++) {
        Enemy* enemy = enemy_list[i];
        if (!enemy->CheckAlive()) {
            std::swap(enemy_list[i], enemy_list.back());
            enemy_list.pop_back();
            delete enemy;
            i--; // 调整索引，因为当前位置现在有一个新元素
        }
    }
}

/**
 * @brief 绘制玩家得分
 */
void GameManager::DrawPlayerScore()
{
    static TCHAR text[64];
    _stprintf_s(text, _T("%d"), score);

    setbkmode(TRANSPARENT);
    settextcolor(RGB(255, 85, 185));
    outtextxy(10, 10, text);
}