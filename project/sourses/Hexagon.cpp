#include "Hexagon.hpp"
#include "Map.hpp"


Hexagon::Hexagon(const Type type1, double xNew, double yNew, size_t cellStrNew, size_t cellColNew)
        :    type(type1),
             x(xNew),
             y(yNew),
             cellStr(cellStrNew),
             cellCol(cellColNew),
             lifes(40)
{}

Hexagon& Hexagon::operator=(const Hexagon* hex)
{
    if (hex != this)
    {
        x = hex->x;
        y = hex->y;
        cellStr = hex->cellStr;
        cellCol = hex->cellCol;
        type = hex->type;
        lifes = hex->lifes;
        medicine = hex->medicine;
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

bool Hexagon::GetisHealfy() const
{
    return isHealfy;
}

void Hexagon::SetX(double newX)
{
    x = newX;
}

void Hexagon::SetY(double newY)
{
    y = newY;
}

void Hexagon::SetCellStr(size_t newCellStr)
{
    cellStr = newCellStr;
}

void  Hexagon::SetCellCol(size_t newCellCol)
{
    cellCol = newCellCol;
}


void Hexagon::SetType(Type& typeNew)
{
    type = typeNew;
}

void Hexagon::SetLifes(double newLifes)
{
    lifes = newLifes;
}

void Hexagon::SetMedicine(double newMedicine)
{
    medicine = newMedicine;
}


void Hexagon::ResetMedicine()
{
    medicine = 0;
    isHealfy = true;
}

bool Hexagon::IsAlive()
{
    return lifes > 0;
}

void Hexagon::Print(sf::RenderWindow*) const
{}

