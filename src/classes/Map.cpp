#include "Map.hpp"
#include "Food.hpp"
#include "Pixel.hpp"


Map::Map()
{
    double deltaX = 9;
    double deltaY = 15;
    double x = deltaX * 6;
    double y = deltaY * 6;
    Hexagon hex(Hexagon::Type::WATER, x, y, 0, 0);
    hex.GetHex().setPosition((float)deltaX, (float)deltaY);
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
            if (color % 43 == 0)
            {

                hex = Pixel(x, y, i, j);
                organisms.push_back(&hex);
            }
            else if (color % 100 == 0)
            {

               hex = Poison(x, y, i, j);
            }
            else if (color % 5 == 0)
            {
                hex = Food(x, y, i, j);
            }
            else
            {
                hex = Water(x, y, i, j);
            }
            map[i].push_back(hex);
        }
        y += deltaY;
    }
}

void Map::Update()
{
    /*for (size_t i = 0; i < organisms.size(); ++i)
    {
        organisms[i]->Update();
    }*/
}

Row& Map::operator[](size_t index)
{
    return map[index];
}

const Row& Map::operator[](size_t index) const
{
    return map[index];
}


unsigned int Map::GetWidth()
{
    return width;
}

unsigned int Map::GetHeight()
{
    return height;
}

size_t Map::GetWidthInCells()
{
    return widthInCells;
}

size_t Map::GetHeightInCells()
{
    return heightInCells;
}

void Map::SetObject(const Hexagon& obj)
{
    map[obj.GetCellStr()][obj.GetCellCol()] = obj;
}