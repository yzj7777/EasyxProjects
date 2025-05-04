#pragma once
#include <windows.h> // for POINT

class Bullet {
public:
    POINT position = { 0, 0 };

    Bullet() = default;
    ~Bullet() = default;

    void Draw() const;

private:
    const int RADIUS = 10;
};
