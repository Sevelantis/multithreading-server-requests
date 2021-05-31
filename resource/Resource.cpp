#include "Resource.h"

int Resource::idCntr = 0;

void Resource::draw(int borderColor, int idColor)
{
    rect.draw(id, -1, borderColor, idColor, state);
}

Resource::Resource()
{
    this->id=idCntr++;
    this->state = HALF;
    rect = Rectangle(Rectangle::X_START, Rectangle::Y_START + (Rectangle::HEIGHT + Rectangle::Y_SPACE) * id);
}

Resource::~Resource()
{

}
