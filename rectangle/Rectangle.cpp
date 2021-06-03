#include "Rectangle.h"
#include <ncurses.h>
#include <string>
#include "../constants/Constants.h"
#include "../resource/Resource.h"

int Rectangle::WIDTH = 11;
int Rectangle::HEIGHT = 5;
int Rectangle::X_START = 10;
int Rectangle::Y_START = 1;
int Rectangle::Y_SPACE = 4;
int Rectangle::Y_HEADER = Y_START;
int Rectangle::Y_HEADER_VALUES = Y_START + 1;

// header xs and ys
int Rectangle::X_HEADER_OFFSET = 22;
int Rectangle::X_HEADER = X_START + WIDTH + 3;
int Rectangle::X_HEADER_1 = X_HEADER + X_HEADER_OFFSET*1;
int Rectangle::X_HEADER_2 = X_HEADER + X_HEADER_OFFSET*2;
int Rectangle::X_HEADER_3 = X_HEADER + X_HEADER_OFFSET*3;
int Rectangle::X_HEADER_4 = X_HEADER + X_HEADER_OFFSET*4;

int x_1;
int y_1;
int x_2;
int y_2;


Rectangle::Rectangle(int x1, int y1)
{
    this->x_1 = x1;
    this->y_1 = y1;
    this->x_2 = x1 + WIDTH;
    this->y_2 = y1 + HEIGHT;
}

void Rectangle::draw(Resource *pRes)
{
    // fill rectangle with color if it is being used
    if(pRes->getState() != NONE)   drawRequestOnState(pRes);

    //print rectangle border
    drawRectBorder(x_1, y_1, x_2, y_2);

    //print id
    drawResourceId(y_1, x_2, pRes->getId());
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

void Rectangle::drawResourceId(int x, int y, int id)
{
    attron(COLOR_PAIR(COLOR_ID_RESOURCE));
    mvprintw(x, y, std::to_string(id).c_str());
    attroff(COLOR_PAIR(COLOR_ID_RESOURCE));
}

void Rectangle::drawRequestOnState(Resource *pRes)
{
    int state = pRes->getState();
    std::vector<Request*>& requests = pRes->getRequests();

    if(requests.size() > 2) // TOO MUCH REQUESTS
        clear();

    int it = 0;
    for(auto req : requests)
    {
        int idRequest = req->getId();
        int c = req->getColor();
        
        attron(COLOR_PAIR(c));
        if(state == HALF)
        {
            drawRectRequest(x_1, y_1, x_1 + WIDTH/2 + 1, y_1 + HEIGHT + 1, idRequest);
        }
        else if(state == HALF2)
        {
            if(it == 0) // left
            { 
                drawRectRequest(x_1, y_1, x_1 + WIDTH/2 + 1, y_1 + HEIGHT + 1, idRequest);
            }
            else if(it == 1) // right
            {
                drawRectRequest(x_1 + WIDTH/2 + 1, y_1, x_2, y_1 + HEIGHT + 1, idRequest);
            }
        }
        else if(state == FULL)
        {
            drawRectRequest(x_1, y_1, x_2+1, y_2+1, idRequest);
        }
        attroff(COLOR_PAIR(c));
        
        it++;
    }
}

void Rectangle::drawRequestInfo(Request *pReq, int i)
{
    auto info = pReq->getInfo();
    int yRow = Y_HEADER+4+i*2;
    int c = pReq->getColor();
    attron(COLOR_PAIR(c));
    mvprintw(yRow, X_HEADER, info[0].c_str());
    mvprintw(yRow, X_HEADER_1, info[1].c_str());
    mvprintw(yRow, X_HEADER_2, info[2].c_str());
    mvprintw(yRow, X_HEADER_3, info[3].c_str());
    mvprintw(yRow, X_HEADER_4, info[4].c_str());

    // line under
    mvprintw(yRow+1, X_HEADER_1, info[5].c_str());
    mvprintw(yRow+1, X_HEADER_2, info[6].c_str());
    mvprintw(yRow+1, X_HEADER_3, info[7].c_str());
    attroff(COLOR_PAIR(c));
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