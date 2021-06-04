#include "Resource.h"
#include <ncurses.h>
#include <algorithm>
#include "../constants/Constants.h"

int Resource::idCntr = 0;

void Resource::draw()
{
    rect.draw(this);
}

Resource::Resource()
{
    this->id=idCntr++;
    this->state = NONE;
    rect = Rectangle(Rectangle::X_START, Rectangle::Y_START + (Rectangle::HEIGHT + Rectangle::Y_SPACE) * id);
}

Resource::~Resource()
{

}

int Resource::getState()
{
    return state;
}

int Resource::getId()
{
    // std::lock_guard<std::mutex> guard(mtx);
    return id;
}

void Resource::lock()
{
    mtx.lock();
}

void Resource::unlock()
{
    mtx.unlock();
}

void Resource::setState(int state)
{
    this->state = state;
}

void Resource::addRequest(Request *pReq, int newState)
{
    setState(newState);
    this->requests.push_back(pReq);
}

void Resource::removeRequest(Request *pReq, int reqState)
{
    // update resource state
    if((state == FULL && reqState == FULL)
        || (state == HALF && reqState == HALF))
        setState(NONE);

    else if(state == HALF2 && reqState == HALF)
        setState(HALF);

    // request no longer need the resource
    this->requests.erase(std::remove(requests.begin(), requests.end(), pReq), requests.end());
}

std::vector<Request*>& Resource::getRequests()
{
    return requests;
}