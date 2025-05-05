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
    // 构造函数
    // 参数 rect：按钮区域矩形
    // 参数 path_img_idle：默认状态图片路径
    // 参数 path_img_hovered：悬停状态图片路径
    // 参数 path_img_pushed：按下状态图片路径
    Button(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
    {
        region = rect;

        // 加载各状态图片资源
        loadimage(&img_idle, path_img_idle);
        loadimage(&img_hovered, path_img_hovered);
        loadimage(&img_pushed, path_img_pushed);
    }

    ~Button() = default;  // 默认析构函数

    // 绘制按钮（根据当前状态显示对应图片）
    void Draw()
    {
        switch (status)
        {
        case Status::Idle:
            putimage(region.left, region.top, &img_idle);
            break;
        case Status::Hovered:
            putimage(region.left, region.top, &img_hovered);
            break;
        case Status::Pushed:
            putimage(region.left, region.top, &img_pushed);
            break;
        }
    }

    // 检测鼠标坐标是否在按钮区域内
// 参数 x,y：鼠标绝对坐标
// 返回值：true表示在区域内
    bool CheckCursorHit(int x, int y)
    {
        return x >= region.left && x <= region.right &&
            y >= region.top && y <= region.bottom;
    }

    // 消息事件处理器
    // 参数 msg：消息结构体
    void ProcessEvent(const ExMessage& msg)
    {
        switch (msg.message)
        {
        case WM_MOUSEMOVE:
            // 鼠标移动时更新悬停状态
            if (status == Status::Idle && CheckCursorHit(msg.x, msg.y))
                status = Status::Hovered;
            else if (status == Status::Hovered && !CheckCursorHit(msg.x, msg.y))
                status = Status::Idle;
            break;

        case WM_LBUTTONDOWN:
            // 左键按下时进入按下状态
            if (CheckCursorHit(msg.x, msg.y))
                status = Status::Pushed;
            break;

        case WM_LBUTTONUP:
            // 左键释放时触发点击事件
            if (status == Status::Pushed) {
                status = Status::Hovered;  // 重置按钮状态为悬停
                OnClick();  // 执行子类实现的点击逻辑
            }
            break;

        default:
            break;
        }
    }
};

// 开始游戏按钮
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
        extern bool is_game_started;
        is_game_started = true;
    }
};  // 添加分号

// 退出游戏按钮
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
};  // 添加分号