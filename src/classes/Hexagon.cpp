#include "Hexagon.hpp"
#include "Map.hpp"



Hexagon::Hexagon()    //  ???????????????????
{}

Hexagon::Hexagon(const Type& type1, float xNew, float yNew, size_t CellStrNew, size_t CellColNew)
    :    type(type1),
         X(xNew),
         Y(yNew),
         CellStr(CellStrNew),
         CellCol(CellColNew),
         Lifes(99),
         Minerals(0),
         Energy(0),
         direction(Direction::WEST)
{
    if (type1 == Type::GRASS)
    {
        hexagon.setFillColor(sf::Color(93, 161, 48)); // Green
        Medicine = rand() % 5;
    }
    else if (type1 == Type::MEDICINE)
    {
        hexagon.setFillColor(sf::Color(153, 102, 204)); // Аметистовый
        Medicine = rand() % 12;
    }
    else if (type1 == Type::POISON)
    {
        hexagon.setFillColor(sf::Color(207, 66, 52)); // Красный
        Medicine = rand() % 12;
    }
    else if (type1 == Type::SOIL)
    {
        hexagon.setFillColor(sf::Color(131, 77, 24)); // Коричневый
        Medicine = 0;
    }
    else if (type1 == Type::WATER)
    {
        hexagon.setFillColor(sf::Color(66, 170, 255)); // Голубой
        Medicine = 0;
    }
    if (type1 != Type::WATER &&  type1 != Type::ORGANICS)
        genes = {PHOTOSINTHESIS, REPRODUCTION, LIFEONTHEGROUND};
    if (type1 == Type::GRASS)
    {
        genes = {PHOTOSINTHESIS, REPRODUCTION, LIFEINWATER, MOVEMENT};
    }
    hexagon.setOutlineThickness(1);
    hexagon.setOutlineColor(sf::Color::Black);
}

Hexagon::Hexagon(sf::CircleShape hex, float xNew, float yNew, size_t CellStrNew, size_t CellColNew,
        Type typeNew, float LifesNew, float EnergyNew, float MedicineNew, float MineralsNew,
        std::set<Genom> genesOld)//  в одном случае из четырех случайным образом меняем один случайный байт в геноме
                :   hexagon(hex),
                    X(xNew),                                                                //  записываем координаты X и Y, тоесть определяем координаты нового пикселёныша
                    Y(yNew),
                    CellStr(CellStrNew),
                    CellCol(CellColNew),
                    type(typeNew),
                    Lifes(LifesNew),                                                        //  забирается половина здоровья у предка
                    Energy(EnergyNew),
                    Medicine(MedicineNew),
                    Minerals(MedicineNew),                                                 //  забирается половина минералов у предка
                    direction(Direction::WEST)                                             //  направление, куда повернут новорожденный, генерируется случайно
{
    std::swap(hexagon,hex);  // ???????????????         //  цвет такой же, как у предка
    ++fourthDescendant;
    if (fourthDescendant % 4 == 0)
    {
        changeGenome(genesOld);
    }
    else
    {
        genes = std::move(genesOld);     //  ??????????????????????
        //  Изменение типа
    }
}


void Hexagon::changeGenome(std::set<Genom>& genesOld)
{
    size_t random = rand() % GeneBank.size();
    genes = genesOld;
    if (random % 2 == 0)
    {
        genes.insert(GeneBank[random]);
    }
    else
    {
        size_t random2 = rand() % genes.size();
        genes.erase(GeneBank[random2]);
        genes.insert(GeneBank[random]);
    }
}

Hexagon& Hexagon::operator=(const Hexagon& hex)
       // : hexagon(std::move(hex.hexagon))
{
    if (&hex != this)
    {
        hexagon = hex.hexagon;
        X = hex.X;
        Y = hex.Y;
        CellStr = hex.CellStr;
        CellCol = hex.CellCol;
        type = hex.type;
        Lifes = hex.Lifes;
        Energy = hex.Energy;
        Medicine = hex.Medicine;
        Minerals = hex.Minerals;
        genes = hex.genes;
        direction = hex.direction;
    }
    return *this;
}
void Hexagon::swap(Hexagon& hex)
{
    if (this != &hex)
    {
        std::swap(hexagon, hex.hexagon);
        std::swap(type, hex.type);
        std::swap(Lifes, hex.Lifes);
        std::swap(Energy, hex.Energy);
        std::swap(Medicine, hex.Medicine);
        std::swap(Minerals, hex.Minerals);
        std::swap(direction, hex.direction);
    }
}

