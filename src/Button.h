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
    // ���캯������
    Button(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed);

    // Ĭ����������
    virtual ~Button() = default;

    // ���ư�ť����
    void Draw();

    // �����������Ƿ��ڰ�ť����������
    bool CheckCursorHit(int x, int y);

    // ��Ϣ�¼�����������
    void ProcessEvent(const ExMessage& msg);
};

// ��ʼ��Ϸ��ť (������ .h �ļ��У���Ϊʵ�ּ������� extern ����)
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
        extern bool is_game_started;  // �����ⲿ����
        is_game_started = true;       // ������Ϸ��ʼ��־
    }
};

// �˳���Ϸ��ť (������ .h �ļ��У�ԭ��ͬ��)
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