#include "Brain.hpp"
#include "Hexagon.hpp"

Brain::Brain(const size_t& inInputs, const size_t& inOutputs, const size_t& inNumOfHiddenLayers, const size_t& inNumOfNeuronsInHiddenLayers)
{
	if(inInputs > 0 && inOutputs > 0)
	{
		inputs = inInputs;
		outputs = inOutputs;
		hidden  = inNumOfNeuronsInHiddenLayers;

        NetworkFunction* InputNeuronsFunc = new Sigmoid;
		NetworkFunction* OutputNeuronsFunc = new Sigmoid;

        std::vector<Neuron*> inputLayer;
        std::vector<Neuron*> outputLayer;
        neuronCreator = new PerceptronNeuronCreator;
        algorithm = new TrainAlgorithm(this);

		for (size_t inner = 0; inner < inOutputs; inner++)
			outputLayer.push_back(neuronCreator->CreateOutputNeuron(OutputNeuronsFunc));
		layers.push_back(outputLayer);

		for (size_t inner = 0; inner < inNumOfHiddenLayers; inner++)
		{
			std::vector<Neuron*> HiddenLayer;
			for (size_t j = 0; j < inNumOfNeuronsInHiddenLayers; j++)
			{
				Neuron* hidden = neuronCreator->CreateHiddenNeuron(layers[0], OutputNeuronsFunc);
				HiddenLayer.push_back(hidden);
			}
			layers.insert(layers.begin(),HiddenLayer);
		}

		for (size_t inner = 0; inner < inInputs; inner++)
		{
			inputLayer.push_back(neuronCreator->CreateInputNeuron(layers[0], InputNeuronsFunc));
		}
		layers.insert(layers.begin(),inputLayer);
		algorithm->WeightsInitialization();
	}
	else
	{
        throw std::logic_error("Error in Brain constructor:"
                               "The number of input and output neurons has to be more than 0");
	}
}

std::vector<Neuron*> Brain::GetLayer(size_t index) const
{
    return layers[index];
};

size_t Brain::size() const
{
    return layers.size();
};

std::vector<Neuron*> Brain::GetOutputLayer() const
{
    return layers[layers.size() - 1];
};

std::vector<Neuron*> Brain::GetInputLayer() const
{
    return layers[0];
};
size_t Brain::GetInputs() const
{
    return inputs;
}

void Brain::Train() const
{
    algorithm->Train();
}

//  Функция принимает на вход вектор указателей на объекты, окружающиx пикселя
//  Если рядом стоит другой пиксель, то мы не можем перейти на клетку, на которой он стоит
const std::vector<bool> Brain::CreateVectorInput(const std::vector<Hexagon*> SurroundingObjects) const
{
    std::vector<bool> input;
    for (auto& a : SurroundingObjects)
    {
        std::map<Hexagon::Type, bool> values = {{Hexagon::Type::FOOD, 0},{Hexagon::Type::POISON, 0}, {Hexagon::Type::PIXEL, 0}};
        if (a != nullptr)
        {
            if (a->GetType() != Hexagon::Type::WATER)
                values[a->GetType()] = true;
        }
        for (auto& b : values)
            input.push_back(b.second);
    }
    return input;
}
double Brain::Think(const std::vector<Hexagon*> surroundingObjects3) const
{
    std::vector<bool> input = CreateVectorInput(surroundingObjects3);
    std::srand(std::time(nullptr)); /// FIXME :  Добавь значение уровня жизни
    double result = 0;
    for (size_t i = 0; i < GetLayer(1).at(0)->GetNumOfInputLinks(); ++i)
    {
        for (size_t k = 0; k < input.size(); ++k)
        {
            result += GetLayer(1).at(i)->GetInputLinks().at(k)->GetWeight() * input[k];
        }
        GetLayer(1).at(i)->SetSumOfWeights(result);
    }
    result = 0;
    for (size_t i = 0; i < GetLayer(2).at(0)->GetNumOfInputLinks(); ++i)
    {
        for (size_t k = 0; k < GetLayer(1).size(); ++k)
        {
            result += GetLayer(2).at(i)->GetInputLinks().at(k)->GetWeight() * GetLayer(1).at(k)->GetSumOfWeights();
        }
        GetLayer(2).at(i)->SetSumOfWeights(result);
    }
    result = 0;
    double sumresult = 0;
    for (size_t i = 0; i < GetOutputLayer().size() ; ++i)
    {
        for (size_t k = 0; k < GetLayer(2).size(); ++k)
        {
            result += GetLayer(3).at(i)->GetInputLinks().at(k)->GetWeight() * GetLayer(2).at(k)->GetSumOfWeights();
        }
        GetOutputLayer().at(i)->SetSumOfWeights(result);
        sumresult += result;
    }
    return GetLayer(1).at(1)->Process(sumresult);
}


/// FIXME :   проверка на 0.3
Hexagon* Brain::GetSolution(const std::vector<Hexagon*> surroundingObjects6) const
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

void Brain::ResetWeights() const
{
	for (size_t i = 0; i < layers.size(); i++)
	{
		for (size_t indexOfOutputElements = 0; indexOfOutputElements < layers.at(i).size(); indexOfOutputElements++)
		{
			layers.at(i).at(indexOfOutputElements)->ResetSumOfWeights();
		}
	}

}

void Brain::ShowNetworkState() const
{
	std::cout << std::endl;
	for (size_t indOfLayer = 0; indOfLayer < layers.size(); indOfLayer++)
	{
		std::cout << "Layer index: " << indOfLayer << std::endl;
		for (size_t indOfNeuron = 0; indOfNeuron < layers[indOfLayer].size(); indOfNeuron++)
		{
			std::cout << "  Neuron index: " << indOfNeuron << std::endl;
			layers[indOfLayer].at(indOfNeuron)->ShowNeuronState();
		}
	}
}