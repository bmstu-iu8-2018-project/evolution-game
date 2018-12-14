#ifndef NEURALLINK_H_
#define NEURALLINK_H_

class Neuron;

class Link
{
public:
    Link();
    explicit Link(Neuron* neuronLinkedTo, double weightToNeuron = 0);

    double GetWeight() const;
    void SetWeight(const double);
  
    void SetNeuronLinkedTo(Neuron*);
    Neuron* GetNeuronLinkedTo() const;
  
    void UpdateWeight(const double);

private:
  double weightToNeuron;
  Neuron* neuronConnectedTo;
};

#endif