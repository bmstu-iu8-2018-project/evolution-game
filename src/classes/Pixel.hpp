#ifndef EVOLUTION_PIXEL_HPP
#define EVOLUTION_PIXEL_HPP

#include "Hexagon.hpp"
#include "Map.hpp"
#include "Brain.hpp"

class Pixel
        : public Hexagon
{
    Brain* brain;
public:
    Pixel();
    Pixel(const double, const double, const size_t, const size_t);
    Pixel(const sf::CircleShape hexagon1, const float xNew, const float yNew, const size_t CellStrNew,
            const size_t CellColNew, const double lifesNew, Brain* brainNew);
    ~Pixel();
    Pixel& operator=(const Pixel& hexagon1);
    void Swap(Pixel&);
    std::vector<Hexagon*> LookArond(Map&);
    void Update(Map& map);
    void EatingFood(Hexagon* hexagon1);
    void Move(Hexagon* hexagon1);
    void Reproduction(Map&);
    bool IsAlive();
    Hexagon* ViewNearbyCells(Map& map, const Type& tmp);
};

#endif //EVOLUTION_PIXEL_HPP
