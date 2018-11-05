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
   // brain = std::make_shared<Brain>(nullptr);
    /*if (type1 == Type::FOOD)
    {
        hexagon.setFillColor(sf::Color(93, 161, 48)); // Green
        medicine = rand() % 5;
    }
    else if (type1 == Type::POISON)
    {
        hexagon.setFillColor(sf::Color(207, 66, 52)); // Красный
        medicine = rand() % 12;
    }*/
    /*else if (type1 == Type::SOIL)
    {
        hexagon.setFillColor(sf::Color(131, 77, 24)); // Коричневый
        Medicine = 0;
    }*/
    /*else if (type1 == Type::WATER)
    {
        hexagon.setFillColor(sf::Color(66, 170, 255)); // Голубой
        medicine = 0;
    }
    hexagon.setOutlineThickness(1);
    hexagon.setOutlineColor(sf::Color::Black);*/
}

Hexagon::Hexagon(const Type& type1,const sf::CircleShape hexagon1, const float xNew, const float yNew, const size_t cellStrNew,
                 const size_t cellColNew, const double lifesNew, Brain brainNew)
        :    type(type1),
             hexagon(hexagon1),
             x(xNew),
             y(yNew),
             cellStr(cellStrNew),
             cellCol(cellColNew),
             lifes(lifesNew),
             brain(brainNew)
{
    hexagon.setOutlineThickness(1);
    hexagon.setOutlineColor(sf::Color::Black);
}

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
        //  std::swap(hexagon.getFillColor(), hex.hexagon.getFillColor());
        /*sf::Color copy = hexagon.getFillColor();
        hexagon.setFillColor(hex.hexagon.getFillColor());
        hex.hexagon.setFillColor(copy);
        //hexagon.setFillColor(sf::Color::White);
        //hex.hexagon.setFillColor(sf::Color(66, 170, 255));
        //std::swap(hexagon, hex.hexagon);
        //sf::Color a = hexagon.getFillColor();
        // sf::Color b =  hex.hexagon.getFillColor();
        std::swap(type, hex.type);
        std::swap(lifes, hex.lifes);
        std::swap(medicine, hex.medicine);
        std::swap(brain, hex.brain);*/
        std::swap(x, hex.x);
        std::swap(y, hex.y);
        std::swap(cellStr, hex.cellStr);
        std::swap(cellCol, hex.cellCol);
        //std::swap(hexagon, hex.hexagon);
        //hexagon.setFillColor(sf::Color(66, 170, 255));
    }
}


double Hexagon::GetX() const
{
    return x;
}

double Hexagon::GetY() const
{
    return y;
}

sf::CircleShape Hexagon::GetHex() const
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

double Hexagon::GetLifes() const
{
    return lifes;
}
double Hexagon::GetMedicine() const
{
    return medicine;
}
double& Hexagon::SetX()
{
    return x;
}

double& Hexagon::SetY()
{
    return y;
}

sf::CircleShape& Hexagon::SetHex()
{
    return hexagon;
}

size_t& Hexagon::SetCellStr()
{
    return cellStr;
}

size_t&  Hexagon::SetCellCol()
{
    return cellCol;
}

Hexagon::Type& Hexagon::SetType()
{
    return type;
}

double& Hexagon::SetLifes()
{
    return lifes;
}
double& Hexagon::SetMedicine()
{
    return medicine;
}
