#include "Hexagon.hpp"
#include "Map.hpp"


Hexagon::Hexagon(const Type& type1, double xNew, double yNew, size_t cellStrNew, size_t cellColNew)
        :    type(type1),
             x(xNew),
             y(yNew),
             cellStr(cellStrNew),
             cellCol(cellColNew),
             lifes(99)
{}

Hexagon::Hexagon(const Type& type1,const sf::CircleShape hexagon1, const float xNew, const float yNew, const size_t cellStrNew,
                 const size_t cellColNew, const double lifesNew)
        :    type(type1),
             hexagon(hexagon1),
             x(xNew),
             y(yNew),
             cellStr(cellStrNew),
             cellCol(cellColNew),
             lifes(lifesNew)
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

void Hexagon::SetX(double newX)
{
    x = newX;
}

void Hexagon::SetY(double newY)
{
    y = newY;
}

sf::CircleShape& Hexagon::SetHex()
{
    return hexagon;
}

void Hexagon::SetCellStr(size_t newCellStr)
{
    cellStr = newCellStr;
}

void  Hexagon::SetCellCol(size_t newCellCol)
{
    cellCol = newCellCol;
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

bool Hexagon::IsAlive()
{
    return lifes > 0;
}

void Hexagon::SaveToFile(const std::string& path_to_file) const
{
    std::fstream fl(path_to_file, std::ios::app);
    fl << "    " << "\"x\"" << " : " << x << "," << std::endl;
    fl << "    " << "\"y\"" << " : " << y << "," << std::endl;
    fl << "    " << "\"type\"" << " : " << type << "," << std::endl;
    fl << "    " << "\"medicine\"" << " : " << medicine << "," << std::endl;
    fl << "    " << "\"isHealfy\"" << " : " << isHealfy << "," << std::endl;
    fl.close();
    //  brain.SaveNetworkState(path_to_file);
}
