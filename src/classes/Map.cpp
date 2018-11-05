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
    Hexagon hex = Hexagon(Hexagon::Type::WATER, x, y, 0, 0);
    hex.SetHex().setPosition((float)deltaX, (float)deltaY);
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

                organisms.push_back(new Pixel(x, y, i, j));
                hex = *organisms.back();
            }
            else if (color % 100 == 0)
            {

               hex = Poison(x, y, i, j);
            }
            else if (color % 5 == 0)
            {
                hex = Food(x, y, i, j);
            }
            else
            {
                hex = Water(x, y, i, j);
            }
            map[i].push_back(hex);
        }
        y += deltaY;
    }
}

void Map::Update()
{
    size_t size = organisms.size();
    //organisms[0].Update(*this);
    for (size_t i = 0; i < organisms.size(); ++i)
    {
        organisms[i]->Update(*this);
    }
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

void Map::SetObject(const Pixel& obj)
{
    map[obj.GetCellStr()][obj.GetCellCol()] = obj;
}

void Map::SetObject(const Hexagon& obj)
{
    map[obj.GetCellStr()][obj.GetCellCol()] = obj;
}
void Map::Swap(Hexagon& hex1, Hexagon& hex2)
{
    std::swap(hex1, hex2);
    hex1.Swap(hex2);
    //organisms[] = &hex2;
    /*std::swap(hex1, hex2);
    std::swap(hex1->SetType(), hex2->SetType());
    std::swap(hex1->SetLifes(), hex2->SetLifes());
    std::swap(hex1->SetMedicine(), hex2->SetMedicine());*/
}

/*std::swap(hex1->GetX(), hex2->GetX());
std::swap(hex1->GetY(), hex2->GetY());
std::swap(hex1->GetCellStr(), hex2->GetCellStr());
std::swap(hex1->GetCellCol(), hex2->GetCellCol());*/