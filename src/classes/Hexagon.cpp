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

Hexagon::Hexagon(const Type& type1, const float xNew, const float yNew, const size_t cellStrNew,
                 const size_t cellColNew, const double lifesNew)
        :    type(type1),
             x(xNew),
             y(yNew),
             cellStr(cellStrNew),
             cellCol(cellColNew),
             lifes(lifesNew)
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

bool Hexagon::GetisHealfy() const
{
    return isHealfy;
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

Brain Hexagon::GetBrain() const
{}

unsigned int Hexagon::GetNumberOfLifeIterations() const
{}

void Hexagon::ResetNumberOfLifeIterations()
{}

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

void Hexagon::SetBrain(const Brain&)
{}

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
}

bool Hexagon::IsAlive()
{
    return lifes > 0;
}

void Hexagon::Print(sf::RenderWindow*) const
{}

void Hexagon::SaveToFile(const std::string& path_to_file) const
{
    std::fstream fl(path_to_file, std::ios::app);
    fl << "\t\t\t\t" << "\"cellStr\"" << " : " << cellStr << "," << std::endl;
    fl << "\t\t\t\t" << "\"cellCol\"" << " : " << cellCol << "," << std::endl;
    fl << "\t\t\t\t" << "\"x\"" << " : " << x << "," << std::endl;
    fl << "\t\t\t\t" << "\"y\"" << " : " << y << "," << std::endl;
    fl << "\t\t\t\t" << "\"type\"" << " : " << type << "," << std::endl;
    fl << "\t\t\t\t" << "\"medicine\"" << " : " << medicine << "," << std::endl;
    fl << "\t\t\t\t" << "\"isHealfy\"" << " : " << isHealfy << std::endl;
    fl.close();
}
