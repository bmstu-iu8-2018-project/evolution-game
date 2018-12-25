#ifndef EVOLUTION_NETWORKFUNCTION_HPP_
#define EVOLUTION_NETWORKFUNCTION_HPP_

#include <cmath>


/// @brief Родительский класс функции
class NetworkFunction
{
public:
    /// @brief Конструктор по умочанию
    NetworkFunction() = default;
    /// @brief Деструктор по умолчанию
    virtual ~NetworkFunction() = default;
    /// @brief Функция получения значения функции
    /// @param x значение аргумента
    /// @result значение функции
    virtual double Process(const double x)
    {
        return 0;
    }
    /// @brief Функция получения значения производной функции
    /// @param x значение аргумента
    /// @result значение производной функции
    virtual double Derivative(double x)
    {
        return 0;
    }
};

/// @brief Класс сигмоидной функции
class Sigmoid
        : public NetworkFunction
{
public:
    /// @brief Функция получения значения функции
    /// @param x значение аргумента
    /// @result значение функции
    double Process(const double x) override
    {
        return (1 / (1 + exp(-x)));
    };
    /// @brief Функция получения значения производной функции
    /// @param x значение аргумента
    /// @result значение производной функции
    double Derivative(const double x) override
    {
        return Process(x) * (1 - Process(x));
    };
};


#endif  //  EVOLUTION_NETWORKFUNCTION_HPP_


