#include "Rectangle.h"
#include <ncurses.h>
#include <string>
#include "../resource/Resource.h"

#define COLOR_ID_RESOURCE   1
#define COLOR_BORDER        2  

int Rectangle::WIDTH = 11;
int Rectangle::HEIGHT = 5;
int Rectangle::X_START = 10;
int Rectangle::Y_START = 1;
int Rectangle::Y_SPACE = 7;

int x1;
int y1;
int x2;
int y2;

Rectangle::Rectangle(int x1, int y1)
{
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x1 + WIDTH;
    this->y2 = y1 + HEIGHT;
}

void Rectangle::draw(Resource *pRes)
{
    // fill rectangle with color if it is being used
    if(pRes->getState() != NONE)   drawRectIfState(pRes);

    //print rectangle border
    drawRectBorder(x1, y1, x2, y2);

    //print id
    drawRectId(y1, x2, pRes->getId());
}

void Rectangle::drawRectBorder(int x1, int y1, int x2, int y2)
{
    attron(COLOR_PAIR(COLOR_BORDER));
    mvhline(y1, x1, 0, x2-x1);
    mvhline(y2, x1, 0, x2-x1);
    mvvline(y1, x1, 0, y2-y1);
    mvvline(y1, x2, 0, y2-y1);
    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
    attroff(COLOR_PAIR(COLOR_BORDER));
}

void Rectangle::drawRectId(int x, int y, int id)
{
    attron(COLOR_PAIR(COLOR_ID_RESOURCE));
    mvprintw(y1, x2, std::to_string(id).c_str());
    attroff(COLOR_PAIR(COLOR_ID_RESOURCE));
}

void Rectangle::drawRectIfState(Resource *pRes)
{
    int state = pRes->getState();
    int idRequest = -1;
    
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

void Rectangle::drawRectRequest(int x1, int y1, int x2, int y2, int idRequest)
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

std::pair<int,int> Rectangle::getInfoPos(int x1, int y1, int x2, int y2)
{
    int xoffset = -1;
    int yoffset = -1;
    return std::make_pair((x1+x2)/2+xoffset, (y1+y2)/2+yoffset);
}

Rectangle::Rectangle()
{

}

Rectangle::~Rectangle()
{

}