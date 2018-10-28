#include "Hexagon.hpp"
#include "Map.hpp"

Hexagon::Hexagon(const Type& type1, double xNew, double yNew, size_t cellStrNew, size_t cellColNew)
        :    type(type1),
             x(xNew),
             y(yNew),
             cellStr(cellStrNew),
             cellCol(cellColNew),
             lifes(99)
{
    if (type1 == Type::FOOD)
    {
        hexagon.setFillColor(sf::Color(93, 161, 48)); // Green
        medicine = rand() % 5;
    }
    else if (type1 == Type::POISON)
    {
        hexagon.setFillColor(sf::Color(207, 66, 52)); // Красный
        medicine = rand() % 12;
    }
    /*else if (type1 == Type::SOIL)
    {
        hexagon.setFillColor(sf::Color(131, 77, 24)); // Коричневый
        Medicine = 0;
    }*/
    else if (type1 == Type::WATER)
    {
        hexagon.setFillColor(sf::Color(66, 170, 255)); // Голубой
        medicine = 0;
    }
    hexagon.setOutlineThickness(1);
    hexagon.setOutlineColor(sf::Color::Black);
}

/*Hexagon::Hexagon(const Hexagon& hex)
    :  type(hex.type),
       x(hex.x),
       y(hex.y),  //  Почему когда объявляю конструктор ничего не работает
       cellStr(hex.cellStr),
       cellCol(hex.cellCol),
       lifes(hex.lifes)
{}*/

Hexagon& Hexagon::operator=(const Hexagon& hex)
{
    if (&hex != this)
    {
        hexagon = hex.hexagon;
        x = hex.x;
        y = hex.y;
        cellStr = hex.cellStr;
        cellCol = hex.cellCol;
        type = hex.type;
        lifes = hex.lifes;
        medicine = hex.medicine;
    }
    return *this;
}
void Hexagon::Swap(Hexagon& hex)
{
    if (this != &hex)
    {
        std::swap(hexagon, hex.hexagon);
        std::swap(type, hex.type);
        std::swap(x, hex.x);
        std::swap(y, hex.y);
        std::swap(lifes, hex.lifes);
        std::swap(cellStr, hex.cellStr);
        std::swap(cellCol, hex.cellCol);
        std::swap(medicine, hex.medicine);
    }
}

double& Hexagon::GetX()
{
    return x;
}

double& Hexagon::GetY()
{
    return y;
}

sf::CircleShape& Hexagon::GetHex()
{
    return hexagon;
}

size_t Hexagon::GetCellStr() const
{
    return cellStr;
}

size_t  Hexagon::GetCellCol() const
{
    return cellCol;
}

Hexagon::Type Hexagon::GetType() const
{
    return type;
}

double& Hexagon::GetLifes()
{
    return lifes;
}
double& Hexagon::GetMedicine()
{
    return medicine;
}
