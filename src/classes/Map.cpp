#include "Map.hpp"
#include "Food.hpp"
#include </home/mariasolovyova/CLionProjects/untitled4/tools/json/single_include/nlohmann/json.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include "Pixel.hpp"
#include <random>

boost::recursive_mutex mutex;

using Json = nlohmann::json;

Map::Map()  //  Конструктор создает поле, состоящее из воды
{
    std::srand(std::time(nullptr));
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
    CreateFood(200);
    SetPoison(200);
}

Map::Map(const Map& mapToCopy)
    :    map(mapToCopy.map),
         organisms(mapToCopy.organisms),
         staticOrganisms(mapToCopy.staticOrganisms),
         evolutionNumber(mapToCopy.evolutionNumber)
{}

Map::Map(Map&& mapToMove)
    :    map(mapToMove.map),
         organisms(mapToMove.organisms),
         staticOrganisms(mapToMove.staticOrganisms),
         evolutionNumber(mapToMove.evolutionNumber)
{}

void Map::MultiplyPixels(int numberOfPixels)
{
    std::srand(std::time(nullptr));
    for (int inner = 0; inner < numberOfPixels; ++inner)
    {
        bool flag = false;
        while (!flag)
        {
            //int xInCells = intrand(0, heightInCells - 1);
            //int yInCells = intrand(0, widthInCells - 1);
            int xInCells = rand() % (0, heightInCells - 1);
            int yInCells = rand() % (0, widthInCells - 1);
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
            int xInCells = rand() % (0, heightInCells - 1);
            int yInCells = rand() % (0, widthInCells - 1);
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
            int xInCells = rand() % (0, heightInCells - 1);
            int yInCells = rand() % (0, widthInCells - 1);
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

void Map::RecreateMap(const std::vector<Hexagon*>& vectorOfNewOrganisms)
{
    Map mapNew;
    mapNew.SetEvolutionNamber(GetEvolutionNamber());
    ClonePixels(mapNew, vectorOfNewOrganisms);
    *this = mapNew;

}

void Map::ClonePixels(Map& mapNew, const std::vector<Hexagon*>& vectorOfNewOrganisms)
{
    std::srand(std::time(nullptr));
    mapNew.organisms.clear();
    mapNew.organisms = vectorOfNewOrganisms;
    for (size_t i = 0; i < mapNew.organisms.size(); ++i)
    {
        mapNew.organisms[i]->SetLifes(99);
        mapNew.organisms[i]->ResetNumberOfLifeIterations();
        mapNew.organisms[i]->ResetMedicine();
        mapNew.organisms[i]->SetColor(sf::Color::Yellow);
    }
    for (size_t innerOfOrganisms = 0; innerOfOrganisms < vectorOfNewOrganisms.size(); innerOfOrganisms++)
    {
        bool flag = false;
        while (!flag)
        {
            int xInCells = rand() % (0, heightInCells - 1);
            int yInCells = rand() % (0, widthInCells - 1);
            if (mapNew.map[xInCells][yInCells]->GetType() == Hexagon::Type::WATER)
            {
                Brain brain = mapNew.organisms[innerOfOrganisms]->GetBrain();
                brain.Train();
                Pixel* hex = new Pixel(map[xInCells][yInCells]->GetX(), map[xInCells][yInCells]->GetY(), (size_t) xInCells, (size_t) yInCells, brain);
                hex->SetColor(sf::Color::Magenta);
                map[xInCells].erase(yInCells);
                map[xInCells].insert(hex, yInCells);
                mapNew.organisms.push_back(hex);
                flag = true;
            }
        }
    }
}

Map::Map(const std::string& path)
{
    boost::filesystem::path path_to_file = path + "/" + "Map";
    if (!boost::filesystem::exists(path_to_file))
        throw std::runtime_error("Error in uploading files");
    std::ifstream file(path_to_file.string());
    std::string s;
    std::string line;
    while (std::getline(file, line))
        s += line;
    file.close();
    Json object = Json::parse(s);
    for (auto& m : object["Map"])
    {
        Row row;
        map.push_back(row);
        for (auto& obj : m)
        {
            auto cellStr = static_cast<size_t >(obj["cellStr"]);
            auto cellCol = static_cast<size_t>(obj["cellCol"]);
            auto x = static_cast<double>(obj["x"]);
            auto y = static_cast<double>(obj["y"]);
            auto medicine = static_cast<double>(obj["medicine"]);
            if (obj["type"] == 1)
            {
                map[cellStr].push_back(new Food(x, y, cellStr, cellCol, medicine));
            }
            else if (obj["type"] == 2)
            {
                map[cellStr].push_back(new Water(x, y, cellStr, cellCol));
            }
            else if (obj["type"] == 3)
            {
                map[cellStr].push_back(new Poison(x, y, cellStr, cellCol, medicine));
            }
            else if (obj["type"] == 4)
            {
                map[cellStr].push_back(new Pixel(x, y, cellStr, cellCol, Brain(obj)));
                organisms.push_back(map[cellStr][cellCol]);
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
        staticOrganisms = mapOld.staticOrganisms;
        evolutionNumber = mapOld.evolutionNumber;
    }
    return *this;
}

Map& Map::operator=(Map&& mapOld)
{
    map = std::move(mapOld.map);
    organisms = std::move(mapOld.organisms);
    staticOrganisms = std::move(mapOld.staticOrganisms);
    evolutionNumber = std::move(mapOld.evolutionNumber);
}
void Map::Update()
{
    //boost::recursive_mutex::scoped_lock lock{mutex};
    size_t size = organisms.size();
    for (int i = organisms.size() -  1; i >= 0; --i)
    {
        if (organisms[i]->IsAlive())
            organisms[i]->Update(*this);
        else if (!organisms[i]->IsAlive()/* && organisms.size() > 10*/)
        {
            map[organisms[i]->GetCellStr()].erase(organisms[i]->GetCellCol());
            if (!organisms[i]->GetisHealfy())
            {
                map[organisms[i]->GetCellStr()].insert(new Poison(organisms[i]->GetX(), organisms[i]->GetY(), organisms[i]->GetCellStr(), organisms[i]->GetCellCol()),
                                                       organisms[i]->GetCellCol());
            }
            else
            {
                map[organisms[i]->GetCellStr()].insert(new Food(organisms[i]->GetX(), organisms[i]->GetY(), organisms[i]->GetCellStr(), organisms[i]->GetCellCol()),
                                                       organisms[i]->GetCellCol());
            }
            organisms.erase(organisms.begin() + i);
        }
        /*else
        {
            staticOrganisms.push_back(organisms[i]);
            map[organisms[i]->GetCellStr()].erase(organisms[i]->GetCellCol());
            if (!organisms[i]->GetisHealfy())
            {
                map[organisms[i]->GetCellStr()].insert(new Poison(organisms[i]->GetX(), organisms[i]->GetY(), organisms[i]->GetCellStr(), organisms[i]->GetCellCol()),
                                                       organisms[i]->GetCellCol());
            }
            else
            {
                map[organisms[i]->GetCellStr()].insert(new Food(organisms[i]->GetX(), organisms[i]->GetY(), organisms[i]->GetCellStr(), organisms[i]->GetCellCol()),
                                                       organisms[i]->GetCellCol());
            }
            organisms.erase(organisms.begin() + i);
        }*/
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

unsigned int Map::GetEvolutionNamber() const
{
    return evolutionNumber;
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

std::vector<Hexagon*> Map::GetStaticOrganisms() const
{
    return staticOrganisms;
}

size_t Map::GetNumberOfAliveOrganisms() const
{
    return organisms.size();
}

int Map::GetTimeToSleep() const
{
    return timeToSleep;
}

void Map::SetStaticOrganisms(std::vector<Hexagon *> newStaticOrganisms)
{
    staticOrganisms = newStaticOrganisms;
}

void Map::IncreaseTimesToSleep(int x)
{
    timeToSleep += x;
}

void Map::DecreaseTimesToSleep(int x)
{
    timeToSleep -= x;
}

void Map::SetEvolutionNamber(unsigned int evNum)
{
    evolutionNumber = evNum;
}

void Map::SetOrganism(Hexagon* org)
{
    organisms.push_back(org);
}

void Map::IncreaseEvolutionNumber()
{
    ++evolutionNumber;
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
    path += "/recordsNew";
    if(!boost::filesystem::exists(path))
        boost::filesystem::create_directory(path);
    std::string path_to_file = path.string() + "/Map " + std::to_string(evolutionNumber);
    std::fstream file(path_to_file, std::ios::app);
    file << "{" << std::endl;
    file << "\t\"Evolution\" : " << evolutionNumber << ","<< std::endl;
    file << "\t\"Static Pixels\" : [" << std::endl;
    for (auto& p : staticOrganisms)
    {
        file << "\t\t{" << std::endl;
        p->SaveToFile(path_to_file);
        file << "\t\t}";
        if (staticOrganisms.back() != p)
            file << ",";
        file << std::endl;
    }
    file << "\t]," << std::endl;
    file << "\t\"Map\" : " << std::endl;
    file << "\t[" << std::endl;
    for (size_t i = 0; i < heightInCells; ++i)
    {
        file << "\t\t[" << std::endl;
        for (size_t j = 0; j < widthInCells; ++j)
        {
            file << "\t\t\t{" << std::endl;
            map[i][j]->SaveToFile(path_to_file);
            file << "\t\t\t}";
            if (j != widthInCells - 1)
                file << ",";
            file << std::endl;
        }
        file << "\t\t]";
        if (i != heightInCells - 1)
            file << ",";
        file << std::endl;
    }
    file << "\t]" << std::endl;
    file << "}" << std::endl;
    file.close();
}


void Map::UploadFromFile()
{
    boost::filesystem::path path = boost::filesystem::current_path().parent_path();
    path += "/recordsNew";
    if(!boost::filesystem::exists(path))
        throw std::runtime_error("UploadFromFile : can't file directory to load from");
    *this = Map(path.string());
}

void Map::Print(sf::RenderWindow* window)
{
    window->clear();
    boost::recursive_mutex::scoped_lock lock{mutex};
    for (size_t i = 1; i < heightInCells; ++i)
    {
        for (size_t j = 0; j < widthInCells; ++j)
        {
            map[i][j]->Print(window);

        }
    }
    sf::Font font;
    font.loadFromFile("/home/mariasolovyova/CLionProjects/untitled4/Arial.ttf");
    sf::Text text("", font, 25);
    text.setColor(sf::Color::Red);
    std::ostringstream numberOfEvolution;
    numberOfEvolution << evolutionNumber;
    text.setString("Number of evolution: " + numberOfEvolution.str());
    text.setPosition(100, 0);
    window->draw(text);
    std::this_thread::sleep_for(std::chrono::milliseconds(GetTimeToSleep()));
}
