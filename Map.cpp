#include "Map.hpp"
#include "Food.hpp"
#include </home/anastasia/CLionProjects/evolution/tools/json-develop/single_include/nlohmann/json.hpp>
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
                organisms.push_back(hex);
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
                Food* hex = new Food(map[xInCells][yInCells]->GetX(), map[xInCells][yInCells]->GetY(), (size_t)xInCells, (size_t)yInCells);
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

Map::Map(const std::string& path)
{
    size_t i = 0;
    size_t j = 0;
    // for (size_t i = 0; i < heightInCells; ++i)
    {
        Row row;
        map.push_back(row);
        // for (size_t j = 0; j < widthInCells; ++j)
        {
            boost::filesystem::path path_to_file = path + "/" + std::to_string(i) + "_" + std::to_string(j);
            if (!boost::filesystem::exists(path_to_file))
                throw std::runtime_error("Error in uploading files");
            std::ifstream file(path_to_file.string());
            std::string s;
            std::string line;
            while (std::getline(file, line))
                s += line;
            file.close();
            Json object = Json::parse(s);
            auto x = static_cast<double>(object["x"]);
            auto y = static_cast<double>(object["y"]);
            auto medicine = static_cast<double>(object["medicine"]);
            if (object["type"] == "1")
            {
                map[i].push_back(new Food(x, y, i, j, medicine));
            }
            else if (object["type"] == "2")
            {
                map[i].push_back(new Water(x, y, i, j));
            }
            else if (object["type"] == "3")
            {
                map[i].push_back(new Poison(x, y, i, j, medicine));
            }
            else if (object["type"] == "4")
            {
                map[i].push_back(new Pixel(x, y, i, j, Brain(object["layers"])));
            }
        }
    }
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
    map[hex1->GetCellStr()][hex1->GetCellCol()] = hex2;
    map[hex2->GetCellStr()][hex2->GetCellCol()] = hex1;

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
}

void Map::SaveToFile() const
{
    boost::filesystem::path path = boost::filesystem::current_path().parent_path();
    path += "/records";
    if(!boost::filesystem::exists(path))
        boost::filesystem::create_directory(path);  //  добавить дату в название папки, загружать всегда последнюю
    std::string path_to_file;
    size_t i = 0;
    size_t j = 0;
    //for (size_t i = 0; i < heightInCells; ++i)
    {
        //for (size_t j = 0; j < widthInCells; ++j)
        {
            path_to_file = path.string() + "/" + std::to_string(i) + "_" + std::to_string(j);
            std::fstream file(path_to_file, std::ios::app);
            file << "{" << std::endl;
            map[i][j]->SaveToFile(path_to_file);
            file << "}" << std::endl;
            file.close();
        }
    }
}

/*void Map::UploadFromFile()
{
    boost::filesystem::path path = boost::filesystem::current_path().parent_path();
    path += "/records";
    if(!boost::filesystem::exists(path))
        throw std::runtime_error("UploadFromFile : can't file directory to load from");
    *this = Map(path.string());
}*/
