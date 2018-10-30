#include "Brain.hpp"
#include "Hexagon.hpp"

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
    resultsFirstLayer = std::vector<double>(N, doublerand());
    for (size_t i = 0; i < N; ++i)
    {
        std::vector<double> row;
        for (size_t j = 0; j < N; ++j)
        {
            row.push_back(doublerand());
        }
        matrixOfWeightsOfSecondLayer.push_back(row);
    }
    resultsSecondLayer = std::vector<double>(N, doublerand());
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

std::vector<bool> Brain::CreateVectorInput(const std::vector<std::shared_ptr<Hexagon>> surroundingObjects) const
{
    std::vector<bool> input;
    for (auto& a : surroundingObjects)
    {
        if (a != nullptr)
        {
            std::map<Hexagon::Type, bool> values = {{Hexagon::FOOD,  0},
                                                    {Hexagon::WATER, 0},
                                                    {Hexagon::PIXEL, 0}};
            values[a->GetType()] = true;
            for (auto &b : values)
                input.push_back(b.second);
        }
        else
        {
            input.push_back(false);
            input.push_back(false);
            input.push_back(false);
        }
    }
    return input;
}

//  Функция принимает на вход вектор указателей на объекты, окружающие пикселя и находящиеся в поле видимости
double Brain::Think(const std::vector<std::shared_ptr<Hexagon>> surroundingObjects3) const
{
    std::vector<bool> input = CreateVectorInput(surroundingObjects3);
    std::vector<double> resultsFLCopy = resultsFirstLayer;
    for (size_t i = 0; i < resultsFLCopy.size(); ++i)
    {
        for (size_t k = 0; k < input.size(); ++k)
        {
            resultsFLCopy[i] += matrixOfWeightsOfFirstLayer[i][k] * input[k];
        }
        resultsFLCopy[i] = sigmoid(resultsFLCopy[i]);
    }
    std::vector<double> output(7);
    std::vector<double> resultsSLCopy(resultsSecondLayer);
    for (size_t i = 0; i < resultsSLCopy.size(); ++i)
    {
        for (size_t k = 0; k < resultsFirstLayer.size(); ++k)
        {
            resultsSLCopy[i] += matrixOfWeightsOfSecondLayer[i][k] * resultsFLCopy[k];
        }
        resultsSLCopy[i] = sigmoid(resultsSLCopy[i]);
    }
    double result = 0;
    for (size_t i = 0; i < weightsOfThirdLayer.size(); ++i)
    {
        result += weightsOfThirdLayer[i] * resultsSLCopy[i];
    }
    return sigmoid(result);
}


//  проверка на 0.3
std::shared_ptr<Hexagon> Brain::GetSolution(const std::vector<std::shared_ptr<Hexagon>> surroundingObjects6) const
{
    std::vector<std::shared_ptr<Hexagon>> sObjectsCopy = surroundingObjects6;
    std::srand(std::time(nullptr));
    std::vector<double> values;
    for (size_t i = 0; i < surroundingObjects6.size(); ++i)
    {
        std::vector<std::shared_ptr<Hexagon>> vec(sObjectsCopy.begin(), sObjectsCopy.begin() + 3);
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