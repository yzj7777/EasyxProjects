#include "GameManager.h"
#include <cmath>
#include <mmsystem.h>    // 添加这行，用于mciSendString
#pragma comment(lib, "MSIMG32.LIB")
#pragma comment(lib, "winmm.lib")  // 添加这行，链接Windows多媒体库

// 初始化静态成员变量
int GameManager::enemy_spawn_counter = 0;

// 定义外部变量，供Button类使用
bool is_game_started = false;
bool running = false;

/**
 * @brief GameManager构造函数
 */
GameManager::GameManager()
    : running(false), is_game_started(false), score(0), player(nullptr),
    btn_start_game(nullptr), btn_quit_game(nullptr)
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

    // 释放按钮资源
    if (btn_start_game != nullptr) {
        delete btn_start_game;
        btn_start_game = nullptr;
    }
    if (btn_quit_game != nullptr) {
        delete btn_quit_game;
        btn_quit_game = nullptr;
    }
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
    loadimage(&img_menu, _T("res/img/menu.png"));
    loadimage(&img_background, _T("res/img/background.png"));

    mciSendString(_T("open res/mus/bgm.mp3 alias bgm"), NULL, 0, NULL);
    mciSendString(_T("open res/mus/hit.wav alias hit"), NULL, 0, NULL);
    mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);

    RECT region_btn_start_game, region_btn_quit_game;

    region_btn_start_game.left = (WIN_WIDTH - BUTTON_WIDTH) / 2;
    region_btn_start_game.right = region_btn_start_game.left + BUTTON_WIDTH;
    region_btn_start_game.top = 430;
    region_btn_start_game.bottom = region_btn_start_game.top + BUTTON_HEIGHT;

    region_btn_quit_game.left = (WIN_WIDTH - BUTTON_WIDTH) / 2;
    region_btn_quit_game.right = region_btn_quit_game.left + BUTTON_WIDTH;
    region_btn_quit_game.top = 550;
    region_btn_quit_game.bottom = region_btn_quit_game.top + BUTTON_HEIGHT;

    // 创建按钮对象
    btn_start_game = new StartGameButton(region_btn_start_game,
        _T("res/img/ui_start_idle.png"), _T("res/img/ui_start_hovered.png"), _T("res/img/ui_start_pushed.png"));
    btn_quit_game = new QuitGameButton(region_btn_quit_game,
        _T("res/img/ui_quit_idle.png"), _T("res/img/ui_quit_hovered.png"), _T("res/img/ui_quit_pushed.png"));

    // 创建玩家对象并初始化
    player = new Player(500, 500);
    player->LoadAnimation();

    // 初始化子弹列表
    bullet_list.resize(3);

    // 初始化游戏状态
    ::running = true;  // 使用全局变量
    ::is_game_started = false;  // 使用全局变量
    running = true;  // 类成员变量
    is_game_started = false;  // 类成员变量
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
    while (running && ::running) {  // 检查类成员变量和全局变量
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
        if (!is_game_started) {
            // 在游戏未开始时处理按钮消息
            btn_start_game->ProcessEvent(msg);
            btn_quit_game->ProcessEvent(msg);
            
            // 检查全局变量是否被按钮更改
            if (::is_game_started) {
                is_game_started = true;  // 更新类成员变量
            }
        } else {
            // 游戏开始后处理玩家输入
            if (msg.message == WM_KEYDOWN) {
                player->OnKeyDown(msg.vkcode);
            }
            else if (msg.message == WM_KEYUP) {
                player->OnKeyUp(msg.vkcode);
            }
        }
    }
}

/**
 * @brief 更新游戏状态
 */
void GameManager::Update()
{
    if (!is_game_started) {
        // 游戏未开始时，不更新游戏逻辑
        return;
    }

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
    cleardevice();
    
    if (!is_game_started) {
        // 绘制菜单界面
        putimage(0, 0, &img_menu);
        btn_start_game->Draw();
        btn_quit_game->Draw();
    } else {
        // 绘制游戏界面
        putimage(0, 0, &img_background);
        player->Draw();
        for (Enemy* enemy : enemy_list) {
            enemy->Draw(1000/144);
        }
        for (const Bullet& bullet : bullet_list) {
            bullet.Draw();
        }
        DrawPlayerScore();
    }
    
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

/**
 * @brief 获取玩家得分
 * @return 玩家当前得分
 */
int GameManager::GetScore() const
{
    return score;
}