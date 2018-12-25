#ifndef EVOLUTION_NEURON_HPP_
#define EVOLUTION_NEURON_HPP_

#include <vector>

#include <nlohmann/json.hpp>

#include "Link.hpp"
#include "NetworkFunction.hpp"

using Json = nlohmann::json;


/// @brief Класс нейрона
class Neuron
{
public:
    /// @brief Конструктор по умочанию
    Neuron();
    /// @brief Конструктор, создающий нейрон с заданной функцией
    /// @brief func функция, с которой будет создан нейрон
    explicit Neuron(NetworkFunction* func);
    /// @brief Конструктор по умолчанию
    /// @param vectorOfNeurons вектор нейронов, с которыми соединен нейрон
    /// @param func функция нейрона
    Neuron(std::vector<Neuron*>& vectorOfNeurons, NetworkFunction* func);
    /// @brief Конструктор копирования
    /// @param neuron нейрон, который следует скопировать
    Neuron(const Neuron& neuron);
    /// @brief Деструктор по умолчанию
    virtual	~Neuron();
    /// @brief Функция обращения к связи по индексу
    /// @param index индекс связи, к которой нужно обратиться
    /// @return связь
    virtual Link* at(const size_t& index) const;
    /// @brief Функция изменения веса нейрона
    /// @param deltaWeight значение, на котрое следует изменить вес нейрона
    virtual void Input(double deltaWeight);
    /// @brief Функция получения всех связей нейрона
    /// @return все связи нейрона
    virtual std::vector<Link*> GetLinksToNeurons() const;
    /// @brief Функция получения числа связей нейрона
    /// @return число связей нейрона
    virtual size_t GetNumOfLinks() const;
    /// @brief Функция получения числа входных связей нейрона
    /// @return число входных связей нейрона
    virtual size_t GetNumOfInputLinks() const;
    /// @brief Функция получения веса нейрона
    /// @brief вес нейрона
    virtual double GetSumOfWeights() const;
    /// @brief Функция получения входных связей нейрона
    /// @return все входные связи нейрона
    virtual std::vector<Link*> GetInputLinks() const;
    /// @brief Функция обнуления веса нейрона
    virtual void ResetSumOfWeights();
    /// @brief Функция получения значения функции
    /// @param x значение аргумента
    /// @return значение функции
    virtual double Process(double x) const;
    /// @brief Функция добавления выходной связи
    /// @param link указатель на связь
    virtual void SetLinkToNeuron(Link* link);
    /// @brief Функция установки веса нейрона
    /// @param x значение аргумента
    void SetSumOfWeights(double x);
    /// @brief Функция добавления входной связи
    /// @param link указатель на связь
    virtual void SetInputLink(Link* link);
    /// @brief Функция преобразования данных класса в формат Json
    /// @return данные класса в формате Json
    const Json getJson() const;
private:
    /// @brief указатель на функцию нейрона
    NetworkFunction* function;
    /// @brief все входные связи
    std::vector<Link*> inputLinks;
    /// @brief все выходные связи
    std::vector<Link*> linksToNeurons;
    /// @brief вес нейрона
    double sumOfWeights;
};

/// @brief Выходной нейрон
class OutputLayerNeuron
    : public Neuron
{
public:
    /// @brief Конструктор копирования
    /// @param inNeuron указатель на нейрон, который следует скопировать
    explicit OutputLayerNeuron(Neuron* inNeuron)
        : Neuron(*inNeuron)
    {};
};

/// @brief Скрытый нейрон
class HiddenLayerNeuron
        : public Neuron
{
public:
    /// @brief Конструктор копирования
    /// @param inNeuron указатель на нейрон, который следует скопировать
    explicit HiddenLayerNeuron(Neuron* inNeuron)
            : Neuron(*inNeuron)
    {};
};

#endif  //  EVOLUTION_NEURON_HPP_