float& Hexagon::getX()
{
    return X;
}

float& Hexagon::getY()
{
    return Y;
}

sf::CircleShape& Hexagon::getHex()
{
    return hexagon;
}

size_t& Hexagon::getCellStr()
{
    return CellStr;
}

size_t&  Hexagon::getCellCol()
{
    return CellCol;
}

Hexagon::Type& Hexagon::getType()
{
    return type;
}

float& Hexagon::getLifes()
{
    return Lifes;
}
void Hexagon::Die()
{
    type = Type::ORGANICS;//  Убрать пикселя из ряда живых, превратив в органику
    hexagon.setFillColor(sf::Color::White);
    genes.clear();
}
void Hexagon::Update(Map& map, SunMap& sunmap)
{
    if (type == Type::ORGANICS || type == Type::WATER)
    {
        return;
    }
    else if (type == Type::SOIL)
    {
        Photosinthesis(sunmap); //  фотосинтез
        return;
    }
    /*int command = 3; //(rand() % 5) + 1; //  выбираем - двигаться, размножаться, или есть(фотосинтезировать)
    if (command == 1)
    {
        EatingFood(map, sunmap);
    }
    else if (command == 2)
    {
        Reproduction(map);
    }
    else if (command == 3)
    {
        Move(map);
    }
    else if (command == 4)
    {
         //  ViewNearbyCells();  //  не знаю зачем, это нужно для нс
    }
    else if (command == 5)
    {
        Rotation();
    }*/
    if (type != Type::SOIL && type != Type::WATER)
        --Lifes;
    if (Lifes <= 0)
    {
        Die();
    }
}

void Hexagon::EatingFood(Map& map, SunMap& sunMap)
{
    Hexagon* hexagon1 = nullptr;
    //  вообще нужно посчитать количество генов отвечающих за еду и выбрать рандомно один из них, повторять пока он что-то не съест, если конечно есть что есть
    if (genes.find(Genom::EATPREDATOR) != genes.end())
    {                                                              //  и тут тоже самое что в в травоядном, только ищем не траву(яд и лекарство могут съесть все кроме травы, воды,земли, соответсвенно лекарства и яда)
        hexagon1 = ViewNearbyCells(map, Type::PREDATOR);                //  ищем себе подобных
        if (hexagon1 != nullptr)                                  //  если нашли себе подобных
        {
            if (hexagon1->getLifes() < Lifes)                     //  если мы сильнее
                hexagon1 = ViewNearbyCells(map, SCAVENGER);      //  если мы слабее, ищем падальщиков, которых можем съесть
        }
    }
    if (genes.find(Genom::EATORGANICS) != genes.end())            //  Все то же самое что и в травоядном , только ищем органику
    {
        hexagon1 = ViewNearbyCells(map, Type::ORGANICS);
    }
    if (genes.find(EATGRASS) != genes.end())
    {
        hexagon1 = ViewNearbyCells(map, Type::GRASS);                   //  Просмотр клеток должен возвращать указатель на найденную еду  //  а может shared_ptr?
        //  если пища не найдена, переходим к следующему условию , если выполнено заканчиваем функцию , за одну итерацию можно только что-то одно съесть
    }
    if (genes.find(PHOTOSINTHESIS) != genes.end())
    {
        Photosinthesis(sunMap);                                     //  нужно передать карту солнца ... он должен знать где солнце...
    }
    if (hexagon1 != nullptr)
    {
        //!!!           Move(coordinaties);//  Передвигаемся на найденную пищу  НАДО ДОПИСАТЬ
        Energy += hexagon1->Energy;                                //  Прибавляем энергии
        Lifes += hexagon1->Medicine;                               //  Прибаляем / убавляем жизни
        Minerals += hexagon1->Minerals;                            //  Надо решить что делать с минералами и для чего они нужны
    }
}

void Hexagon::Move(Hexagon* hexagon1)  //  нужно чем- то заполнить клетку, с которой мы ушли
{
    Hexagon hexagonSoil; // или гекс вода
    *this = *hexagon1;
}
float floatrand()
{
    static std::mt19937 rng_engine((unsigned)time(nullptr));
    static std::uniform_real_distribution<float> distribution;
    return distribution(rng_engine);
}

