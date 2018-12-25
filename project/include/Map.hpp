#ifndef EVOLUTION_MAP_HPP_
#define EVOLUTION_MAP_HPP_

#include <iomanip>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include <boost/filesystem.hpp>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include "Food.hpp"
#include "Hexagon.hpp"

using Json = nlohmann::json;

class Pixel;

class Row
{
    std::vector<Hexagon*> row;
public:
    /// @brief Конструктор по умочанию
    Row() = default;
    /// @brief Деструктор по умочанию
    ~Row() = default;
    /// @brief Оператор обращения по индексу
    /// @param index номер элемента в строке
    /// @return указатель на гекс
    Hexagon*& operator[](size_t index)
    {
        return row[index];
    }
    /// @brief Оператор обращения по индексу
    /// @param index номер элемента в строке
    /// @return указатель на гекс
    const Hexagon* operator[](size_t index) const
    {
        return row[index];
    }
    /// @brief Оператор добавления
    /// @param hex указатель на гекс, который нужно добавить
    void push_back(Hexagon* hex)
    {
        row.push_back(hex);
    }
    /// @brief Функция удаления
    /// @param index номер гекса, который нужно убрать
    void erase(size_t index)
    {
        row.erase(row.begin() + index);
    }
    /// @brief Функция вставки
    /// @param hex указатель на гекс, который нужно добавить
    /// @param index место куда нужно вставить гекс
    void insert(Hexagon* hex, size_t index)
    {
        row.insert(row.begin() + index, hex);
    }
};


class Map
{
public:
    /// @brief Конструктор, создающий карту по заданным параметрам(по умолчанию количество строк - 60, столбцов - 94)
    /// @param widthCells ширина карты
    /// @param heightCells высота карты
    Map(size_t widthCells = 94, size_t heightCells = 60);
    /// @brief Конструктор для загрузки карты из файла
    /// @param path путь до файла, из которого нужно загрузить данные
    /// @param numberOfEvolution номер эволюции
    /// @param newWidth ширина карты
    /// @param newHeight высота карты
    Map(const std::string& path, int numberOfEvolution, size_t newWidth, size_t newHeight);
    /// @brief Конструктор копирования
    /// @param mapToCopy карта, которую нужно скопировать
    Map(const Map& mapToCopy);
    /// @brief Конструктор перемещения
    /// @param mapToMove карта, которую следует переместить
    Map(Map&& mapToMove);
    /// @brief Деструктор по умочанию
    ~Map() = default;
    /// @brief Оператор копирования
    /// @param mapToCopy карта, которую следует скопировать
    Map& operator=(const Map& mapToCopy);
    /// @brief Оператор перемещения
    /// @param mapToMove карта, которую следует переместить
    Map& operator=(Map&& mapToMove);
    /// @brief Оператор обращения по индексу
    /// @param index номер строки, к которой нужно обратиться
    /// @return строка с индексом index
    Row& operator[](size_t index);
    /// @brief Оператор обращения по индексу
    /// @param index номер строки, к которой нужно обратиться
    /// @return строка с индексом index
    const Row& operator[](size_t index) const;
    /// @brief Функция обновления карты
    void Update();
    /// @brief Функция запуска организмов на карту
    /// @param numberOfPixels количество организмов, которые должны жить на карте
    void MultiplyPixels(int numberOfPixels);
    /// @brief Функция распространения еды по карте
    /// @param numberOfFood количество еды, которое должно находиться на карте
    void CreateFood(int numberOfFood);
    /// @brief Функция распостранения яда по карте
    /// @param numberOfPoison количество яда, которое должно находиться на карте
    void SetPoison(int numberOfPoison);
    /// @brief Функция пересоздания карты
    /// @param organisms_ организмы, которые должны жить на новой карте
    void RecreateMap(const std::vector<Pixel*>& organisms_);
    /// @brief Функция клонирования организмов
    /// @param map_ старая карта
    /// @param organisms_ организмы, которых нужно размножить
    void ClonePixels(Map& map_, const std::vector<Pixel*>& organisms_);
    /// @brief Функция селекции
    /// @param organisms_ вектор организмов, из которых следует осуществить выборку
    std::vector<Pixel*> Selection(const std::vector<Pixel*>& organisms_);
    /// @brief Функция получения ширины карты
    /// @return ширина карты
    unsigned int GetWidth() const;
    /// @brief Функция получения высоты карты
    /// @return высота карты
    unsigned int GetHeight() const;
    /// @brief Функция получения количества столбцов в карте
    /// @return количество столбцов
    size_t GetWidthInCells() const;
    /// @brief Функция получения количества строк в карте
    /// @return количество строк
    size_t GetHeightInCells() const;
    /// @brief Функция получения огранизмов, живущих на карте
    /// @return вектор организмов, живущих на карте
    std::vector<Pixel*> GetOrganisms() const;
    /// @brief Функция получения умерших огранизмов
    /// @return вектор умерших организмов
    std::vector<Pixel*> GetStaticOrganisms() const;
    /// @brief Функция получения числа живых организмов на карте
    /// @return число живых организмов на карте
    size_t GetNumberOfAliveOrganisms() const;
    /// @brief Функция получения номера эволюции
    /// @return номер эволюции
    unsigned int GetEvolutionNumber() const;
    /// @brief Функция увеличения номера эволюции
    void IncreaseEvolutionNumber();
    /// @brief Функция получения задержки потока
    /// @return задержка потока
    int GetTimeToSleep() const;
    /// @brief Функция увеличения задержки потока
    /// @param delta значения увеличения задержки потока
    void IncreaseTimesToSleep(int delta);
    /// @brief Функция уменьшения задержки потока
    /// @param delta значения уменьшения задержки потока
    void DecreaseTimesToSleep(int delta);
    /// @brief Функция получения указателя на стену
    /// @return указатель на стену
    Wall* GetWall() const;
    /// @brief Функция установки организма на карту
    /// @param pixel_ указатель на организм, который следует установить
    void SetOrganism(Pixel* pixel_);
    /// @brief Функция обмена координатами
    /// @param hexagon1 указатель на гекс, с которыми нужно поменяться значениями координат
    /// @param hexagon2 указатель на гекс, с которыми нужно поменяться значениями координат
    void Swap(Hexagon* hexagon1, Hexagon* hexagon2);
    /// @brief Функция сохраниения в файл
    void SaveToFile() const;
    /// @brief Функция загрузки из файла
    /// @param numberOfEvolution номерэволюции, которую следует загрузить
    /// @param newWidth ширина карты, которую следует создать
    /// @param newHeight высота карты, которую следует создать
    void UploadFromFile(int numberOfEvolution, size_t newWidth, size_t newHeight);
    /// @brief Функция отрисовки
    /// @param window окно, в котором происходит отрисовка
    void Print(sf::RenderWindow* window) const;
private:
    /// @brief Ширина окна
    static const unsigned int width = 2000;
    /// @brief Высота окна
    static const unsigned int height = 1000;
    /// @brief Количество столбцов в карте
    size_t widthInCells;
    /// @brief Количество строк в карте
    size_t heightInCells;
    /// @brief карта
    std::vector<Row> map;
    /// @brief Живые организмы
    std::vector<Pixel*> organisms;
    /// @brief Умершие организмы
    std::vector<Pixel*> staticOrganisms;
    /// @brief указатель на стену
    Wall* wall;
    /// @brief Номер эволюции
    int evolutionNumber = 1;
    /// @brief Значение задержки потока
    int timeToSleep = 100;
};

#endif  //  EVOLUTION_MAP_HPP_