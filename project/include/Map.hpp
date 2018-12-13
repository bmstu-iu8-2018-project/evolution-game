#ifndef MAP_H
#define MAP_H

#include <iomanip>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include <boost/filesystem.hpp>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include "Food.hpp"
#include "Hexagon.hpp"

using Json = nlohmann::json;

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

    void erase(size_t index)
    {
        row.erase(row.begin() + index);
    }

    void insert(Hexagon* hex, size_t index)
    {
        row.insert(row.begin() + index, hex);
    }

    std::vector<Hexagon*>::iterator begin()
    {
        return row.begin();
    }

    Hexagon* back()
    {
        return row.back();
    }
};


class Map
{
public:
    Map(size_t widthCells = 94, size_t heightCells = 60);
    Map(const std::string&, int);
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
    void RecreateMap(const std::vector<Pixel*>&);
    void ClonePixels(Map&, const std::vector<Pixel*>&);
    std::vector<Pixel*> Selection(const std::vector<Pixel*>&);

    unsigned int GetWidth() const;
    unsigned int GetHeight() const;

    size_t GetWidthInCells() const;
    size_t GetHeightInCells() const;

    std::vector<Pixel*> GetOrganisms() const;
    std::vector<Pixel*> GetStaticOrganisms() const;
    size_t GetNumberOfAliveOrganisms() const;

    unsigned int GetEvolutionNumber() const;
    void IncreaseEvolutionNumber();

    int GetTimeToSleep() const;

    void IncreaseTimesToSleep(int);
    void DecreaseTimesToSleep(int);

    Wall* GetWall() const;

    void SetOrganism(Pixel*);
    void Swap(Hexagon*, Hexagon*);
    void SaveToFile() const;
    void UploadFromFile(int);
    void Print(sf::RenderWindow*) const;

private:
    static const unsigned int width = 2000;
    static const unsigned int height = 1000;
    size_t widthInCells = 94;
    size_t heightInCells = 60;
    std::vector<Row> map;
    std::vector<Pixel*> organisms;
    std::vector<Pixel*> staticOrganisms;
    Wall* wall;
    int evolutionNumber = 1;
    int timeToSleep = 100;
};

#endif