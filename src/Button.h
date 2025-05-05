#pragma once
#include <graphics.h>

// ��ť������ࣺ�ṩ������ť�ؼ�����
class Button
{
protected:
    // ����¼��ص����������麯����������ʵ�֣�
    virtual void OnClick() = 0;

private:
    // ��ť״̬ö��
    enum class Status
    {
        Idle = 0,     // Ĭ��״̬
        Hovered,      // �����ͣ״̬
        Pushed        // ��ť����״̬
    };

private:
    RECT region;              // ��ť������Ļ���꣩
    IMAGE img_idle;           // Ĭ��״̬ͼƬ
    IMAGE img_hovered;        // ��ͣ״̬ͼƬ
    IMAGE img_pushed;         // ����״̬ͼƬ
    Status status = Status::Idle;  // ��ǰ��ť״̬


public:
    // ���캯��
    // ���� rect����ť�������
    // ���� path_img_idle��Ĭ��״̬ͼƬ·��
    // ���� path_img_hovered����ͣ״̬ͼƬ·��
    // ���� path_img_pushed������״̬ͼƬ·��
    Button(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
    {
        region = rect;

        // ���ظ�״̬ͼƬ��Դ
        loadimage(&img_idle, path_img_idle);
        loadimage(&img_hovered, path_img_hovered);
        loadimage(&img_pushed, path_img_pushed);
    }

    ~Button() = default;  // Ĭ����������

    // ���ư�ť�����ݵ�ǰ״̬��ʾ��ӦͼƬ��
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

    // �����������Ƿ��ڰ�ť������
// ���� x,y������������
// ����ֵ��true��ʾ��������
    bool CheckCursorHit(int x, int y)
    {
        return x >= region.left && x <= region.right &&
            y >= region.top && y <= region.bottom;
    }

    // ��Ϣ�¼�������
    // ���� msg����Ϣ�ṹ��
    void ProcessEvent(const ExMessage& msg)
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
                status = Status::Hovered;  // ���ð�ť״̬Ϊ��ͣ
                OnClick();  // ִ������ʵ�ֵĵ���߼�
            }
            break;

        default:
            break;
        }
    }
};

// ��ʼ��Ϸ��ť
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
};  // ��ӷֺ�

// �˳���Ϸ��ť
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
};  // ��ӷֺ