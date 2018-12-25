#ifndef EVOLUTION_NEURONCREATOR_HPP_
#define EVOLUTION_NEURONCREATOR_HPP_

#include "Neuron.hpp"
#include "NetworkFunction.hpp"


/// @brief Родительский класс нейронной фабрики
class NeuronCreator
{
public:
	/// @brief Конструктор по умочанию
	NeuronCreator() = default;
	/// @brief Деструктор по умолчанию
	virtual	~NeuronCreator() = default;
	/// @brief Функция, создающая входной нейрон
	/// @param inNeuronsLinkTo нейроны, с которыми следует соединить новый нейрон
	/// @param inNetFunc функция, по которой должен принимать решение нейрон
	virtual Neuron*	CreateInputNeuron(std::vector<Neuron*>& inNeuronsLinkTo, NetworkFunction* inNetFunc) = 0;
	/// @brief Функция, создающая выходной нейрон
	/// @param inNetFunc функция, по которой должен принимать решение нейрон
	virtual Neuron*	CreateOutputNeuron(NetworkFunction* inNetFunc) = 0;
	/// @brief Функция, создающая скрытый нейрон
	/// @param inNeuronsLinkTo нейроны, с которыми следует соединить новый нейрон
	/// @param inNetFunc функция, по которой должен принимать решение нейрон
	virtual Neuron*	CreateHiddenNeuron(std::vector<Neuron*>& inNeuronsLinkTo, NetworkFunction* inNetFunc) = 0;
};

/// @brief Нейронная фабрика
class PerceptronNeuronCreator
        : public NeuronCreator
{
public:
	/// @brief Функция, создающая входной нейрон
	/// @param inNeuronsLinkTo нейроны, с которыми следует соединить новый нейрон
	/// @param inNetFunc функция, по которой должен принимать решение нейрон
	Neuron* CreateInputNeuron(std::vector<Neuron*>& inNeuronsLinkTo, NetworkFunction* inNetFunc) override
	{
	    return new Neuron(inNeuronsLinkTo, inNetFunc);
	};
	/// @brief Функция, создающая выходной нейрон
	/// @param inNetFunc функция, по которой должен принимать решение нейрон
	Neuron* CreateOutputNeuron(NetworkFunction* inNetFunc) override
	{
	    return new OutputLayerNeuron(new Neuron(inNetFunc));
	};
	/// @brief Функция, создающая скрытый нейрон
	/// @param inNeuronsLinkTo нейроны, с которыми следует соединить новый нейрон
	/// @param inNetFunc функция, по которой должен принимать решение нейрон
	Neuron* CreateHiddenNeuron(std::vector<Neuron*>& inNeuronsLinkTo, NetworkFunction* inNetFunc) override
	{
	    return new HiddenLayerNeuron(new Neuron(inNeuronsLinkTo, inNetFunc));
	};
};


#endif  //  EVOLUTION_NEURONCREATOR_HPP_
