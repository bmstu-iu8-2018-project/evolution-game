#include "Map.hpp"
#include "Hexagon.hpp"



Map::Map()
{
    // std::vector<Hexagon::Type> types = {Hexagon::Type::GRASS, Hexagon::Type::WATER, Hexagon::Type::MEDICINE, Hexagon::Type::POISON, Hexagon::Type::SOIL};
    float deltaX = 9;
    float deltaY = 15;
    float x = deltaX * 6;
    float y = deltaY * 6;
    Hexagon hex(Hexagon::Type::GRASS, x, y, 0, 0);
    hex.getHex().setPosition(deltaX, deltaY);
    for (size_t i = 0; i < heightInCells; ++i)
    {
        x = deltaX * 6;
        Row row;
        map.push_back(row);
        if ((i % 2) != 0)
        {
            x += deltaX;
        }
        for (size_t j = 0; j < widthInCells; ++j)
        {
            x += 2 * deltaX;
            int color = rand() % 6600;
            if (color % 3 == 0)
            {
                hex = Hexagon(Hexagon::Type::SOIL, x, y, i, j);
            }
            else if (color % 43 == 0)
            {

                hex = Hexagon(Hexagon::Type::MEDICINE, x, y, i, j);
            }
            else if (color % 100 == 0)
            {

                hex = Hexagon(Hexagon::Type::POISON, x, y, i, j);
            }
            else if (color % 5 == 0)
            {

                hex = Hexagon(Hexagon::Type::GRASS, x, y, i, j);
            }
            else
            {
                hex = Hexagon(Hexagon::Type::WATER, x, y, i, j);
            }
            map[i].push_back(hex);
        }
        y += deltaY;
    }
}

Row& Map::operator[](size_t index)
{
    return map[index];
}

const Row& Map::operator[](size_t index) const
{
    return map[index];
}


unsigned int Map::getWidth()
{
    return width;
}

unsigned int Map::getHeight()
{
    return height;
}

size_t Map::getWidthInCells()
{
    return widthInCells;
}

size_t Map::getHeightInCells()
{
    return heightInCells;
}

void Map::setObject(Hexagon& obj)
{
    map[obj.getCellStr()][obj.getCellCol()] = obj;
}