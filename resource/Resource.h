#ifndef P2_RESOURCE_H
#define P2_RESOURCE_H

#include <string>
#include <vector>
#include <random>
#include <mutex>
#include "../rectangle/Rectangle.h"
#include "../request/Request.h"

class Request;

class Resource
{
public:
    Resource();
    ~Resource();
    void draw();
public:
    void setState(int state);
    void addRequest(Request *pReq, int newState);
    void removeRequest(Request *pReq, int state);
public:
    void lock();
    void unlock();
public:
    int getId();
    int getState();
    std::vector<Request*>& getRequests();
    
private:
    static int idCntr;
    int state;
    int id;
private:
    std::vector<Request*> requests;
private:
    Rectangle rect;
    std::mutex mtx;
};

#endif //P2_RESOURCE_H