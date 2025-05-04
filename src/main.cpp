#include <graphics.h>
#include "Player.h"
#include "Enemy.h"

/**
 * @brief 动画测试程序入口
 * @return 程序退出码
 */

 // 生成新的敌人
void TryGenerateEnemy(std::vector<Enemy*>& enemy_list)
{
    const int INTERVAL = 100;
    static int counter = 0;
    if ((++counter) % INTERVAL == 0)
        enemy_list.push_back(new Enemy());
}

// 更新子弹位置
void UpdateBullets(std::vector<Bullet>& bullet_list, const Player& player)
{
    const double RADIAL_SPEED = 0.0045;          // 径向波动速度
    const double TANGENT_SPEED = 0.0055;         // 切向波动速度
    double radian_interval = 2 * 3.14159 / bullet_list.size(); // 子弹之间的弧度间隔
    POINT player_position = player.GetPosition();
    double radius = 100 + 25 * sin(GetTickCount() * RADIAL_SPEED);
    for (size_t i = 0; i < bullet_list.size(); i++)
    {
        double radian = GetTickCount() * TANGENT_SPEED + radian_interval * i; // 当前子弹所在弧度值
        bullet_list[i].position.x = player_position.x + player.PLAYER_WIDTH / 2 + (int)(radius * sin(radian));
        bullet_list[i].position.y = player_position.y + player.PLAYER_HEIGHT / 2 + (int)(radius * cos(radian));
    }
}

int main()
{
    // 初始化图形窗口，设置大小为1280x720
    initgraph(1280, 720);
    
    // 游戏运行标志
    bool running = true;
    
    // 消息结构体，用于接收用户输入
    ExMessage msg;

    // 加载背景图像
    IMAGE img_background;
    loadimage(&img_background, _T("res/img/background.png"));

    // 创建玩家对象并初始化
    Player player(500, 500);  // 在坐标(500,500)创建玩家
    player.LoadAnimation();   // 加载玩家动画资源

    std::vector<Enemy*> enemy_list;
    std::vector<Bullet> bullet_list(3);

    // 开始批量绘制，提高绘图效率
    BeginBatchDraw();

    // 主游戏循环
    while (running)
    {
        // 记录当前帧开始时间
        DWORD start_time = GetTickCount();

        // 处理所有待处理的消息
        while (peekmessage(&msg))
        {
            // 处理按键按下事件
            if (msg.message == WM_KEYDOWN)
            {
                player.OnKeyDown(msg.vkcode);
            }
            // 处理按键释放事件
            else if (msg.message == WM_KEYUP)
            {
                player.OnKeyUp(msg.vkcode);
            }
        }

        // 更新玩家状态
        player.Update();
        UpdateBullets(bullet_list, player);

        TryGenerateEnemy(enemy_list);
        for (Enemy* enemy : enemy_list)
            enemy->Move(player);
        
        // 检测敌人和玩家的碰撞
        for (Enemy* enemy : enemy_list)
        {
            if (enemy->CheckPlayerCollision(player))
            {
                MessageBox(GetHWnd(), _T("You lost"), _T("Game end"), MB_OK);
                running = false;
                break;
            }
        }

        // 清空屏幕准备绘制新帧
        cleardevice();
        
        // 绘制背景
        putimage(0, 0, &img_background);
        
        // 绘制玩家
        player.Draw();
        for (Enemy* enemy : enemy_list)
            enemy->Draw(1000/144);
        for (const Bullet& bullet : bullet_list)
            bullet.Draw();

        // 将缓冲区内容刷新到屏幕
        FlushBatchDraw();

        // 计算当前帧耗时
        DWORD end_time = GetTickCount();
        DWORD delta_time = end_time - start_time;

        // 帧率控制，限制最高144FPS
        if (delta_time < 1000 / 144)
        {
            Sleep(1000 / 144 - delta_time);
        }
    }

    // 结束批量绘制
    EndBatchDraw();
    
    // 关闭图形窗口
    closegraph();
    
    return 0;
}