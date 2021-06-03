#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <utility>

class Resource;
class Request;

class Rectangle
{
private:
    int x_1;
    int y_1;
    int x_2;
    int y_2;

public:
    static int WIDTH;
    static int HEIGHT;
    static int X_START;
    static int Y_START;
    static int Y_SPACE;
    static int Y_HEADER;
    static int Y_HEADER_VALUES;
    static int X_HEADER;
    static int X_HEADER_OFFSET;
    static int X_HEADER_1;
    static int X_HEADER_2;
    static int X_HEADER_3;
    static int X_HEADER_4;

public:
    Rectangle(int x1, int y1);
    Rectangle();
    ~Rectangle();

    void draw(Resource *pRes);
    static void drawRequestInfo(Request *pReq, int i);

private:
    void drawRectBorder(int x1, int y1, int x2, int y2);
    void drawResourceId(int x, int y, int id);
    void drawRequestOnState(Resource *pRes);
    void drawRectRequest(int x1, int y1, int x2, int y2, int idRequest);
    std::pair<int,int> getInfoPos(int x1, int y1, int x2, int y2);
};

#endif //RECTANGLE_H