#include "Map.hpp"
#include "Food.hpp"
#include </home/mariasolovyova/CLionProjects/Evolution/tools/json/single_include/nlohmann/json.hpp>
#include "Pixel.hpp"


using Json = nlohmann::json;

Map::Map()  //  Конструктор создает поле, состоящее из воды
{
    double deltaX = 9;
    double deltaY = 15;
    double x = deltaX * 6;
    double y = deltaY * 6;
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
            map[i].push_back(new Water(x, y, i, j));
        }
        y += deltaY;
    }
}

void Map::MultiplyPixels(int numberOfPixels)
{
    std::srand(std::time(nullptr));
    for (int inner = 0; inner < numberOfPixels; ++inner)
    {
        bool flag = false;
        while (!flag)
        {
            int xInCells = intrand(0, heightInCells - 1);
            int yInCells = intrand(0, widthInCells - 1);
            if (map[xInCells][yInCells]->GetType() == Hexagon::Type::WATER)
            {
                Pixel* hex = new Pixel(map[xInCells][yInCells]->GetX(), map[xInCells][yInCells]->GetY(), (size_t) xInCells, (size_t) yInCells);
                map[xInCells].erase(yInCells);
                map[xInCells].insert(hex, yInCells);
                organisms.push_back(map[xInCells][yInCells]);
                flag = true;
            }
        }
    }
}

void Map::CreateFood(int numberOfFood)
{
    std::srand(std::time(nullptr));
    for (int inner = 0; inner < numberOfFood; ++inner)
    {
        bool flag = false;
        while (!flag)
        {
            int xInCells = intrand(0, heightInCells - 1);
            int yInCells = intrand(0, widthInCells - 1);
            if (map[xInCells][yInCells]->GetType() == Hexagon::Type::WATER)
            {
                Food* hex = new Food(map[xInCells][yInCells]->GetX(), map[xInCells][yInCells]->GetY(), (size_t) xInCells, (size_t) yInCells);
                map[xInCells].erase(yInCells);
                map[xInCells].insert(hex, yInCells);
                flag = true;
            }
        }
    }
}

void Map::SetPoison(int numberOfPoison)
{
    std::srand(std::time(nullptr));
    for (int inner = 0; inner < numberOfPoison; ++inner)
    {
        bool flag = false;
        while (!flag)
        {
            int xInCells = intrand(0, heightInCells - 1);
            int yInCells = intrand(0, widthInCells - 1);
            if (map[xInCells][yInCells]->GetType() == Hexagon::Type::WATER)
            {
                Poison* hex = new Poison(map[xInCells][yInCells]->GetX(), map[xInCells][yInCells]->GetY(), (size_t) xInCells, (size_t) yInCells);
                map[xInCells].erase(yInCells);
                map[xInCells].insert(hex, yInCells);
                flag = true;
            }
        }
    }
}

Map::Map(const std::string& path_to_file)
{

}

Map& Map::operator=(const Map& mapOld)
{
    if (&mapOld != this)
    {
        map = mapOld.map;
        organisms = mapOld.organisms;
    }
    return *this;
}

