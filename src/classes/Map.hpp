#ifndef EVOLUTION_MAP_H
#define EVOLUTION_MAP_H

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Hexagon.hpp"

// нужно сделать обновление карты, замерять через какое время трава вырастает

//class Hexagon;

class Row
{
    std::vector<Hexagon> row;
public:
    Row() = default;
    ~Row() = default;
    Hexagon& operator[](size_t index)
    {
        return row[index];
    }
    const Hexagon& operator[](size_t index) const
    {
        return row[index];
    }
    void push_back(Hexagon& hex)
    {
        row.push_back(hex);
    }
    float getPositionX(size_t index)
    {
        return row[index].getX();
    }

    float getPositionY(size_t index)
    {
        return row[index].getY();
    }
};


class Map
{
public:

    Map();
    ~Map() = default;
    Row& operator[](size_t indexX);
    const Row& operator[](size_t index) const;

    unsigned int getWidth();
    unsigned int getHeight();

    size_t getWidthInCells();
    size_t getHeightInCells();

    void setObject(Hexagon&);
private:
    static const unsigned int width = 2000;
    static const unsigned int height = 1000;
    static const size_t widthInCells = 94;
    static const size_t heightInCells = 60;
    std::vector<Row> map;
};

#endif //EVOLUTION_MAP_H