void Hexagon::TurnInto()
{
    std::srand(std::time(nullptr));
    float r = floatrand();
    if (r < 0.888)
    {
        type = GRASS;
        hexagon.setFillColor(sf::Color(93, 161, 48));
    }
    if (r > 0.888 && r < 0.9222)
    {
        type = MEDICINE;
        hexagon.setFillColor(sf::Color(153, 102, 204));
    }
    if (r > 0.9222)
    {
        type = POISON;
        hexagon.setFillColor(sf::Color(207, 66, 52));
    }
}

void Hexagon::Photosinthesis(SunMap& sunmap)
{
    if (sunmap[CellStr][CellCol] == 1)
    {
        std::srand(std::time(nullptr));
        float energy = floatrand();                                 //  выбор рандомного количества энергии [0, 1)
        Energy += energy;
        Lifes = Lifes + 1 + floatrand();
    }
    if (Type::SOIL == type && Energy > 100)
    {
        TurnInto();
    }
}

void Hexagon::Move(Map& map)
{
    if (genes.find(MOVEMENT) != genes.end())
    {
        ///           // метод , что в movableobject
        //  добавить проверку гена "жизнь на суше или в воде" и проверку типа для каждой клетки, на которую хотим перейти

        int random = (rand() % 6) + 1;
        //Hexagon tmp = map[object.getCellStr()][object.getCellCol()];
        if (random == 1 && CellStr >= 0 && CellCol > 0)  // change for (-1, 0)
        {
            if ((direction != NORTH_EAST) && (direction != EAST) && (direction != EAST_SOUTH))
            {
                X -= 18;
                CellCol -= 1;
                //if (object.getCellCol() < 1)
                //{
                //  map[object.getCellStr()][object.getCellCol() + 1] = object;
                //} else {
                //  map[object.getCellStr()][object.getCellCol()] = object;
                //map[object.getCellStr()][object.getCellCol() + 1] = tmp;
                //}
                //  swap(map[CellStr][CellCol]);
            }
        }
        else if (random == 2 && CellStr > 0 && CellCol > 0)  // change for (0, -1)
        {
            if ((direction != SOUTH_WEST) && (direction != EAST) && (direction != EAST_SOUTH)) {
                if (CellStr % 2 == 0)
                {
                    CellStr -= 1;
                    CellCol -= 1;
                    X -= 9;
                    Y -= 15;
                    if (CellStr < 1 && CellCol < 2)
                    {
                        CellStr += 1;
                        CellCol += 1;
                        X += 9;
                        Y += 15;
                    }
                }
                else
                {
                    CellStr -= 1;
                    X -= 9;
                    if (CellStr < 1 && CellCol < 2)
                    {
                        CellStr += 1;
                        X += 9;
                    }
                }
            }
        }
        else if (random == 3 && CellCol <= 92 && CellStr > 0)  // change for (1, -1)
        {
            if ((direction != WEST) && (direction != EAST_SOUTH) && (direction != SOUTH_WEST)) {
                X += 9;
                Y -= 15;
                if (CellStr % 2 == 0)
                {
                    CellStr -= 1;
                    if (CellStr < 1 && CellCol < 92)
                    {
                        CellStr += 1;
                    }
                }
                else
                {
                    CellStr -= 1;
                    CellCol += 1;
                    if (CellStr < 1 && CellCol < 92)
                    {
                        CellStr += 1;
                        CellCol -= 1;
                    }
                }
            }
        }
        else if (random == 4 && CellCol <= 93) // change for (1, 0)
        {
            if ((direction != WEST) && (direction != NORTH_WEST) && (direction != SOUTH_WEST)) {
                Y += 18;
                CellCol += 1;
                if (CellCol == 93)
                {
                    CellCol -= 1;
                    Y -= 18;
                }
            }
        }
        else if (random == 5 && CellCol <= 93 && CellStr <= 58)  // change for (1, 1)
        {
            if ((direction != WEST) && (direction != NORTH_WEST) && (direction != NORTH_EAST)) {
                if (CellStr % 2 == 0)
                {
                    CellStr += 1;
                    X += 9;
                    if (CellStr > 58 && CellCol > 93)
                    {
                        CellStr -= 1;
                        X -= 9;
                    }
                }
                else
                {
                    CellStr += 1;
                    CellCol += 1;
                    X += 9;
                    Y += 15;
                    if (CellStr > 58 && CellCol > 93)
                    {
                        CellStr -= 1;
                        CellCol -= 1;
                        X -= 9;
                        Y -= 15;
                    }
                }
            }
        }
        else if (random == 6 && CellCol > 0 && CellStr < 58)  // change for (0, 1)
        {
            if ((direction != NORTH_WEST) && (direction != NORTH_EAST) && (direction != EAST)) {

                if (CellStr % 2 == 0)
                {
                    CellStr += 1;
                    CellCol -= 1;
                    X += 9;
                    Y -= 15;
                    if (CellStr > 58 && CellCol < 2)
                    {
                        CellStr -= 1;
                        CellCol += 1;
                        X -= 9;
                        Y += 15;
                    }
                }
                else
                {
                    CellStr += 1;
                    X += 9;
                    if (CellStr > 58 && CellCol < 2)
                    {
                        CellStr -= 1;
                        X -= 9;
                    }
                }
            }
        }
        //hexagon.setFillColor(sf::Color::Black);
        map.setObject(*this);
    }
}