Map& Map::operator=(Map&& mapOld)
{
    map = std::move(mapOld.map);
    organisms = std::move(mapOld.organisms);
}
void Map::Update()
{
    size_t size = organisms.size();
    for (int i = organisms.size() -  1; i >= 0; --i)
    {
        if (organisms[i]->IsAlive())
            organisms[i]->Update(*this);
        else if (!organisms[i]->IsAlive() && organisms.size() > 2)
        {
            map[organisms[i]->GetCellStr()].erase(organisms[i]->GetCellCol());
            map[organisms[i]->GetCellStr()].insert(new Food(organisms[i]->GetX(), organisms[i]->GetY(), organisms[i]->GetCellStr(), organisms[i]->GetCellCol()),
                                                   organisms[i]->GetCellCol());
            organisms.erase(organisms.begin() + i);
        }
        else
        {
            organisms[i]->SetHex().setFillColor(sf::Color::White);
            map[organisms[i]->GetCellStr()].erase(organisms[i]->GetCellCol());
            map[organisms[i]->GetCellStr()].insert(new Food(organisms[i]->GetX(), organisms[i]->GetY(), organisms[i]->GetCellStr(), organisms[i]->GetCellCol()),
                                                   organisms[i]->GetCellCol());
        }
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

std::vector<Hexagon*> Map::GetOrganisms() const
{
    return organisms;
}

void Map::SetObject(Hexagon* obj)
{
    map[obj->GetCellStr()].erase(obj->GetCellCol());
    map[obj->GetCellStr()].insert(obj, obj->GetCellCol());
}

void Map::SetOrganism(Hexagon* org)
{
    organisms.push_back(org);
}

void Map::Swap(Hexagon* hex1, Hexagon* hex2)
{
    //  std::swap(hex1, hex2);
    Hexagon* hex =  hex1;
    map[hex1->GetCellStr()].erase(hex1->GetCellCol());
    map[hex2->GetCellStr()].insert(hex, hex2->GetCellCol());
    hex =  hex2;
    map[hex2->GetCellStr()].erase(hex2->GetCellCol() + 1);
    map[hex1->GetCellStr()].insert(hex, hex1->GetCellCol());
    //organisms.push_back(map[xInCells][yInCells]);
    double copy = hex1->GetX();
    hex1->SetX(hex2->GetX());
    hex2->SetX(copy);
    copy = hex1->GetY();
    hex1->SetY(hex2->GetY());
    hex2->SetY(copy);
    size_t cp = hex1->GetCellStr();
    hex1->SetCellStr(hex2->GetCellStr());
    hex2->SetCellStr(cp);
    cp = hex1->GetCellCol();
    hex1->SetCellCol(hex2->GetCellCol());
    hex2->SetCellCol(cp);

    /*if (hex2.GetType() == Hexagon::WATER)
    {
        Water tmp1(hex2.GetX(), hex2.GetY(), hex2.GetCellStr(), hex2.GetCellCol());
        Pixel tmp2(hex1.GetX(), hex1.GetY(), hex1.GetCellStr(), hex1.GetCellCol());
        hex2 = tmp2;
        hex1 = tmp1;
    }*/
}

void Map::SaveToFile() const
{
    boost::filesystem::path path = boost::filesystem::current_path().parent_path();
    path += "/records";
    if(!boost::filesystem::exists(path))
        boost::filesystem::create_directory(path);  //  добавить дату в название папки, загрузать всегда последнюю
    std::string path_to_file;
    size_t i = 0;
    size_t j = 0;
    //for (size_t i = 0; i < heightInCells; ++i)
    //{
        //for (size_t j = 0; j < widthInCells; ++j)
        //{
            path_to_file = path.string() + "/" + std::to_string(i) + "_" + std::to_string(j);
            std::fstream file(path_to_file, std::ios::app);
            file << "{" << std::endl;
            map[i][j]->SaveToFile(path_to_file);
            file << "}" << std::endl;
            file.close();
        //}
    //}
}

void Map::UploadFromFile()
{
    boost::filesystem::path path = boost::filesystem::current_path().parent_path();
    path += "/records";
    if(!boost::filesystem::exists(path))
        throw std::runtime_error("UploadFromFile : can't file directory to load from");
    std::string path_to_file;
    size_t i = 0;
    size_t j = 0;
    //for (size_t i = 0; i < heightInCells; ++i)
    //{
        //for (size_t j = 0; j < widthInCells; ++j)
        //{
            path_to_file = path.string() + "/" + std::to_string(i) + "_" + std::to_string(j);
            std::ifstream file(path_to_file);
            std::string s;
            std::string line;
            while (std::getline(file, line))
                s += line;
            file.close();
            Json object = Json::parse(s);

        //}
    //}
}
