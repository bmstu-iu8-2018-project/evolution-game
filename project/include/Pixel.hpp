#ifndef EVOLUTION_PIXEL_HPP_
#define EVOLUTION_PIXEL_HPP_

#include <algorithm>
#include "Hexagon.hpp"
#include "Food.hpp"
#include "Map.hpp"
#include <nlohmann/json.hpp>

using Json = nlohmann::json;

/// @brief Класс Организма
class Pixel
        : public Hexagon
{
    /// @brief Мозг организма
    Brain brain;
    /// @brief Число итераций, которые прожил организма
    unsigned int numberOfLifeIterations;
    /// @brief Количество еды, которое съел организм
    int howMuchFoodAte;
    /// @brief Количество яда, которое съел организм
    int howMuchPoisonAte;
public:
    /// @brief Конструктор по умолчанию
    explicit Pixel();
    /// @brief Конструктор, создающий организм с заданными координатами
    /// @param xInPixels расположение гекса в пикселях по оси Ox на окне
    /// @param yInPixels расположение гекса в пикселях по оси Oy на окне
    /// @param xInCells номер строки в матрице карты
    /// @param yInCells номер столбца в матрице карты
    Pixel(double xInPixels, double yInPixels, size_t xInCells, size_t yInCells);
    /// @brief Конструктор, создающий организм с заданными координатами и мозгом
    /// @param xInPixels расположение гекса в пикселях по оси Ox на окне
    /// @param yInPixels расположение гекса в пикселях по оси Oy на окне
    /// @param xInCells номер строки в матрице карты
    /// @param yInCells номер столбца в матрице карты
    /// @param brainNew мозг организма
    Pixel(double xInPixels, double yInPixels, size_t xInCells, size_t yInCells, const Brain& brainNew);
    /// @brief Конструктор, создающий организм с заданными координатами, мозгом и жизнями
    /// @param xInPixels расположение гекса в пикселях по оси Ox на окне
    /// @param yInPixels расположение гекса в пикселях по оси Oy на окне
    /// @param xInCells номер строки в матрице карты
    /// @param yInCells номер столбца в матрице карты
    /// @param lifesNew количество жизней организма
    /// @param brainNew мозг организма
    Pixel(double xInPixels, double yInPixels, size_t xInCells, size_t yInCells, double lifesNew, const Brain& brainNew);
    /// @brief Конструктор, создающий организм с заданными координатами, мозгом, жизнями и ядовитостью
    /// @param xInPixels расположение гекса в пикселях по оси Ox на окне
    /// @param yInPixels расположение гекса в пикселях по оси Oy на окне
    /// @param xInCells номер строки в матрице карты
    /// @param yInCells номер столбца в матрице карты
    /// @param lifesNew количество жизней организма
    /// @param brainNew мозг организма
    /// @param medicineNew степень ядовитости организма
    Pixel(double xInPixels, double yInPixels, size_t xInCells, size_t yInCells, double lifesNew, const Brain& brainNew, double medicineNew);
    /// @brief Конструктор копирования
    /// @param pixel организм, которого нужно склонировать
    Pixel(const Pixel& pixel);
    /// @brief Функция получения стоящих рядом объектов
    /// @param map карта, на которой стоит организм
    /// @return вектор объектов, окружающих организма
    std::vector<Hexagon*> LookAround(Map& map) const;
    /// @brief Функция обновления организма
    /// @param map карта, на которой стоит организм
    void Update(Map& map);
    /// @brief Функция употребления пищи
    /// @param hexToEat указатель на гекс, который нужно съесть
    /// @param map карта, на которой стоит организм
    void EatingFood(Hexagon* hexToEat, Map& map);
    /// @brief Функция передвижения
    /// @param hexToMove указатель на гекс, на который следует переместиться
    /// @param map карта, на которой стоит организм
    void Move(Map& map, Hexagon* hexToMove);
    /// @brief Функция размножения
    /// @param map карта, на которой стоит организм
    void Reproduction(Map& map);
    /// @brief Функция просмотра объектов, стоящих вокруг
    /// @param map карта, на которой стоит организм
    /// @param type тип гекса, который требуется найти
    Hexagon* ViewNearbyCells(Map& map, const Type& type);
    /// @brief Функция получения числа прожитых итераций
    /// @return число прожитых итераций
    unsigned int GetNumberOfLifeIterations() const;
    /// @brief Функция получения мозга организма
    /// @return xInPixels расположение гекса в пикселях по оси Ox на окне
    const Brain& GetBrain() const;
    /// @brief Функция получения количества еды, которое съел организм за жизнь
    /// @return количество еды, которое съел организм за жизнь
    int GetHowMuchFoodAte() const;
    /// @brief Функция получения количества яда, которое съел организм за жизнь
    /// @return количество яда, которое съел организм за жизнь
    int GetHowMuchPoisonAte() const;
    /// @brief Функция установки мозга
    /// @param brainNew мозг, который следует установить
    void SetBrain(const Brain& brainNew);
    /// @brief Функция обнуления количества прожитых итераций
    void ResetNumberOfLifeIterations();
    /// @brief Функция отрисовки
    /// @param window окно, в котором следует отрисовать организм
    void Print(sf::RenderWindow* window) const override;
    /// @brief Функция преобразования данных класса в формате Json
    /// @return данные класса в формате Json
    const Json getJson() const;
};

#endif  //  EVOLUTION_PIXEL_HPP_
