#include "Resource.h"

#include <algorithm>

int Resource::idCntr = 0;

void Resource::draw()
{
    rect.draw(this);
}

Resource::Resource()
{
    this->id=idCntr++;
    this->state = FULL;
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

void Resource::addRequest(Request *req)
{
    requests.push_back(req);
}

void Resource::removeRequest(Request *req)
{
    requests.erase(std::remove(requests.begin(), requests.end(), req), requests.end());
}

std::vector<Request*>& Resource::getRequests()
{
    return requests;
}
