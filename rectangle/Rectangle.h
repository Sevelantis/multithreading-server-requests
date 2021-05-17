#include <ncurses.h>

struct Rectangle
{
    const static int WIDTH = 10;
    const static int HEIGHT = 5;
    const static int X_START = 60;
    const static int Y_START = 1;
    const static int Y_SPACE = 7;
    int x1;
    int y1;
    int x2;
    int y2;
    
    Rectangle(int x1, int y1)
    {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x1 + WIDTH;
        this->y2 = y1 + HEIGHT;
    }

    Rectangle() = default;

    void draw()
    {
        mvhline(y1, x1, 0, x2-x1);
        mvhline(y2, x1, 0, x2-x1);
        mvvline(y1, x1, 0, y2-y1);
        mvvline(y1, x2, 0, y2-y1);
        mvaddch(y1, x1, ACS_ULCORNER);
        mvaddch(y2, x1, ACS_LLCORNER);
        mvaddch(y1, x2, ACS_URCORNER);
        mvaddch(y2, x2, ACS_LRCORNER);
    }
};