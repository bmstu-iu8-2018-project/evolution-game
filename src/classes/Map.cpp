#include "Map.hpp"
#include "Food.hpp"
#include "Pixel.hpp"

int intrand(int a, int b)
{
    static std::default_random_engine e;
    static std::uniform_int_distribution<> dis(a, b);
    return dis(e);
}

Map::Map()
{
    double deltaX = 9;
    double deltaY = 15;
    double x = deltaX * 6;
    double y = deltaY * 6;
    organisms.clear();
    std::shared_ptr<Hexagon> hex(new Hexagon(Hexagon::Type::WATER, x, y, 0, 0));
    hex->GetHex().setPosition((float)deltaX, (float)deltaY);
    for (size_t i = 0; i < heightInCells; ++i)
    {
        x = deltaX * 6;
        Row row;
        map.push_back(row);
        if ((i % 2) != 0)
        {
            x += deltaX;
        }
        for (size_t j = 0; j < widthInCells; ++j)
        {
            x += 2 * deltaX;
            int color = intrand(0, 6600);
            if (color % 43 == 0)
            {
                hex = std::shared_ptr<Hexagon>(new Pixel(x, y, i, j));
                organisms.push_back(std::shared_ptr<Pixel>(new Pixel(x, y, i, j)));

            }
            else if (color % 100 == 0)
            {

               hex = std::shared_ptr<Hexagon>(new Poison(x, y, i, j));
            }
            else if (color % 5 == 0)
            {
                hex = std::shared_ptr<Hexagon>(new Food(x, y, i, j));
            }
            else
            {
                hex = std::shared_ptr<Hexagon>(new Water(x, y, i, j));
            }
            map[i].push_back(hex);
        }
        y += deltaY;
    }
}

void Map::Update()
{
    int size = organisms.size();
    organisms[0]->Update(*this);
}

Row& Map::operator[](size_t index)
{
    return map[index];
}

const Row& Map::operator[](size_t index) const
{
    return map[index];
}


unsigned int Map::GetWidth() const
{
    return width;
}

unsigned int Map::GetHeight() const
{
    return height;
}

size_t Map::GetWidthInCells() const
{
    return widthInCells;
}

size_t Map::GetHeightInCells() const
{
    return heightInCells;
}

/*void Map::SetObject(const Hexagon& obj)
{
    map[obj.GetCellStr()][obj.GetCellCol()] = obj;
}*/
void Map::Swap(std::shared_ptr<Hexagon> hex1, std::shared_ptr<Hexagon> hex2)
{
    std::swap(hex1, hex2);
    /*std::swap(hex1->GetX(), hex2->GetX());
    std::swap(hex1->GetY(), hex2->GetY());
    std::swap(hex1->GetCellStr(), hex2->GetCellStr());
    std::swap(hex1->GetCellCol(), hex2->GetCellCol());*/
    std::swap(hex1->GetType(), hex2->GetType());
    std::swap(hex1->GetLifes(), hex2->GetLifes());
    std::swap(hex1->GetMedicine(), hex2->GetMedicine());
}