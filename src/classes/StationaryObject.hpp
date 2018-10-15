#ifndef STATIONARYOBJECT_HPP
#define STATIONARYOBJECT_HPP

#include "Map.hpp"

// нужен ли метод update?

class StationaryObject
{
public:
    enum Direction
    {
        WEST = 0,
        NORTH_WEST = 45,
        NORTH_EAST = 135,
        EAST = 180,
        EAST_SOUTH = -135,
        SOUTH_WEST = -45,
    };
    enum Type : int
    {
        ORGANICS = 0,
        GRASS = 1,
        PREDATOR = 2
    };
private:
    Map::Hexagon object;
    Direction direction;
    Type type;
public:
    StationaryObject() = default;
    ~StationaryObject() = default;
    //  virtual void Update(float) = 0;
    Type getType();
    void setPosition(Map& map);
    float getX();
    float getY();
    sf::CircleShape getObject();
};

#endif
