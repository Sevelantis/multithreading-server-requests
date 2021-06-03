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

void Resource::removeRequest(Request *pReq, int reqDemand)
{
    // update resource state
    if(state == FULL && (reqDemand == FULL 
        || (state == HALF && reqDemand == HALF)))
    {
        setState(NONE);
    }
    else if(state == HALF2 && reqDemand == HALF)
    {
        setState(HALF);
    }
    // CATCHING UNHANDLED ERRORS
    else if(state == NONE 
            || (state == FULL && reqDemand == HALF)
            || (state == HALF2 && reqDemand == FULL)
            || (state == HALF && reqDemand == FULL))
    {
        clear();
    }

    // request no longer need the resource
    this->requests.erase(std::remove(requests.begin(), requests.end(), pReq), requests.end());
}

std::vector<Request*>& Resource::getRequests()
{
    return requests;
}