void Hexagon::Rotation()
{
    if (genes.find(ROTATION) != genes.end())
    {
        Direction angle[6] = {WEST, NORTH_WEST, NORTH_EAST, EAST, EAST_SOUTH, SOUTH_WEST};
        direction = angle[rand() % 6];
    }
}

void Hexagon::Reproduction(Map& map)
{
    if (genes.find(REPRODUCTION) != genes.end())
    {
        if (Lifes - Lifes / 2 > 0)//  бот затрачивает на это половину энергии , тоесть если у него ровно половина, то он умирает
        {
            Lifes = Lifes / 2;  //  уменьшаем количество энергии у родителя
            Minerals = Minerals / 2;
        }
        else
        {
            return;                                                                     //  иначе выходим из функции и собираем энергию или доживаем свою жизнь
        }
        Hexagon *dir = nullptr;
        if (genes.find(Genom::LIFEINWATER) != genes.end())                                        //  если мы здесь, значит пиксель полон энергии
        {
            dir = ViewNearbyCells(map, Type::WATER);  //  проверяем, окружен ли бот и находим пустое напрвление, если такое имеется, иначе бот окружен и функция заканчивается

        }
        else if (genes.find(Genom::LIFEONTHEGROUND) != genes.end())
        {
            dir = ViewNearbyCells(map, Type::SOIL);
        }
        if (dir == nullptr)
        {
            return;
        }
        Hexagon newHexagon(hexagon, dir->X, dir->Y, dir->CellStr, dir->CellCol,
                           type, Lifes, Energy, 0, Minerals, genes);                      //  создаем нового пикселя
        map.setObject(newHexagon);
    }
}

