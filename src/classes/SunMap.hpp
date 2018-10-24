#ifndef SUNMAP_HPP
#define SUNMAP_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class SunMap
{
public:
    struct Tile
    {
        sf::CircleShape hexagon = sf::CircleShape(10, 6);
        float X;
        float Y;
    };
private:
    std::vector<std::vector<bool>> mapOfSun;
    std::vector<Tile> vectorOfGrafics;
public:
    SunMap();
    ~SunMap() = default;
    std::vector<bool>& operator[](size_t);
    const std::vector<bool>& operator[](size_t) const;
    void Update(sf::RenderWindow*);

    size_t getWidthInCells();
    size_t getHeightInCells();
    std::vector<Tile>& getGrafics();
private:
    static const size_t widthInCells = 94;
    static const size_t heightInCells = 60;
    float deltaX = 18;
};

#endif
