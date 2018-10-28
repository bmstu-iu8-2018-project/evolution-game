#include "Brain.hpp"

Brain::Brain()
{
    std::srand(std::time(nullptr));
    size_t N = 10;
    for (size_t i = 0; i < N; ++i)
    {
        std::vector<double> row;
        for (size_t j = 0; j < N; ++j)
        {
            row.push_back(doublerand());
        }
        matrixOfWeightsOfFirstLayer.push_back(row);
    }
    resultsFirstLayer = std::vector<double>(N, 0);
    for (size_t i = 0; i < N; ++i)
    {
        std::vector<double> row;
        for (size_t j = 0; j < N; ++j)
        {
            row.push_back(doublerand());
        }
        matrixOfWeightsOfSecondLayer.push_back(row);
    }
    resultsSecondLayer = std::vector<double>(N, 0);
    for (size_t i = 0; i < N; ++i)
    {
        weightsOfThirdLayer.push_back(doublerand());
    }
}


Brain::Brain(const Brain& brain)
        :    matrixOfWeightsOfFirstLayer(brain.matrixOfWeightsOfFirstLayer),
             resultsFirstLayer(brain.resultsFirstLayer),
             matrixOfWeightsOfSecondLayer(brain.matrixOfWeightsOfSecondLayer),
             resultsSecondLayer(brain.resultsSecondLayer)
{}
Brain& Brain::operator=(const Brain& brain)
{
    if (this != &brain)
    {
        matrixOfWeightsOfFirstLayer = brain.matrixOfWeightsOfFirstLayer;
        resultsFirstLayer = brain.resultsFirstLayer;
        matrixOfWeightsOfSecondLayer = brain.matrixOfWeightsOfSecondLayer;
        resultsSecondLayer = brain.resultsSecondLayer;
    }
}

std::vector<bool> Brain::CreateVectorInput(const std::vector<Hexagon*> surroundingObjects)
{
    std::vector<bool> input;
    for (auto& a : surroundingObjects)
    {
        std::map<Hexagon::Type, bool> values = {{Hexagon::FOOD, 0}, {Hexagon::WATER, 0}, {Hexagon::PIXEL, 0}};
        values[a->GetType()] = true;
        for (auto& b : values)
            input.push_back(b.second);
    }
    return input;
}

//  Функция принимает на вход вектор указателей на объекты, окружающие пикселя и находящиеся в поле видимости
double Brain::Think(const std::vector<Hexagon*> surroundingObjects3)
{
    std::vector<bool> input = CreateVectorInput(surroundingObjects3);
    for (size_t i = 0; i < resultsFirstLayer.size(); ++i)
    {
        for (size_t k = 0; k < input.size(); ++k)
        {
            resultsFirstLayer[i] += matrixOfWeightsOfFirstLayer[i][k] * input[k];
        }
        resultsFirstLayer[i] = sigmoid(resultsFirstLayer[i]);
    }
    std::vector<double> output(7);
    for (size_t i = 0; i < resultsSecondLayer.size(); ++i)
    {
        for (size_t k = 0; k < resultsFirstLayer.size(); ++k)
        {
            resultsSecondLayer[i] += matrixOfWeightsOfSecondLayer[i][k] * resultsFirstLayer[k];
        }
        resultsSecondLayer[i] = sigmoid(resultsSecondLayer[i]);
    }
    double result = 0;
    for (size_t i = 0; i < weightsOfThirdLayer.size(); ++i)
    {
        result += weightsOfThirdLayer[i] * resultsSecondLayer[i];
    }
    return sigmoid(result);
}


//  проверка на 0.3
Hexagon* Brain::GetSolution(const std::vector<Hexagon*> surroundingObjects6)
{
    std::vector<Hexagon*> sObjectsCopy = surroundingObjects6;
    std::srand(std::time(nullptr));
    std::vector<double> values;
    for (size_t i = 0; i < surroundingObjects6.size(); ++i)
    {
        std::vector<Hexagon*> vec(sObjectsCopy.begin(), sObjectsCopy.begin() + 3);
        sObjectsCopy.insert(sObjectsCopy.begin(), sObjectsCopy.back());
        sObjectsCopy.pop_back();
        values.push_back(Think(vec));
    }
    auto it = std::max_element(values.begin(), values.end());
    size_t result = (size_t)(it - values.begin());
    if (result == 7)
        return nullptr;
    return surroundingObjects6[result];
}

void Brain::ModifyBrain()
{

}