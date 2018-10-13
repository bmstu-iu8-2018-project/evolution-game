#ifndef EVOLUTION_MAP_H
#define EVOLUTION_MAP_H

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Map
{
public:
    struct Hexagon
    {
        sf::CircleShape hexagon = sf::CircleShape(10, 6);
        float X;
        float Y;
    };
    Map() = default;
    ~Map() = default;
    Map(sf::RenderWindow& window);
    Hexagon& operator[](size_t index);
    const Hexagon& operator[](size_t index) const;
    size_t Size();
    float getPositionX(size_t index);
    float getPositionY(size_t index);
private:
    std::vector<Hexagon> vecHex;
};

#endif //EVOLUTION_MAP_H