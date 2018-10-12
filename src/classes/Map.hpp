#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Map
{
    struct Hexagon
    {
        sf::CircleShape hexagon = sf::CircleShape(10, 6);
        float X;
        float Y;
    };
    std::vector<Hexagon> vecHex;
public:
    Map() = default;
    ~Map() = default;
    Map(sf::RenderWindow *window);
    Hexagon& operator[](int index);
    const Hexagon& operator[](int index) const;
    size_t Size();
};
