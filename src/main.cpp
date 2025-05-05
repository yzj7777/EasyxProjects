#include <graphics.h>
#include "GameManager.h"
#include <fstream> // 包含文件流头文件
#include <iostream> // 包含标准输入输出流头文件（可选，用于调试）
#include <chrono>   // 包含 chrono 用于时间处理
#include <ctime>    // 包含 ctime 用于时间转换和格式化
#include <iomanip>  // 包含 iomanip 用于 put_time (可选的格式化方式)
#include <sstream>  // 包含 sstream 用于字符串流格式化

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

    // 获取最终得分
    int finalScore = gameManager.GetScore();

    // 获取当前时间
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm;
    localtime_s(&now_tm, &now_c); // 使用 localtime_s 替代 localtime 以提高安全性

    // 格式化日期和时间 (例如: YYYY-MM-DD HH:MM:SS)
    std::stringstream ss;
    ss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
    std::string dateTimeString = ss.str();

    // 将得分和日期时间写入文件
    std::ofstream scoreFile("score.txt", std::ios::app); // 以追加模式打开文件
    if (scoreFile.is_open()) {
        scoreFile << "[" << dateTimeString << "] Player Score: " << finalScore << std::endl; // 在分数前添加日期时间
        scoreFile.close();
    } else {
        // 如果文件无法打开，可以在这里添加错误处理
        std::cerr << "Error: Unable to open score.txt for writing." << std::endl;
    }


    return 0;
}