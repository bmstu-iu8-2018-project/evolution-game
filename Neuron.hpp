#ifndef NEURON_HPP_
#define NEURON_HPP_

#include "Link.hpp"
#include "NetworkFunction.hpp"
#include <fstream>
#include <iostream>
#include <vector>


const double LearningRate = 0.01;

class Neuron
{
public:
    Neuron();
    explicit Neuron(NetworkFunction*);
    Neuron(std::vector<Neuron*>&, NetworkFunction*);
    Neuron(const Neuron&);
    virtual	~Neuron();

    virtual Link* at(const size_t&) const;
    virtual void Input(double);
    virtual double Fire() const;

    virtual std::vector<Link*> GetLinksToNeurons() const;
    virtual size_t	GetNumOfLinks() const;
    virtual size_t GetNumOfInputLinks() const;
    virtual double GetSumOfWeights() const;
    virtual std::vector<Link*> GetInputLinks() const;
    virtual void ResetSumOfWeights();
    virtual double Process() const;
    virtual double Process(double) const;
    virtual double Derivative() const;

    virtual void SetLinkToNeuron(Link*);
    void SetSumOfWeights(double);
    virtual void SetInputLink(Link*);

    virtual void SaveNeuronState(const std::string&) const;
private:
    NetworkFunction* function;
    std::vector<Link*> inputLinks;
    std::vector<Link*> linksToNeurons;

    double sumOfWeights;
};


class OutputLayerNeuron
    : public Neuron
{
public:
    explicit OutputLayerNeuron(Neuron* inNeuron)
        : Neuron(*inNeuron)
    {};
};


class HiddenLayerNeuron
        : public Neuron
{
public:
    explicit HiddenLayerNeuron(Neuron* inNeuron)
            : Neuron(*inNeuron)
    {};
};

#endif
