#ifndef EVOLUTION_PIXEL_HPP
#define EVOLUTION_PIXEL_HPP

#include <algorithm>
#include "Hexagon.hpp"
#include "Food.hpp"
#include "Map.hpp"

class Pixel
        : public Hexagon
{
    Brain brain;
public:
    Pixel();
    Pixel(const double, const double, const size_t, const size_t);
    Pixel(const sf::CircleShape hexagon1, const float xNew, const float yNew, const size_t CellStrNew,
          const size_t CellColNew, const double lifesNew, Brain brainNew);
    Pixel(const Pixel& hex);
    virtual ~Pixel() = default;
    Pixel& operator=(const Pixel& hexagon1);
    std::vector<Hexagon*> LookArond(Map&) const;
    void Update(Map&);
    void EatingFood(Hexagon*, Map&);
    void Move(Map&, Hexagon*);
    void Reproduction(Map&);
    Hexagon* ViewNearbyCells(Map&, const Type&);
    void Die();

    Brain GetBrain() const;
    void SetBrain(Brain&);
};

#endif //EVOLUTION_PIXEL_HPP
