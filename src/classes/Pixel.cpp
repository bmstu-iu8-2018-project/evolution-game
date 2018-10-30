#include "Pixel.hpp"

Pixel::Pixel()
{
    brain = std::shared_ptr<Brain>(new Brain());
}

Pixel::Pixel(const double xNew, const double yNew, const size_t CellStrNew, const size_t CellColNew)
        :    Hexagon(Type::PIXEL, xNew, yNew, CellStrNew, CellColNew)
{
    brain = std::shared_ptr<Brain>(new Brain());
    hexagon.setOutlineThickness(1);
    hexagon.setOutlineColor(sf::Color::Black);
}
Pixel::Pixel(const sf::CircleShape hexagon1, const float xNew, const float yNew, const size_t CellStrNew,
      const size_t CellColNew, const double lifesNew, std::shared_ptr<Brain> brainNew)
        :    Hexagon(Type::PIXEL, xNew, yNew, CellStrNew, CellColNew)
{
    hexagon = hexagon1;
    hexagon.setOutlineThickness(1);
    hexagon.setOutlineColor(sf::Color::Black);
    lifes = lifesNew;
    brain = brainNew;
}



Pixel& Pixel::operator=(const Pixel& hexagon1)
{
    if (this != &hexagon1)
    {
        *this = hexagon1;
        brain = hexagon1.brain;
    }
    return *this;
}

void Pixel::Swap(Pixel& hexagon1)
{
    //  std::swap(hex, hexagon1.hex);
    std::swap(brain, hexagon1.brain);
}

std::vector<std::shared_ptr<Hexagon>> Pixel::LookArond(Map& map)
{
    std::vector<std::shared_ptr<Hexagon>> dir;
    /*if (cellStr % 2 == 0 && cellStr < map.GetHeightInCells() - 1  && cellCol > 0)
        dir.push_back(std::shared_ptr<Hexagon>(&map[cellStr + 1][cellCol - 1]));
    else
        dir.push_back(nullptr);
    if (cellStr % 2 == 1 && cellStr < map.GetHeightInCells() - 1)
        dir.push_back(std::shared_ptr<Hexagon>(&map[cellStr + 1][cellCol]));
    else
        dir.push_back(nullptr);
    if (cellCol > 0)
        dir.push_back(std::shared_ptr<Hexagon>(&map[cellStr][cellCol - 1]));
    else
        dir.push_back(nullptr);
    if (cellStr % 2 == 0 && cellStr > 0 && cellCol > 0)
        dir.push_back(std::shared_ptr<Hexagon>(&map[cellStr - 1][cellCol - 1]));
    else
        dir.push_back(nullptr);
    if (cellStr % 2 == 1 && cellStr > 0)
        dir.push_back(std::shared_ptr<Hexagon>(&map[cellStr - 1][cellCol]));
    else
        dir.push_back(nullptr);
    if (cellStr % 2 == 0 && cellStr > 0)
        dir.push_back(std::shared_ptr<Hexagon>(&map[cellStr - 1][cellCol]));
    else
        dir.push_back(nullptr);
    if (cellStr % 2 == 1 && cellStr > 0 && cellCol > 0 )
        dir.push_back(std::shared_ptr<Hexagon>(&map[cellStr - 1][cellCol + 1]));
    else
        dir.push_back(nullptr);
    if (cellCol < map.GetWidthInCells() - 1)
        dir.push_back(std::shared_ptr<Hexagon>(&map[cellStr][cellCol + 1]));
    else
        dir.push_back(nullptr);
    if (cellStr % 2 == 0 && cellStr < map.GetHeightInCells() - 1)
        dir.push_back(std::shared_ptr<Hexagon>(&map[cellStr + 1][cellCol]));
    else
        dir.push_back(nullptr);
    if (cellStr % 2 == 1 && cellStr < map.GetHeightInCells() - 1 && cellCol < map.GetWidthInCells() - 1)
        dir.push_back(std::shared_ptr<Hexagon>(&map[cellStr + 1][cellCol + 1]));
    else
        dir.push_back(nullptr);*/
    if (cellStr % 2 == 0)
    {
        if (cellStr < map.GetHeightInCells() - 1  && cellCol > 0)
            dir.push_back(std::shared_ptr<Hexagon>(&map[cellStr + 1][cellCol - 1]));
        else
            dir.push_back(nullptr);
        if (cellCol > 0)
            dir.push_back(std::shared_ptr<Hexagon>(&map[cellStr][cellCol - 1]));
        else
            dir.push_back(nullptr);

        if (cellStr > 0 && cellCol > 0)
            dir.push_back(std::shared_ptr<Hexagon>(&map[cellStr - 1][cellCol - 1]));
        else
            dir.push_back(nullptr);

        if (cellStr > 0)
            dir.push_back(std::shared_ptr<Hexagon>(&map[cellStr - 1][cellCol]));
        else
            dir.push_back(nullptr);

        if (cellCol < map.GetWidthInCells() - 1)
            dir.push_back(std::shared_ptr<Hexagon>(&map[cellStr][cellCol + 1]));
        else
            dir.push_back(nullptr);
        if (cellStr % 2 == 0 && cellStr < map.GetHeightInCells() - 1)
            dir.push_back(std::shared_ptr<Hexagon>(&map[cellStr + 1][cellCol]));
        else
            dir.push_back(nullptr);
    }
    else
    {
        if (cellStr < map.GetHeightInCells() - 1)
            dir.push_back(std::shared_ptr<Hexagon>(&map[cellStr + 1][cellCol]));
        else
            dir.push_back(nullptr);
        if (cellCol > 0)
            dir.push_back(std::shared_ptr<Hexagon>(&map[cellStr][cellCol - 1]));
        else
            dir.push_back(nullptr);
        if (cellStr % 2 == 1 && cellStr > 0)
            dir.push_back(std::shared_ptr<Hexagon>(&map[cellStr - 1][cellCol]));
        else
            dir.push_back(nullptr);

        if (cellStr % 2 == 1 && cellStr > 0 && cellCol > 0 )
            dir.push_back(std::shared_ptr<Hexagon>(&map[cellStr - 1][cellCol + 1]));
        else
            dir.push_back(nullptr);
        if (cellCol < map.GetWidthInCells() - 1)
            dir.push_back(std::shared_ptr<Hexagon>(&map[cellStr][cellCol + 1]));
        else
            dir.push_back(nullptr);
        if (cellStr % 2 == 1 && cellStr < map.GetHeightInCells() - 1 && cellCol < map.GetWidthInCells() - 1)
            dir.push_back(std::shared_ptr<Hexagon>(&map[cellStr + 1][cellCol + 1]));
        else
            dir.push_back(nullptr);
    }
    return dir;
}

