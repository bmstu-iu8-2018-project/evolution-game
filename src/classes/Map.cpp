#include "Map.hpp"

Map::Map(sf::RenderWindow& window)
{
    Hexagon hex;
    hex.hexagon.setFillColor(sf::Color(66, 170, 255));
    float deltaX = 9;
    float deltaY = 15;
    hex.Y = 0;
    hex.hexagon.setPosition(deltaX, deltaY);
    for (int i = 0; i < 66; ++i)
    {
        hex.hexagon.setOutlineThickness(1);
        hex.hexagon.setOutlineColor(sf::Color::Black);
        hex.X = 0;
        if ((i % 2) != 0)
        {
            hex.X += deltaX;
        }
        for (int j = 0; j < 100; ++j)
        {
            hex.X += 2 * deltaX;
            vecHex.push_back(hex);
            int color = rand() % 6600;
            if (color % 2 == 0)
            {
                hex.hexagon.setFillColor(sf::Color(93, 161, 48)); // Green
            }
            else
            {
                hex.hexagon.setFillColor(sf::Color(66, 170, 255)); // Blue
            }
        }
        hex.Y += deltaY;
    }
}
Map::Hexagon& Map::operator[](int index)
{
    return vecHex[index];
}
const Map::Hexagon& Map::operator[](int index) const
{
    return vecHex[index];
}
size_t Map::Size()
{
    return vecHex.size();
}
