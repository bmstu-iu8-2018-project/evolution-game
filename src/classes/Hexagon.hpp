#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <set>
#include <atomic>


// #include "Genes.hpp"
#include "SunMap.hpp"

//  У каждого пикселя эволюции есть свой геном
//  В зависимости от генов, он может или не может выполнять функции
//  Установим некоторую пищевую цепочку для понимая происходящего
//  Травы, лекарства и яды могут фотосинтезировать(если у них есть этот ген, мы записываем их в соответствуюций тип)
//  Если у пикселя - травы появляется ген движения, ЗНАЧИТ ТРАВА МОЖЕТ БЕГАТЬ (ДА Я ЗНАЮ ЧТО ЭТО СУМАШЕСТВИЕ)
//  Если у пикселя появляется ген "поедания травы", значит он переходит в травоядные, если пиксель до этого был ядом(и у него остался ген яда),
//  то в воследующем он все равно будет накапливать яд и съевший его ТОЖЕ УМРЕТ
//  Если у пикселя появляется ген-падальщика, он начинает есть органику(трупики пикселей)
//  Если пиксель становится хищником он может есть всех , но чтобы фотосинтезировать, есть яд и  органику нужен отдельный ген (чтобы нейтролизовать яд тоже)



enum Genom : int
{
    PHOTOSINTHESIS = 1,
    REPRODUCTION = 2,
    MOVEMENT = 3,
    EATGRASS = 4,
    EATMEDICINE = 5,
    EATPOISON = 6,
    EATHERBIVORE = 7,
    EATPREDATOR = 8,
    NEUTRALIZATIONOFPOISON = 9,
    SPEED = 10,
    ROTATION = 11,
    LIFEINWATER = 12,
    LIFEONTHEGROUND = 13,
    DISEASE = 14,
    EATORGANICS = 15
};

static const std::vector<Genom> GeneBank = {PHOTOSINTHESIS, REPRODUCTION, MOVEMENT, EATGRASS, EATMEDICINE,
        EATPOISON, EATHERBIVORE, EATPREDATOR, NEUTRALIZATIONOFPOISON, SPEED,
        ROTATION, LIFEINWATER, LIFEONTHEGROUND, DISEASE, EATORGANICS};

static int fourthDescendant = 0;

class Map;

class Hexagon
{
public:

    enum Type : int
    {
        ORGANICS = 0, // труп пиклеля
        GRASS = 1,
        WATER = 2,
        MEDICINE = 3,
        POISON = 4,
        SOIL = 5,
        HERBIVORE = 6,  // травоядное
        SCAVENGER = 7,  //  падальщик
        PREDATOR = 8  //  хищник
    };
    enum  Direction : int
    {
        WEST = 0,
        NORTH_WEST = 45,
        NORTH_EAST = 135,
        EAST = 180,
        EAST_SOUTH = -135,
        SOUTH_WEST = -45,
    };
private:
    sf::CircleShape hexagon = sf::CircleShape(10, 6); // сам шестиугольник
    float X;  // координата по х как номер ячейки
    float Y;  // координата по у как номер ячейки
    size_t CellStr;
    size_t CellCol;
    Type type;
    float Lifes;
    float Energy;
    float Medicine;  // отрицательна если яд и положительна если лекарство
    float Minerals;
    std::set<Genom> genes;  //  должны быть байты
    Direction direction;
    bool isHealfy = true;
public:
    Hexagon();
    Hexagon(const Type& type1, float xNew, float yNew, size_t CellStrNew, size_t CellColNew);
    Hexagon(sf::CircleShape hex, float xNew, float yNew, size_t CellStrNew, size_t CellColNew,
            Type typeNew, float LifesNew, float EnergyNew, float MedicineNew, float MineralsNew,
            std::set<Genom> genesOld);
    ~Hexagon() = default;
    void changeGenome(std::set<Genom>& genesOld);

    Hexagon& operator=(const Hexagon& hex);
    void swap(Hexagon& hex);

    float& getX();
    float& getY();

    sf::CircleShape& getHex();
    size_t& getCellStr();

    size_t&  getCellCol();

    Type& getType();

    float& getLifes();
    void Die();
    void Update(Map& map, SunMap& sunmap);

    void EatingFood(Map& map, SunMap& sunMap);

    void Move(Hexagon* hexagon1);  //  нужно чем- то заполнить клетку, с которой мы ушли
    void Photosinthesis(SunMap& sunmap);

    void TurnInto();

    void Move(Map& map);

    void Rotation();

    void Reproduction(Map& map);

    Hexagon* ViewNearbyCells(Map& map, const Type& tmp);
};

#endif
