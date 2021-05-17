#ifndef P2_RESOURCE_H
#define P2_RESOURCE_H

#include <string>
#include "../rectangle/Rectangle.h"

class Resource
{
public:
    Resource();
    ~Resource();

    void draw();

private:
    static int idCntr;
    int id;
    Rectangle rect;
};

#endif //P2_RESOURCE_H