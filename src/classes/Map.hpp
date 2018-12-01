#ifndef EVOLUTION_MAP_H
#define EVOLUTION_MAP_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <boost/filesystem.hpp>
#include <SFML/Graphics.hpp>
#include "Hexagon.hpp"


class Pixel;

class Row
{
    std::vector<Hexagon*> row;
public:
    Row() = default;
    ~Row() = default;
    Hexagon*& operator[](size_t index)
    {
        return row[index];
    }

    const Hexagon* operator[](size_t index) const
    {
        return row[index];
    }

    void push_back(Hexagon* hex)
    {
        row.push_back(hex);
    }

    double getPositionX(size_t index)
    {
        return row[index]->GetX();
    }

    double getPositionY(size_t index)
    {
        return row[index]->GetY();
    }

    void erase(size_t index)
    {
        row.erase(row.begin() + index);
    }

    std::vector<Hexagon*>::iterator begin()
    {
        return row.begin();
    }

    void insert(Hexagon* hex, size_t index)
    {
        row.insert(row.begin() + index, hex);
    }
    Hexagon* back()
    {
        return row.back();
    }
};


class Map
{
public:
    Map();
    Map(const std::string&);
    Map(const Map&);
    Map(Map&&);
    ~Map() = default;
    Map& operator=(const Map&);
    Map& operator=(Map&&);
    Row& operator[](size_t);
    const Row& operator[](size_t) const;

    void Update();
    void MultiplyPixels(int);
    void CreateFood(int);
    void SetPoison(int);
    void RecreateMap(const std::vector<Hexagon*>&);
    void ClonePixels(Map&, const std::vector<Hexagon*>&);
    void IncreaseEvolutionNumber();

    unsigned int GetWidth() const;
    unsigned int GetHeight() const;
    unsigned int GetEvolutionNamber() const;
    int GetTimeToSleep() const;

    size_t GetWidthInCells() const;
    size_t GetHeightInCells() const;

    std::vector<Hexagon*> GetOrganisms() const;
    std::vector<Hexagon*> GetStaticOrganisms() const;
    size_t GetNumberOfAliveOrganisms() const;

    void SetStaticOrganisms(std::vector<Hexagon*>);
    void SetOrganism(Hexagon*);
    void IncreaseTimesToSleep(int);
    void DecreaseTimesToSleep(int);
    void SetEvolutionNamber(unsigned int);
    void Swap(Hexagon*, Hexagon*);
    void SaveToFile() const;
    void UploadFromFile();
    void Print(sf::RenderWindow*);
private:
    unsigned int evolutionNumber = 1;
    int timeToSleep = 100;
    static const unsigned int width = 2000;
    static const unsigned int height = 1000;
    static const size_t widthInCells = 94;
    static const size_t heightInCells = 60;
    std::vector<Row> map;
    std::vector<Hexagon*> organisms;
    std::vector<Hexagon*> staticOrganisms;
    int intrand(int a, int b)
    {
        static std::default_random_engine e;
        static std::uniform_int_distribution<> dis(a, b);
        return dis(e);
    }
};

#endif