#ifndef EVOLUTION_MAP_H
#define EVOLUTION_MAP_H

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Hexagon.hpp"


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
    double getPositionX(size_t index)
    {
        return row[index].GetX();
    }

    double getPositionY(size_t index)
    {
        return row[index].GetY();
    }
};


class Map
{
public:
    Map();
    ~Map() = default;
    Row& operator[](size_t indexX);
    const Row& operator[](size_t index) const;

    void Update();

    unsigned int GetWidth();
    unsigned int GetHeight();

    size_t GetWidthInCells();
    size_t GetHeightInCells();

    void SetObject(const Hexagon&);
private:
    static const unsigned int width = 2000;
    static const unsigned int height = 1000;
    static const size_t widthInCells = 94;
    static const size_t heightInCells = 60;
    std::vector<Row> map;
    std::vector<Hexagon*> organisms;
};

#endif