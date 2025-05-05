#include "Button.h"

// ���캯��ʵ��
Button::Button(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
{
    region = rect;
    status = Status::Idle; // ��ʼ��״̬

    // ���ظ�״̬ͼƬ��Դ
    loadimage(&img_idle, path_img_idle);
    loadimage(&img_hovered, path_img_hovered);
    loadimage(&img_pushed, path_img_pushed);
}

// ���ư�ťʵ��
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

// �����������Ƿ��ڰ�ť������ʵ��
bool Button::CheckCursorHit(int x, int y)
{
    return x >= region.left && x <= region.right &&
        y >= region.top && y <= region.bottom;
}

// ��Ϣ�¼�������ʵ��
void Button::ProcessEvent(const ExMessage& msg)
{
    switch (msg.message)
    {
    case WM_MOUSEMOVE:
        // ����ƶ�ʱ������ͣ״̬
        if (status == Status::Idle && CheckCursorHit(msg.x, msg.y))
            status = Status::Hovered;
        else if (status == Status::Hovered && !CheckCursorHit(msg.x, msg.y))
            status = Status::Idle;
        break;

    case WM_LBUTTONDOWN:
        // �������ʱ���밴��״̬
        if (CheckCursorHit(msg.x, msg.y))
            status = Status::Pushed;
        break;

    case WM_LBUTTONUP:
        // ����ͷ�ʱ��������¼�
        if (status == Status::Pushed) {
            // �������Ƿ����ڰ�ť���ͷ�
            if (CheckCursorHit(msg.x, msg.y)) {
                OnClick();  // ִ������ʵ�ֵĵ���߼�
            }
            // �����Ƿ��ڰ�ť���ͷţ����ָ�����ͣ�����״̬
            if (CheckCursorHit(msg.x, msg.y)) {
                status = Status::Hovered;
            }
            else {
                status = Status::Idle;
            }
        }
        break;
    case WM_MOUSELEAVE: // ��ѡ����������뿪���ڵ����
        status = Status::Idle;
        break;
    default:
        // �����겻�ڰ�ť�ϣ��Ұ�ť��ǰ���ǰ���״̬������Ϊ����
        if (status != Status::Pushed && !CheckCursorHit(msg.x, msg.y)) {
            status = Status::Idle;
        }
        break;
    }
}