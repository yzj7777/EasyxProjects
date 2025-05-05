#include "Button.h"

// 构造函数实现
Button::Button(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
{
    region = rect;
    status = Status::Idle; // 初始化状态

    // 加载各状态图片资源
    loadimage(&img_idle, path_img_idle);
    loadimage(&img_hovered, path_img_hovered);
    loadimage(&img_pushed, path_img_pushed);
}

// 绘制按钮实现
void Button::Draw()
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

// 检测鼠标坐标是否在按钮区域内实现
bool Button::CheckCursorHit(int x, int y)
{
    return x >= region.left && x <= region.right &&
        y >= region.top && y <= region.bottom;
}

// 消息事件处理器实现
void Button::ProcessEvent(const ExMessage& msg)
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
            // 检查鼠标是否仍在按钮内释放
            if (CheckCursorHit(msg.x, msg.y)) {
                OnClick();  // 执行子类实现的点击逻辑
            }
            // 无论是否在按钮内释放，都恢复到悬停或空闲状态
            if (CheckCursorHit(msg.x, msg.y)) {
                status = Status::Hovered;
            }
            else {
                status = Status::Idle;
            }
        }
        break;
    case WM_MOUSELEAVE: // 可选：处理鼠标离开窗口的情况
        status = Status::Idle;
        break;
    default:
        // 如果鼠标不在按钮上，且按钮当前不是按下状态，则设为空闲
        if (status != Status::Pushed && !CheckCursorHit(msg.x, msg.y)) {
            status = Status::Idle;
        }
        break;
    }
}