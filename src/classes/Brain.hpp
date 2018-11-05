#ifndef NEURALNETWORK_HPP_
#define NEURALNETWORK_HPP_

#include <algorithm>
#include <ctime>
#include <map>
#include <iostream>
#include <string>

#include "NeuronCreator.hpp"
#include "TrainAlgorithm.hpp"

class Hexagon;

class TrainAlgorithm;

class Brain
{
public:
    Brain(const size_t &inInputs = 10, const size_t &inOutputs = 7, const size_t &inNumOfHiddenLayers = 2,
                  const size_t &inNumOfNeuronsInHiddenLayers = 10);

    ~Brain() = default;

    void Train() const;

    std::vector<Neuron*> GetLayer(size_t) const;

    size_t size() const;

    std::vector<Neuron*> GetOutputLayer() const;

    std::vector<Neuron*> GetInputLayer() const;

    size_t GetInputs() const;

    void ResetWeights() const;

    const std::vector<bool> CreateVectorInput(const std::vector<Hexagon*>) const;

    double Think(const std::vector<Hexagon*>) const;

    Hexagon* GetSolution(const std::vector<Hexagon*>) const;

    void ShowNetworkState() const;

private:
    NeuronCreator* neuronCreator;
    TrainAlgorithm* algorithm;
    std::vector<std::vector<Neuron*>> layers;
    size_t inputs;
    size_t outputs;
    size_t hidden;
};

#endif
