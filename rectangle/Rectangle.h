#include <ncurses.h>
#include <string>
#include "../resource/Resource.h"

struct Rectangle
{
    const static int WIDTH = 11;
    const static int HEIGHT = 5;
    const static int X_START = 10;
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

    void draw(int idResource, int idRequest, int borderColor, int idColor, int state)
    {
        // fill rectangle with color if it is being used
        if(state != NONE)   fillRectOnState(state, idRequest);

        //print rectangle border
        attron(COLOR_PAIR(borderColor));
        mvhline(y1, x1, 0, x2-x1);
        mvhline(y2, x1, 0, x2-x1);
        mvvline(y1, x1, 0, y2-y1);
        mvvline(y1, x2, 0, y2-y1);
        mvaddch(y1, x1, ACS_ULCORNER);
        mvaddch(y2, x1, ACS_LLCORNER);
        mvaddch(y1, x2, ACS_URCORNER);
        mvaddch(y2, x2, ACS_LRCORNER);
        attroff(COLOR_PAIR(borderColor));

        //print id
        attron(COLOR_PAIR(idColor));
        mvprintw(y1, x2, std::to_string(idResource).c_str());
        attroff(COLOR_PAIR(idColor));

    }

    void fillRectOnState(int state, int idRequest)
    {
        if(state == HALF)
        {
            int c = 5;
            attron(COLOR_PAIR(c));
            drawRectRequest(this->x1, this->y1, x1 + WIDTH/2 + 1, y1 + HEIGHT + 1, idRequest);attroff(COLOR_PAIR(c)); // unset blue color
        }
        else if(state == HALF2)
        {
            int colorLeft = 6; // green
            int colorRight = 7; // RED

            // left
            attron(COLOR_PAIR(colorLeft));
            drawRectRequest(this->x1, this->y1, x1 + WIDTH/2 + 1, y1 + HEIGHT + 1, idRequest);attroff(COLOR_PAIR(colorLeft));
            // right
            attron(COLOR_PAIR(colorRight));
            drawRectRequest(x1 + WIDTH/2 + 1, this->y1, this->x2, y1 + HEIGHT + 1, idRequest);attroff(COLOR_PAIR(colorRight));
        }
        else if(state == FULL)
        {
            int c = 8; // yellow
            attron(COLOR_PAIR(c));
            drawRectRequest(this->x1, this->y1,this->x2+1, this->y2+1, idRequest);
            attroff(COLOR_PAIR(c));
        }
    }

    void drawRectRequest(int x1, int y1, int x2, int y2, int idRequest)
    {
        for (int i = y1; i < y2; i++)
        {
            for (int j = x1; j < x2; j++)
            {
                mvaddch(i, j, ' ');
            }
        }
        // print id
        std::pair<int,int> pos = getInfoPos(x1,y1,x2,y2);
        mvprintw(pos.second, pos.first, std::to_string(idRequest).c_str());
    }

    std::pair<int,int> getInfoPos(int x1, int y1, int x2, int y2)
    {
        int xoffset = -1;
        int yoffset = -1;
        return std::make_pair((x1+x2)/2+xoffset, (y1+y2)/2+yoffset);
    }
};