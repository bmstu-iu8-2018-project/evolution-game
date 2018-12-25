#ifndef EVOLUTION_BRAIN_HPP_
#define EVOLUTION_BRAIN_HPP_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "NeuronCreator.hpp"
#include "TrainAlgorithm.hpp"

#include <nlohmann/json.hpp>

using Json = nlohmann::json;

class Hexagon;

class TrainAlgorithm;

/// @brief Класс, описывающий мозг организма
class Brain
{
public:
    /// @brief Конструктор создающий нейронную сеть с заданными параметрами
    /// @param inInputs количество входных нейронов
    /// @param inOutputs количество выходных нейронов
    /// @param inNumOfHiddenLayers количество скрытых слоев
    /// @param inNumOfNeuronsInHiddenLayers количество нейронов в скрытых слоях
    Brain(const size_t& inInputs = 10, const size_t &inOutputs = 7, const size_t &inNumOfHiddenLayers = 2,
                  const size_t &inNumOfNeuronsInHiddenLayers = 10);
    /// @brief Конструктор создающий нейронную сеть из данных формата Json
    /// @param json данные, которые нужно преобразовать в объект класса Brain
    Brain(const Json& json);
    /// @brief Деструктор по умолчанию
    ~Brain() = default;
    /// @brief Конструктор копирования
    /// @param brain мозг, который нужно скопировать
    Brain& operator=(const Brain& brain);
    /// @brief Функция изменения(тренировки) мозга(нейронной сети) организма
    void Train();
    /// @brief Функция для получения слоя нейронной сети по номеру
    /// @param n номер слоя в нейронной сети
    /// @return слой нейронной сети
    std::vector<Neuron*> GetLayer(size_t n) const;
    /// @brief Функция для получения количества слоев в нейронной сети
    /// @return количество слоёв в нейронной сети
    size_t Size() const;
    /// @brief Функция по получению выходного слоя нейронной сети
    /// @return выходной слой нейронной сети
    std::vector<Neuron*> GetOutputLayer() const;
    /// @brief Функция по получению входного слоя нейронной сети
    /// @return входной слой нейронной сети
    std::vector<Neuron*> GetInputLayer() const;
    /// @brief Функция по получению количества входных нейронов
    /// @return количество входных нейронов
    size_t GetInputs() const;
    /// @brief Функция, обнуляющая все веса нейронной сети
    void ResetWeights() const;
    /// @brief Функция, преобразующая данные об окружающих объектах
    /// @param SurroundingObjects вектор указателей на объекты, окружающие организм
    /// @return вектор входных значений для нейронной сети
    const std::vector<double> CreateVectorInput(const std::vector<Hexagon*>& SurroundingObjects) const;
    /// @brief Функция, высчитывающая степень уверенности нейронной сети
    /// @param surroundingObjects3 вектор указателей на 3 объекта, попадающие в его поле зрения
    /// @return степень уверенности нейронной сети(стоит ли перемещаться в данном напрвлении)
    double Think(const std::vector<Hexagon*>& surroundingObjects3) const;
    /// @brief Функция, принимающая решение о самом выгодном направлении перемещения
    /// @param surroundingObjects6 вектор указателей на объекты, окружающих организм
    /// @return указатель на объект, в направлении которого следует перемещаться
    Hexagon* GetSolution(const std::vector<Hexagon*>& surroundingObjects6) const;
    /// @brief Функция, обновляющая состояние жизни организма
    /// @param newST новое состояние жизни организма
    void UpdateStateOfLife(double newST);
    /// @brief Функция по преобразованию мозга(нейронной сети) в формат Json
    /// @return мозг(нейронная сеть), преобразованная в формат Json
    const Json getJson() const;

private:
    /// @brief указатель на нейронную фабрику
    NeuronCreator* neuronCreator;
    /// @brief указатель на алгоритм тренировки нейронной сети
    TrainAlgorithm* algorithm;
    /// @brief нейронная сеть
    std::vector<std::vector<Neuron*>> layers;
    /// @brief количество входных нейронов
    size_t inputs;
    /// @brief количество выходных нейронов
    size_t outputs;
    /// @brief количество нейронов на скрытых слоях
    size_t hidden;
    /// @brief Значение уровня жизни организма
    double stateOfLife;
    /// @brief Функция рандома
    int intrand(int a, int b) const
    {
        static std::default_random_engine e;
        static std::uniform_int_distribution<> dis(a, b);
        return dis(e);
    }
};

#endif //  EVOLUTION_BRAIN_HPP_
