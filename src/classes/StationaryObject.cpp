#include "StationaryObject.hpp"

StationaryObject::Type StationaryObject::getType()
{
    return type;
}

void StationaryObject::setPosition(Map &map)
{
    size_t pos = rand() % map.Size();
    object.X = map.getPositionX(pos);
    object.Y = map.getPositionY(pos);
    object.hexagon.setPosition(object.X, object.Y);
}

sf::CircleShape StationaryObject::getObject()
{
    return object.hexagon;
}

float StationaryObject::getX()
{
    return object.X;
}

float StationaryObject::getY()
{
    return object.Y;
}