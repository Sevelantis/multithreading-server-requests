#ifndef P2_RESOURCE_H
#define P2_RESOURCE_H

#define NONE     1
#define HALF     2
#define HALF2    3
#define FULL     4

#include <string>
#include "../rectangle/Rectangle.h"

class Resource
{
public:
    Resource();
    ~Resource();
    void draw(int, int);

private:
    static int idCntr;
    int state;
    int id;
    Rectangle rect;
};

#endif //P2_RESOURCE_H