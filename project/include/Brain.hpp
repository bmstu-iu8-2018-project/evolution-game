#ifndef NEURALNETWORK_HPP_
#define NEURALNETWORK_HPP_

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

class Brain
{
public:

    Brain(const size_t &inInputs = 10, const size_t &inOutputs = 7, const size_t &inNumOfHiddenLayers = 2,
                  const size_t &inNumOfNeuronsInHiddenLayers = 10);
    Brain(const Json&);
    ~Brain() = default;
    Brain& operator=(const Brain&);
    void Train();

    std::vector<Neuron*> GetLayer(size_t) const;

    size_t Size() const;

    std::vector<Neuron*> GetOutputLayer() const;

    std::vector<Neuron*> GetInputLayer() const;

    size_t GetInputs() const;

    void ResetWeights() const;

    const std::vector<double> CreateVectorInput(const std::vector<Hexagon*>&) const;

    double Think(const std::vector<Hexagon*>&, std::vector<double>&, int) const;

    Hexagon* GetSolution(const std::vector<Hexagon*>&) const;

    void UpdateStateOfLife(double);

    const Json getJson() const;

private:
    NeuronCreator* neuronCreator;
    TrainAlgorithm* algorithm;
    std::vector<std::vector<Neuron*>> layers;
    size_t inputs;
    size_t outputs;
    size_t hidden;
    double stateOfLife;
    int intrand(int a, int b) const
    {
        static std::default_random_engine e;
        static std::uniform_int_distribution<> dis(a, b);
        return dis(e);
    }
};

#endif
