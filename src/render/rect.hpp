#ifndef __RECT__
#define __RECT__

class Rect {
public:
    Rect(const int x, const int y, const int width, const int height);

private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
};

#endif
