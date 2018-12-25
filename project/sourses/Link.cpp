#include "Link.hpp"

Link::Link()
        :   weightToNeuron(0),
            neuronConnectedTo(0)
{}

Link::Link(Neuron* neuronLinkedTo, double weightToNeuronNew)
        :   weightToNeuron(weightToNeuronNew),
            neuronConnectedTo(neuronLinkedTo)
{}

double Link::GetWeight() const
{
    return weightToNeuron;
}

void Link::SetWeight(const double newWeight)
{
    weightToNeuron = newWeight;
}

void Link::SetNeuronLinkedTo(Neuron* neuronLinkedTo)
{
    neuronConnectedTo = neuronLinkedTo;
}

Neuron* Link::GetNeuronLinkedTo() const
{
    return neuronConnectedTo;
}

void Link::UpdateWeight(const double deltaWeight)
{
    weightToNeuron += deltaWeight;
}