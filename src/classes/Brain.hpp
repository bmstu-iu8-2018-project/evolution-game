#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <map>
#include <random>
#include <vector>

#include "Hexagon.hpp"

class Brain
{
    std::vector<std::vector<double>> matrixOfWeightsOfFirstLayer;
    std::vector<double> resultsFirstLayer;
    std::vector<std::vector<double>> matrixOfWeightsOfSecondLayer;
    std::vector<double> resultsSecondLayer;
    std::vector<double> weightsOfThirdLayer;
    double learnigRate = 0.01;

    double sigmoid(double a)
    {
        return 1 / (1 + exp(-a));
    }
public:
    double doublerand()
    {
        static std::mt19937 rng_engine((unsigned)time(nullptr));
        static std::uniform_real_distribution<double> distribution;
        return distribution(rng_engine);
    }

    Brain();
    ~Brain() = default;
    Brain(const Brain& brain);
    Brain& operator=(const Brain& brain);
    std::vector<bool> CreateVectorInput(const std::vector<Hexagon*> surroundingObjects);
    //  Функция принимает на вход вектор указателей на объекты, окружающие пикселя и находящиеся в поле видимости
    double Think(const std::vector<Hexagon*> surroundingObjects3);
    //  проверка на 0.3
    Hexagon* GetSolution(const std::vector<Hexagon*> surroundingObjects6);
    void ModifyBrain();
};


#endif