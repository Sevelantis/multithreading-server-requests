#ifndef P2_RESOURCE_H
#define P2_RESOURCE_H

#define NONE     1
#define HALF     2
#define HALF2    3
#define FULL     4

#include <string>
#include <vector>
#include "../rectangle/Rectangle.h"
#include "../request/Request.h"

class Resource
{
public:
    Resource();
    ~Resource();
    void draw();

    int getState();
    int getId();
    std::vector<Request*>& getRequests();

    void addRequest(Request *req);
    void removeRequest(Request *req); // may be private

private:
    static int idCntr;
    int state;
    int id;
    Rectangle rect;
    std::vector<Request*> requests;
};

#endif //P2_RESOURCE_H