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
    explicit Pixel();
    Pixel(const double, const double, const size_t, const size_t);
    Pixel(const double, const double, const size_t, const size_t, Brain);
    Pixel(const float xNew, const float yNew, const size_t CellStrNew,
          const size_t CellColNew, const double lifesNew, Brain brainNew);
    Pixel(const float xNew, const float yNew, const size_t CellStrNew,
          const size_t CellColNew, const double lifesNew, Brain brainNew, double medicineNew);
    Pixel(const Pixel&);
     ~Pixel() = default;
    std::vector<Hexagon*> LookAround(Map&) const;
    void Update(Map&);
    void EatingFood(Hexagon*, Map&);
    void Move(Map&, Hexagon*);
    void Reproduction(Map&);
    Hexagon* ViewNearbyCells(Map&, const Type&);
    unsigned int GetNumberOfLifeIterations() const;
    const Brain& GetBrain() const;
    void SetBrain(const Brain&);
    void ResetNumberOfLifeIterations();
    void SaveToFile(const std::string&) const;
    void Print(sf::RenderWindow*) const override;
};

#endif
