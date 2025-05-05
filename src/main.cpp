#include <graphics.h>
#include "GameManager.h"
//测试上传14：57

/**
 * @brief 游戏程序入口
 * @return 程序退出码
 */
int main()
{
    // 创建游戏管理器
    GameManager gameManager;

    // 初始化游戏
    gameManager.Initialize();

    // 运行游戏
    gameManager.Run();

    return 0;
}