#ifndef NEURONFACTORY_H_
#define NEURONFACTORY_H_

#include "Neuron.hpp"

class NeuronCreator
{
public:
	NeuronCreator() = default;
	virtual	~NeuronCreator() = default;
	virtual Neuron*	CreateInputNeuron(std::vector<Neuron*>&, NetworkFunction*) = 0;
	virtual Neuron*	CreateOutputNeuron(NetworkFunction*) = 0;
	virtual Neuron*	CreateHiddenNeuron(std::vector<Neuron*>&, NetworkFunction*) = 0;
};

class PerceptronNeuronCreator
        : public NeuronCreator
{
public:
	Neuron* CreateInputNeuron(std::vector<Neuron*>& inNeuronsLinkTo, NetworkFunction* inNetFunc) override
	{
	    return new Neuron(inNeuronsLinkTo, inNetFunc);
	};
	Neuron* CreateOutputNeuron(NetworkFunction* inNetFunc) override
	{
	    return new OutputLayerNeuron(new Neuron(inNetFunc));
	};
	Neuron* CreateHiddenNeuron(std::vector<Neuron*>& inNeuronsLinkTo, NetworkFunction* inNetFunc) override
	{
	    return new HiddenLayerNeuron(new Neuron(inNeuronsLinkTo, inNetFunc));
	};
};


#endif
