#ifndef EVOLUTION_PIXEL_HPP
#define EVOLUTION_PIXEL_HPP

#include <algorithm>
#include "Hexagon.hpp"
#include "Map.hpp"

class Pixel
        : public Hexagon
{
public:
    Pixel(const double xNew, const double yNew, const size_t CellStrNew, const size_t CellColNew);
    Pixel(const sf::CircleShape hexagon1, const float xNew, const float yNew, const size_t CellStrNew,
          const size_t CellColNew, const double lifesNew, Brain brainNew);
    ~Pixel() override = default;
    Pixel(const Pixel& hex);
    Pixel& operator=(const Hexagon& hex);
    void Update(Map& map);
    std::vector<Hexagon*> LookArond(Map& map) const;
    void EatingFood(Hexagon*);
    void Move(Map&, Hexagon*);
    void Reproduction(Map&);
    bool IsAlive();
    Hexagon* ViewNearbyCells(Map& map, const Type& tmp);
};
/*class Pixel
        : public Hexagon
{
public:
    Pixel(const double, const double, const size_t, const size_t);
    Pixel(const sf::CircleShape hexagon1, const float xNew, const float yNew, const size_t CellStrNew,
            const size_t CellColNew, const double lifesNew, Brain brainNew);
    Pixel& operator=(const Pixel& hexagon1);
    void Swap(Pixel&);
    std::vector<std::shared_ptr<Hexagon>> LookArond(Map&);
    void Update(Map& map);
    void EatingFood(std::shared_ptr<Hexagon>);
    void Move(Map&, std::shared_ptr<Hexagon>);
    void Reproduction(Map&);
    bool IsAlive();
    std::shared_ptr<Hexagon> ViewNearbyCells(Map& map, const Type& tmp);
};*/

#endif //EVOLUTION_PIXEL_HPP
