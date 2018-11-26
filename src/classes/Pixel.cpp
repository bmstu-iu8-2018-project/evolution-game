#include "Pixel.hpp"

Pixel::Pixel()
{
    numberOfLifeIterations = 1;
    brain = Brain();
}

Pixel::Pixel(const double xNew, const double yNew, const size_t CellStrNew, const size_t CellColNew)
        :    Hexagon(Type::PIXEL, xNew, yNew, CellStrNew, CellColNew)
{
    numberOfLifeIterations = 1;
    medicine = 0;
}

Pixel::Pixel(const double xNew, const double yNew, const size_t CellStrNew, const size_t CellColNew, Brain newBrain)
        :    Hexagon(Type::PIXEL, xNew, yNew, CellStrNew, CellColNew),
             brain(newBrain)
{
    numberOfLifeIterations = 1;
    medicine = 0;
}

Pixel::Pixel(const float xNew, const float yNew, const size_t CellStrNew,
             const size_t CellColNew, const double lifesNew, Brain brainNew)
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

std::vector<Hexagon*> Pixel::LookArond(Map& map) const
{
    std::vector<Hexagon*> dir;
    if (cellStr % 2 == 0)
    {
        if (cellStr < map.GetHeightInCells() - 1  && cellCol > 0)
            dir.push_back(map[cellStr + 1][cellCol - 1]);
        else
            dir.push_back(nullptr);
        if (cellCol > 0)
            dir.push_back(map[cellStr][cellCol - 1]);
        else
            dir.push_back(nullptr);

        if (cellStr > 0 && cellCol > 0)
            dir.push_back(map[cellStr - 1][cellCol - 1]);
        else
            dir.push_back(nullptr);

        if (cellStr > 0)
            dir.push_back(map[cellStr - 1][cellCol]);
        else
            dir.push_back(nullptr);

        if (cellCol < map.GetWidthInCells() - 1)
            dir.push_back(map[cellStr][cellCol + 1]);
        else
            dir.push_back(nullptr);
        if (cellStr % 2 == 0 && cellStr < map.GetHeightInCells() - 1)
            dir.push_back(map[cellStr + 1][cellCol]);
        else
            dir.push_back(nullptr);
    }
    else
    {
        if (cellStr < map.GetHeightInCells() - 1)
            dir.push_back(map[cellStr + 1][cellCol]);
        else
            dir.push_back(nullptr);
        if (cellCol > 0)
            dir.push_back(map[cellStr][cellCol - 1]);
        else
            dir.push_back(nullptr);
        if (cellStr % 2 == 1 && cellStr > 0)
            dir.push_back(map[cellStr - 1][cellCol]);
        else
            dir.push_back(nullptr);

        if (cellStr % 2 == 1 && cellStr > 0 && cellCol > 0 )
            dir.push_back(map[cellStr - 1][cellCol + 1]);
        else
            dir.push_back(nullptr);
        if (cellCol < map.GetHeight() - 1)
            dir.push_back(map[cellStr][cellCol + 1]);
        else
            dir.push_back(nullptr);
        if (cellStr % 2 == 1 && cellStr < map.GetHeightInCells() - 1 && cellCol < map.GetWidthInCells() - 1)
            dir.push_back(map[cellStr + 1][cellCol + 1]);
        else
            dir.push_back(nullptr);
    }
    return dir;
}

void Pixel::Update(Map& map)
{
    std::vector<Hexagon*> vec = LookArond(map);
    Hexagon* moveTo = brain.GetSolution(vec);
    Move(map, moveTo);
    ++numberOfLifeIterations;
    if (isHealfy)
        lifes -= 1;
    else
        lifes -= medicine;
}

void Pixel::EatingFood(Hexagon* hexagon1, Map& map)
{
    if (hexagon1->GetType() == Hexagon::Type::POISON)
        isHealfy = false;
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
        if (hexagon1->GetType() == Hexagon::Type::PIXEL)
            return;
        else if (hexagon1->GetType() == Hexagon::Type::FOOD || hexagon1->GetType() == Hexagon::Type::POISON)
        {
            EatingFood(hexagon1, map);
            return;
        }
        /*else if (lifes > 90)
        {
            Reproduction(map);
            return;
        }*/
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
        map[dir->GetCellStr()].erase(dir->GetCellCol());
        map[dir->GetCellStr()].insert(new Pixel(dir->GetX(), dir->GetY(), dir->GetCellStr(), dir->GetCellCol(), lifes,
                                                brain), dir->GetCellCol());
        map.SetOrganism(map[dir->GetCellStr()][dir->GetCellCol()]);
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

Brain Pixel::GetBrain() const
{
    return brain;
}

void Pixel::SetBrain(const Brain& brainNew)
{
    brain = brainNew;
}

void Pixel::ResetNumberOfLifeIterations()
{
    numberOfLifeIterations = 0;
}

void Pixel::SaveToFile(const std::string& path_to_file) const
{
    std::fstream fl(path_to_file, std::ios::app);
    fl << "\t\t\t\t" << "\"cellStr\"" << " : " << cellStr << "," << std::endl;
    fl << "\t\t\t\t" << "\"cellCol\"" << " : " << cellCol << "," << std::endl;
    fl << "\t\t\t\t" << "\"x\"" << " : " << x << "," << std::endl;
    fl << "\t\t\t\t" << "\"y\"" << " : " << y << "," << std::endl;
    fl << "\t\t\t\t" << "\"type\"" << " : " << type << "," << std::endl;
    fl << "\t\t\t\t" << "\"medicine\"" << " : " << medicine << "," << std::endl;
    fl << "\t\t\t\t" << "\"isHealfy\"" << " : " << isHealfy << "," << std::endl;
    fl.close();
    brain.SaveNetworkState(path_to_file);
}

/*void Pixel::SaveToFile(const std::string& path_to_file) const
{
    std::fstream fl(path_to_file, std::ios::app);
    fl << "    " << "\"x\"" << " : " << x << "," << std::endl;
    fl << "    " << "\"y\"" << " : " << y << "," << std::endl;
    fl << "    " << "\"type\"" << " : " << type << "," << std::endl;
    fl << "    " << "\"medicine\"" << " : " << medicine << "," << std::endl;
    fl << "    " << "\"isHealfy\"" << " : " << isHealfy << "," << std::endl;
    fl.close();
    brain.SaveNetworkState(path_to_file);
}*/

void Pixel::Print(sf::RenderWindow* window) const
{
    sf::CircleShape hexagon1(10, 6);
    hexagon1.setFillColor(sf::Color::Yellow);
    hexagon1.setOutlineThickness(1);
    hexagon1.setOutlineColor(sf::Color::Black);
    hexagon1.setPosition(x, y);
    window->draw(hexagon1);
}