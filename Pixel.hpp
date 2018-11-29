#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <algorithm>
#include <sstream>
#include "Hexagon.hpp"
#include "Food.hpp"
#include "Map.hpp"
#include </home/anastasia/CLionProjects/evolution/tools/json-develop/single_include/nlohmann/json.hpp>

using Json = nlohmann::json;

class Pixel
        : public Hexagon
{
    Brain brain;
    unsigned int numberOfLifeIterations;
public:
    Pixel();
    Pixel(const double, const double, const size_t, const size_t);
    Pixel(const double, const double, const size_t, const size_t, Brain);
    Pixel(const float xNew, const float yNew, const size_t CellStrNew,
          const size_t CellColNew, const double lifesNew, Brain brainNew);
    Pixel(const Pixel& hex);
     ~Pixel() = default;
    Pixel& operator=(const Pixel&);
    std::vector<Hexagon*> LookArond(Map&) const;
    void Update(Map&);
    void EatingFood(Hexagon*, Map&);
    void Move(Map&, Hexagon*);
    void Reproduction(Map&);
    Hexagon* ViewNearbyCells(Map&, const Type&);
    void SaveToFile(const std::string&) const;

    Brain GetBrain() const override;
    unsigned int GetNumberOfLifeIterations() const override;
    void SetNumberOfLifeIterations(unsigned int) override;
    void SetBrain(const Brain&) override;
    void ResetNumberOfLifeIterations() override;
    void Print(sf::RenderWindow*) override;
};

#endif