void Pixel::Update(Map& map)
{
    std::vector<std::shared_ptr<Hexagon>> vec = LookArond(map);
    //std::shared_ptr<Hexagon> moveTo = brain->GetSolution(vec);
    //Move(map, moveTo);
}

void Pixel::EatingFood(std::shared_ptr<Hexagon> hexagon1)
{
    lifes += hexagon1->GetLifes();
    medicine = hexagon1->GetMedicine();
}

void Pixel::Move(Map& map, std::shared_ptr<Hexagon> hexagon1)
{
    if (hexagon1 != nullptr)
    {
        if (hexagon1->GetType() == Hexagon::Type::PIXEL)
            return;
        else if (hexagon1->GetType() == Hexagon::Type::FOOD)
        {
            EatingFood(hexagon1);
        }
        else if (hexagon1->GetType() == Hexagon::Type::POISON)
        {
            EatingFood(hexagon1);
        }
        else if (hexagon1->GetType() == Hexagon::Type::WATER)
        {
           // map.Swap(std::shared_ptr<Hexagon>(this), hexagon1);
            // hexagon1 = this; // ?
        }
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
    std::shared_ptr<Hexagon> dir = nullptr;
    dir = ViewNearbyCells(map, Type::WATER);
    Pixel newPixel(hexagon, dir->GetX(), dir->GetY(), dir->GetCellStr(), dir->GetCellCol(), lifes, brain);                      //  создаем нового пикселя
    //  map.setObject(Pixel);
}
bool Pixel::IsAlive()
{
    return lifes > 0;
}
std::shared_ptr<Hexagon> Pixel::ViewNearbyCells(Map& map, const Type& tmp)
{
    std::vector<std::pair<int, int>> dir;
    if (cellStr > 0 && cellCol < 93 && cellCol > 0 && cellStr < 59)
    {
        if (map[cellStr + 1][cellCol - 1].GetType() == tmp && cellStr % 2 == 0)
            dir.push_back({1, -1});
        if (map[cellStr + 1][cellCol].GetType() == tmp && cellStr % 2 == 1)
            dir.push_back({1, 0});
        if (map[cellStr][cellCol - 1].GetType() == tmp)
            dir.push_back({0, -1});
        if (map[cellStr - 1][cellCol - 1].GetType() == tmp && cellStr % 2 == 0)
            dir.push_back({-1, -1});
        if (map[cellStr - 1][cellCol].GetType() == tmp && cellStr % 2 == 1)
            dir.push_back({-1, 0});

        if (map[cellStr - 1][cellCol].GetType() == tmp && cellStr % 2 == 0)
            dir.push_back({-1, 0});
        if (map[cellStr - 1][cellCol + 1].GetType() == tmp && cellStr % 2 == 1)
            dir.push_back({-1, 1});
        if (map[cellStr][cellCol + 1].GetType() == tmp)
            dir.push_back({0, 1});
        if (map[cellStr + 1][cellCol].GetType() == tmp && cellStr % 2 == 0)
            dir.push_back({1, 0});
        if (map[cellStr + 1][cellCol + 1].GetType() == tmp && cellStr % 2 == 1)
            dir.push_back({1, 1});
    }
    if (dir.size() > 1)
    {
        size_t r = rand() % dir.size();
        return std::shared_ptr<Hexagon>(&map[cellStr + dir[r].first][cellCol + dir[r].second]);
    }
    else if (dir.size() == 1)
    {
        return std::shared_ptr<Hexagon>(&map[cellStr + dir[0].first][cellCol + dir[0].second]);
    }
    else
    {
        return nullptr;
    }
}