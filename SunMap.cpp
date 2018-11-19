#include "SunMap.hpp"
#include <utility>

SunMap::SunMap()
{
    std::vector<bool> row(heightInCells, true);
    Tile hex;
    hex.X = deltaX * 4;
    hex.Y = 0;
    hex.hexagon.setFillColor(sf::Color::Yellow);
    hex.hexagon.setOutlineThickness(1);
    hex.hexagon.setOutlineColor(sf::Color::Red);
    for (size_t i = 0; i < widthInCells; ++i)
    {
        if (i == widthInCells / 2)
        {
            row =  std::vector<bool>(heightInCells, false);
            hex.hexagon.setFillColor(sf::Color::Black);
        }
        mapOfSun.push_back(row);
        vectorOfGrafics.push_back(hex);
        hex.X += deltaX;
    }
}

std::vector<SunMap::Tile>& SunMap::getGrafics()
{
    return vectorOfGrafics;
}

void SunMap::Update(sf::RenderWindow* window)
{
    std::vector<bool> col = mapOfSun.back();
    mapOfSun.pop_back();
    mapOfSun.insert(mapOfSun.begin(), col);
    Tile hex = vectorOfGrafics.back();
    for (size_t i = 1; i < widthInCells; ++i)
    {
        vectorOfGrafics[i]. X += deltaX;  //= vectorOfGrafics[i + 1]. X;
    }
    vectorOfGrafics.pop_back();
    vectorOfGrafics.insert(vectorOfGrafics.begin(), hex);
    vectorOfGrafics[0].X = deltaX * 4;
}
std::vector<bool>& SunMap::operator[](size_t index)
{
    return mapOfSun[index];
}

const std::vector<bool>& SunMap::operator[](size_t index) const
{
    return mapOfSun[index];
}

size_t SunMap::getWidthInCells()
{
    return widthInCells;
}

size_t SunMap::getHeightInCells()
{
    return heightInCells;
}
