#include "Pixel.hpp"

Pixel::Pixel()
{
    numberOfLifeIterations = 1;
    brain = Brain();
    lifes = 99;
    howMuchFoodAte = 0;
    howMuchPoisonAte = 0;
}

Pixel::Pixel(double xNew, double yNew, size_t CellStrNew, size_t CellColNew)
        :    Hexagon(Type::PIXEL, xNew, yNew, CellStrNew, CellColNew)
{
    numberOfLifeIterations = 1;
    medicine = 0;
    lifes = 99;
    howMuchFoodAte = 0;
    howMuchPoisonAte = 0;
}

Pixel::Pixel(double xNew, double yNew, size_t CellStrNew, size_t CellColNew, const Brain& newBrain)
        :    Hexagon(Type::PIXEL, xNew, yNew, CellStrNew, CellColNew),
             brain(newBrain)
{
    numberOfLifeIterations = 1;
    medicine = 0;
    lifes = 99;
}

Pixel::Pixel(double xNew, double yNew, const size_t CellStrNew,
             size_t CellColNew, double lifesNew, const Brain& brainNew, double medicineNew)
        :    Hexagon(Type::PIXEL, xNew, yNew, CellStrNew, CellColNew),
             brain(brainNew),
             numberOfLifeIterations(1)
{
    lifes = lifesNew;
    medicine = medicineNew;
    if (medicine)
        isHealfy = true;
    else
        isHealfy = false;
}

Pixel::Pixel(double xNew, double yNew, size_t CellStrNew,
             size_t CellColNew, double lifesNew, const Brain& brainNew)
        :    Hexagon(Type::PIXEL, xNew, yNew, CellStrNew, CellColNew)
{
    numberOfLifeIterations = 1;
    lifes = lifesNew;
    brain = brainNew;
}

Pixel::Pixel(const Pixel& hex)
        :  Hexagon(hex.type, hex.x, hex.y, hex.cellStr, hex.cellCol)
{
    numberOfLifeIterations = 1;
    lifes = hex.lifes;
    medicine = hex.medicine;
}

std::vector<Hexagon*> Pixel::LookAround(Map& map) const
{
    std::vector<Hexagon*> dir;
    if (cellStr % 2 == 0)
    {
        if (cellStr < map.GetHeightInCells() - 1  && cellCol > 0)
            dir.push_back(map[cellStr + 1][cellCol - 1]);
        else
            dir.push_back(map.GetWall());
        if (cellCol > 0)
            dir.push_back(map[cellStr][cellCol - 1]);
        else
            dir.push_back(map.GetWall());

        if (cellStr > 0 && cellCol > 0)
            dir.push_back(map[cellStr - 1][cellCol - 1]);
        else
            dir.push_back(map.GetWall());

        if (cellStr > 0)
            dir.push_back(map[cellStr - 1][cellCol]);
        else
            dir.push_back(map.GetWall());

        if (cellCol < map.GetWidthInCells() - 1)
            dir.push_back(map[cellStr][cellCol + 1]);
        else
            dir.push_back(map.GetWall());
        if (cellStr < map.GetHeightInCells() - 1)
            dir.push_back(map[cellStr + 1][cellCol]);
        else
            dir.push_back(map.GetWall());
    }
    else
    {
        if (cellStr < map.GetHeightInCells() - 1)
            dir.push_back(map[cellStr + 1][cellCol]);
        else
            dir.push_back(map.GetWall());
        if (cellCol > 0)
            dir.push_back(map[cellStr][cellCol - 1]);
        else
            dir.push_back(map.GetWall());
        if (cellStr > 0)
            dir.push_back(map[cellStr - 1][cellCol]);
        else
            dir.push_back(map.GetWall());

        if (cellStr > 0 && cellCol < map.GetWidthInCells() - 1)
            dir.push_back(map[cellStr - 1][cellCol + 1]);
        else
            dir.push_back(map.GetWall());
        if (cellCol < map.GetWidthInCells() - 1)
            dir.push_back(map[cellStr][cellCol + 1]);
        else
            dir.push_back(map.GetWall());
        if (cellStr < map.GetHeightInCells() - 1 && cellCol < map.GetWidthInCells() - 1)
            dir.push_back(map[cellStr + 1][cellCol + 1]);
        else
            dir.push_back(map.GetWall());
    }
    return dir;
}

void Pixel::Update(Map& map)
{
    std::vector<Hexagon*> vec = LookAround(map);
    brain.UpdateStateOfLife(lifes);
    Hexagon* moveTo = brain.GetSolution(vec);
    Move(map, moveTo);
    ++numberOfLifeIterations;
    if (isHealfy)
        lifes -= 1;
    else
        lifes -= 5;
}

void Pixel::EatingFood(Hexagon* hexagon1, Map& map)
{
    if (hexagon1->GetType() == Hexagon::Type::POISON)
    {
        isHealfy = false;
        ++howMuchPoisonAte;
    }
    else
        ++howMuchFoodAte;
    lifes += hexagon1->GetLifes();
    medicine = hexagon1->GetMedicine();
    map[hexagon1->GetCellStr()].erase(hexagon1->GetCellCol());
    map[hexagon1->GetCellStr()].insert(new Water(hexagon1->GetX(), hexagon1->GetY(),
                                                 hexagon1->GetCellStr(), hexagon1->GetCellCol()), hexagon1->GetCellCol());
    map.Swap(this, map[hexagon1->GetCellStr()][hexagon1->GetCellCol()]);
}