Hexagon* Hexagon::ViewNearbyCells(Map& map, const Type& tmp)
{
    //  сделать отдельный просмотр для лекарства и яда
    /*if (map[CellStr][CellCol].Type == Type::GRASS
        || map[CellStr][CellCol].Type == Type::MEDICINE
        ||  map[CellStr][CellCol].Type == Type::POISON)
    {
        std::vector<std::pair<int, int>> dir = {{0, -1},
                                                {-1, 0},
                                                {-1, 0},
                                                {1,  0},
                                                {0,  1},
                                                {0,  1}};  //  мне нужно просмотреть все напрвления вокруг
        for (size_t i = dir.size() - 1; i >= 0; --i) {
            if (map[CellStr + dir[i].first][CellCol + a[i].second].Type !=
                Type::ORGANICS) // сохранить все возможные напрaвления
            {
                dir.erase(dir.begin() + i);
            }
        }
        if (dir.size() != 0) //  Выбибаем любое направление на котором стоит органика
        {
            size_t r = rand() % dir.size();
            return &map[CellStr + dir[r].first][CellCol + dir[r].second];
        }
        else
        {
            return nullptr;
        }
    }
    else
    {
        Type typeFood;
        if (direction == WEST)
        {
            if (type == Type::HERBIVORE)
                typeFood = Type::GRASS;
            else if (type == Type::SCAVENGER)
                typeFood = Type::ORGANICS;
            else if (type == Type::PREDATOR)
                typeFood = Type::ORGANICS;
        }
        else if (direction == NORTH_WEST)
        {

        }
        else if (direction == NORTH_EAST)
        {

        }
        else if (direction == EAST)
        {

        }
        else if (direction == EAST_SOUTH)
        {

        }
        else if (direction == SOUTH_WEST)
        {

        }
    }*/
    std::vector<std::pair<int, int>> dir;
    if (CellStr > 0 && CellCol < 93 && CellCol > 0 && CellStr < 59)
    {
        if (direction == WEST)  // тк пиксель может просматривать только 3 клетки нужно их просмотреть
        {
            if (map[CellStr + 1][CellCol - 1].type == tmp && CellStr % 2 == 0)
                dir.push_back({1, -1});
            if (map[CellStr + 1][CellCol].type == tmp && CellStr % 2 == 1)
                dir.push_back({1, 0});
            if (map[CellStr][CellCol - 1].type == tmp)
                dir.push_back({0, -1});
            if (map[CellStr - 1][CellCol - 1].type == tmp && CellStr % 2 == 0)
                dir.push_back({-1, -1});
            if (map[CellStr - 1][CellCol].type == tmp && CellStr % 2 == 1)
                dir.push_back({-1, 0});
        } else if (direction == NORTH_WEST) {
            if (map[CellStr][CellCol - 1].type == tmp)
                dir.push_back({0, -1});
            if (map[CellStr - 1][CellCol - 1].type == tmp && CellStr % 2 == 0)
                dir.push_back({-1, -1});
            if (map[CellStr - 1][CellCol].type == tmp && CellStr % 2 == 1)
                dir.push_back({-1, 0});
            if (map[CellStr - 1][CellCol].type == tmp && CellStr % 2 == 0)
                dir.push_back({-1, 0});
            if (map[CellStr - 1][CellCol + 1].type == tmp && CellStr % 2 == 1)
                dir.push_back({-1, 1});
        } else if (direction == NORTH_EAST) {
            if (map[CellStr - 1][CellCol - 1].type == tmp && CellStr % 2 == 0)
                dir.push_back({-1, -1});
            if (map[CellStr - 1][CellCol].type == tmp && CellStr % 2 == 1)
                dir.push_back({-1, 0});
            if (map[CellStr - 1][CellCol].type == tmp && CellStr % 2 == 0)
                dir.push_back({-1, 0});
            if (map[CellStr - 1][CellCol + 1].type == tmp && CellStr % 2 == 1)
                dir.push_back({-1, 1});
            if (map[CellStr][CellCol + 1].type == tmp)
                dir.push_back({0, 1});
        } else if (direction == EAST) {
            if (map[CellStr - 1][CellCol].type == tmp && CellStr % 2 == 0)
                dir.push_back({-1, 0});
            if (map[CellStr - 1][CellCol + 1].type == tmp && CellStr % 2 == 1)
                dir.push_back({-1, 1});
            if (map[CellStr][CellCol + 1].type == tmp)
                dir.push_back({0, 1});
            if (map[CellStr + 1][CellCol].type == tmp && CellStr % 2 == 0)
                dir.push_back({1, 0});
            if (map[CellStr + 1][CellCol + 1].type == tmp && CellStr % 2 == 1)
                dir.push_back({1, 1});
        } else if (direction == EAST_SOUTH) {
            if (map[CellStr][CellCol + 1].type == tmp)
                dir.push_back({0, 1});
            if (map[CellStr + 1][CellCol].type == tmp && CellStr % 2 == 0)
                dir.push_back({1, 0});
            if (map[CellStr + 1][CellCol + 1].type == tmp && CellStr % 2 == 1)
                dir.push_back({1, 1});
            if (map[CellStr + 1][CellCol - 1].type == tmp && CellStr % 2 == 0)
                dir.push_back({1, -1});
            if (map[CellStr + 1][CellCol].type == tmp && CellStr % 2 == 1)
                dir.push_back({1, 0});

        } else if (direction == SOUTH_WEST) {
            if (map[CellStr + 1][CellCol].type == tmp && CellStr % 2 == 0)
                dir.push_back({1, 0});
            if (map[CellStr + 1][CellCol + 1].type == tmp && CellStr % 2 == 1)
                dir.push_back({1, 1});
            if (map[CellStr + 1][CellCol - 1].type == tmp && CellStr % 2 == 0)
                dir.push_back({1, -1});
            if (map[CellStr + 1][CellCol].type == tmp && CellStr % 2 == 1)
                dir.push_back({1, 0});
            if (map[CellStr][CellCol - 1].type == tmp)
                dir.push_back({0, -1});
        }
    }
    if (dir.size() > 1)
    {
        size_t r = rand() % dir.size();
        return &map[CellStr + dir[r].first][CellCol + dir[r].second];
    }
    else if (dir.size() == 1)
    {
        return &map[CellStr + dir[0].first][CellCol + dir[0].second];
    }
    else
    {
        return nullptr;
    }
}