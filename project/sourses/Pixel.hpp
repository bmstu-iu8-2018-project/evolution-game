#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <algorithm>
#include "Hexagon.hpp"
#include "Food.hpp"
#include "Map.hpp"
#include <nlohmann/json.hpp>

using Json = nlohmann::json;

class Pixel
        : public Hexagon
{
    Brain brain;
    unsigned int numberOfLifeIterations;
    int howMuchFoodAte;
    int howMuchPoisonAte;
public:
    explicit Pixel();
    Pixel(double, double, size_t, size_t);
    Pixel(double, double, size_t,  size_t, const Brain&);
    Pixel(double xNew, double yNew, size_t CellStrNew,
          size_t CellColNew, double lifesNew, const Brain& brainNew);
    Pixel(double xNew, double yNew, size_t CellStrNew,
          size_t CellColNew, double lifesNew, const Brain& brainNew, double medicineNew);
    Pixel(const Pixel&);

    std::vector<Hexagon*> LookAround(Map&) const;
    void Update(Map&);
    void EatingFood(Hexagon*, Map&);
    void Move(Map&, Hexagon*);
    void Reproduction(Map&);
    Hexagon* ViewNearbyCells(Map&, const Type&);
    unsigned int GetNumberOfLifeIterations() const;
    const Brain& GetBrain() const;
    int GetHowMuchFoodAte() const;
    int GetHowMuchPoisonAte() const;
    void SetBrain(const Brain&);
    void ResetNumberOfLifeIterations();
    void Print(sf::RenderWindow*) const override;
    const Json getJson() const;
};

#endif
