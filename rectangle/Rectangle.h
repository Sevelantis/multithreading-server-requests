#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <utility>

class Resource;

class Rectangle
{
private:
    int x1;
    int y1;
    int x2;
    int y2;

public:
    static int WIDTH;
    static int HEIGHT;
    static int X_START;
    static int Y_START;
    static int Y_SPACE;

public:
    Rectangle(int x1, int y1);
    Rectangle();
    ~Rectangle();

    void draw(Resource *pRes);

private:
    void drawRectBorder(int x1, int y1, int x2, int y2);
    void drawRectId(int x, int y, int id);
    void drawRectIfState(Resource *pRes);
    void drawRectRequest(int x1, int y1, int x2, int y2, int idRequest);
    std::pair<int,int> getInfoPos(int x1, int y1, int x2, int y2);
};

#endif //RECTANGLE_H