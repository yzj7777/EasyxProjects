#pragma once
#include <graphics.h>

// 按钮抽象基类：提供基础按钮控件功能
class Button
{
protected:
    // 点击事件回调函数（纯虚函数，需子类实现）
    virtual void OnClick() = 0;

private:
    // 按钮状态枚举
    enum class Status
    {
        Idle = 0,     // 默认状态
        Hovered,      // 鼠标悬停状态
        Pushed        // 按钮按下状态
    };

private:
    RECT region;              // 按钮区域（屏幕坐标）
    IMAGE img_idle;           // 默认状态图片
    IMAGE img_hovered;        // 悬停状态图片
    IMAGE img_pushed;         // 按下状态图片
    Status status = Status::Idle;  // 当前按钮状态

public:
    // 构造函数声明
    Button(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed);

    // 默认析构函数
    virtual ~Button() = default;

    // 绘制按钮声明
    void Draw();

    // 检测鼠标坐标是否在按钮区域内声明
    bool CheckCursorHit(int x, int y);

    // 消息事件处理器声明
    void ProcessEvent(const ExMessage& msg);
};

// 开始游戏按钮 (保持在 .h 文件中，因为实现简单且依赖 extern 变量)
class StartGameButton : public Button
{
public:
    StartGameButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
        : Button(rect, path_img_idle, path_img_hovered, path_img_pushed) {
    }
    ~StartGameButton() = default;

protected:
    void OnClick() override
    {
        extern bool is_game_started;  // 声明外部变量
        is_game_started = true;       // 设置游戏开始标志
    }
};

// 退出游戏按钮 (保持在 .h 文件中，原因同上)
class QuitGameButton : public Button
{
public:
    QuitGameButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
        : Button(rect, path_img_idle, path_img_hovered, path_img_pushed) {
    }
    ~QuitGameButton() = default;

protected:
    void OnClick() override
    {
        extern bool running;
        running = false;
    }
};