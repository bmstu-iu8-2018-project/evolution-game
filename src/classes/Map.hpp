#ifndef EVOLUTION_MAP_H
#define EVOLUTION_MAP_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Hexagon.hpp"

class Pixel;

class Row
{
    std::vector<std::shared_ptr<Hexagon>> row;
public:
    Row() = default;
    ~Row() = default;
    Hexagon& operator[](size_t index)
    {
        return *row[index];
    }
    const Hexagon& operator[](size_t index) const
    {
        return *row[index];
    }
    void push_back(const std::shared_ptr<Hexagon> hex)
    {
        row.push_back(hex);
    }
    const double getPositionX(size_t index) const
    {
        return row[index]->GetX();
    }

    const double getPositionY(size_t index) const
    {
        return row[index]->GetY();
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

    unsigned int GetWidth() const;
    unsigned int GetHeight() const;

    size_t GetWidthInCells() const;
    size_t GetHeightInCells() const;

    void SetObject(const Hexagon&);
    void Swap(std::shared_ptr<Hexagon>, std::shared_ptr<Hexagon>);
private:
    static const unsigned int width = 2000;
    static const unsigned int height = 1000;
    static const size_t widthInCells = 94;
    static const size_t heightInCells = 60;
    std::vector<Row> map;
    std::vector<std::shared_ptr<Pixel>> organisms;
};

#endif