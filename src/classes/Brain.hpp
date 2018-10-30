#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <vector>

class Hexagon;

class Brain
{
    std::vector<std::vector<double>> matrixOfWeightsOfFirstLayer;
    std::vector<double> resultsFirstLayer;
    std::vector<std::vector<double>> matrixOfWeightsOfSecondLayer;
    std::vector<double> resultsSecondLayer;
    std::vector<double> weightsOfThirdLayer;
    double learnigRate = 0.01;


public:
    double doublerand()
    {
        static std::mt19937 rng_engine((unsigned)time(nullptr));
        static std::uniform_real_distribution<double> distribution;
        return distribution(rng_engine);
    }
    double sigmoid(const double a) const
    {
        return 1 / (1 + exp(-a));
    }
    Brain();
    ~Brain() = default;
    Brain(const Brain& brain);
    Brain& operator=(const Brain& brain);
    std::vector<bool> CreateVectorInput(const std::vector<std::shared_ptr<Hexagon>> surroundingObjects) const;
    //  Функция принимает на вход вектор указателей на объекты, окружающие пикселя и находящиеся в поле видимости
    double Think(const std::vector<std::shared_ptr<Hexagon>>) const;
    //  проверка на 0.3
    std::shared_ptr<Hexagon> GetSolution(const std::vector<std::shared_ptr<Hexagon>>) const;
    void ModifyBrain();
};


#endif