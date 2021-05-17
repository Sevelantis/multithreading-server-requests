#include "Resource.h"

int Resource::idCntr = 0;

void Resource::draw()
{
    rect.draw();
}

Resource::Resource()
{
    this->id=idCntr++;
    rect = Rectangle(Rectangle::X_START, 
            Rectangle::Y_START + (Rectangle::HEIGHT + Rectangle::Y_SPACE) * id);
}

Resource::~Resource()
{

}