void Pixel::Move(Map& map, Hexagon* hexagon1)
{
    if (hexagon1 != nullptr)
    {
        if (hexagon1->GetType() == Hexagon::Type::PIXEL || hexagon1->GetType() == Hexagon::Type::WALL)
            return;
        else if (hexagon1->GetType() == Hexagon::Type::FOOD || hexagon1->GetType() == Hexagon::Type::POISON)
        {
            EatingFood(hexagon1, map);
            return;
        }
        map.Swap(this, hexagon1);
    }
}

void Pixel::Reproduction(Map& map)
{
    if (lifes - lifes / 2 > 0)//  бот затрачивает на это половину энергии , тоесть если у него ровно половина, то он умирает
    {
        lifes = lifes / 2;  //  уменьшаем количество энергии у родителя
    }
    else
    {
        return;                     //  иначе выходим из функции и собираем энергию или доживаем свою жизнь
    }
    Hexagon* dir = nullptr;
    dir = ViewNearbyCells(map, Type::WATER);
    if (dir != nullptr)
    {
        Pixel* hex = new Pixel(dir->GetX(), dir->GetY(), dir->GetCellStr(), dir->GetCellCol(), lifes,
                               brain);
        map[dir->GetCellStr()].erase(dir->GetCellCol());
        map[dir->GetCellStr()].insert(hex, dir->GetCellCol());
        map.SetOrganism(hex);
    }
}

Hexagon* Pixel::ViewNearbyCells(Map& map, const Type& tmp)
{
    std::vector<std::pair<int, int>> dir;
    if (cellStr > 0 && cellCol < 93 && cellCol > 0 && cellStr < 59)
    {
        if (map[cellStr + 1][cellCol - 1]->GetType() == tmp && cellStr % 2 == 0)
            dir.push_back({1, -1});
        if (map[cellStr + 1][cellCol]->GetType() == tmp && cellStr % 2 == 1)
            dir.push_back({1, 0});
        if (map[cellStr][cellCol - 1]->GetType() == tmp)
            dir.push_back({0, -1});
        if (map[cellStr - 1][cellCol - 1]->GetType() == tmp && cellStr % 2 == 0)
            dir.push_back({-1, -1});
        if (map[cellStr - 1][cellCol]->GetType() == tmp && cellStr % 2 == 1)
            dir.push_back({-1, 0});

        if (map[cellStr - 1][cellCol]->GetType() == tmp && cellStr % 2 == 0)
            dir.push_back({-1, 0});
        if (map[cellStr - 1][cellCol + 1]->GetType() == tmp && cellStr % 2 == 1)
            dir.push_back({-1, 1});
        if (map[cellStr][cellCol + 1]->GetType() == tmp)
            dir.push_back({0, 1});
        if (map[cellStr + 1][cellCol]->GetType() == tmp && cellStr % 2 == 0)
            dir.push_back({1, 0});
        if (map[cellStr + 1][cellCol + 1]->GetType() == tmp && cellStr % 2 == 1)
            dir.push_back({1, 1});
    }
    if (dir.size() > 1)
    {
        size_t r = rand() % dir.size();
        return (map[cellStr + dir[r].first][cellCol + dir[r].second]);
    }
    else if (dir.size() == 1)
    {
        return (map[cellStr + dir[0].first][cellCol + dir[0].second]);
    }
    else
    {
        return nullptr;
    }
}

unsigned int Pixel::GetNumberOfLifeIterations() const
{
    return numberOfLifeIterations;
}

const Brain& Pixel::GetBrain() const
{
    return brain;
}

void Pixel::SetBrain(const Brain& brainNew)
{
    brain = brainNew;
}

int Pixel::GetHowMuchFoodAte() const
{
    return howMuchFoodAte;
}
int Pixel::GetHowMuchPoisonAte() const
{
    return howMuchPoisonAte;
}

void Pixel::ResetNumberOfLifeIterations()
{
    numberOfLifeIterations = 0;
}

void Pixel::Print(sf::RenderWindow* window) const
{
    sf::CircleShape hexagon1(10, 6);
    hexagon1.setFillColor(sf::Color::Yellow);
    hexagon1.setOutlineThickness(1);
    hexagon1.setOutlineColor(sf::Color::Black);
    hexagon1.setPosition(x, y);
    window->draw(hexagon1);
}

const Json Pixel::getJson() const
{
    Json j;
    j["CellStr"] = cellStr;
    j["CellCol"] = cellCol;
    j["X"] = x;
    j["Y"] = y;
    j["Type"] = type;
    j["Lifes"] = lifes;
    j["Medicine"] = medicine;
    j["IsHealfy"] = isHealfy;
    j["NumberOfLifeIterations"] = numberOfLifeIterations;
    j["Brain"] = brain.getJson();
    return j;
}