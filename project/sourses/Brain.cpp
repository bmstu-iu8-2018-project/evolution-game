#include "Brain.hpp"
#include "Hexagon.hpp"


Brain::Brain(const size_t& inInputs, const size_t& inOutputs, const size_t& inNumOfHiddenLayers, const size_t& inNumOfNeuronsInHiddenLayers)
{
	if(inInputs > 0 || inOutputs > 0)
	{
		inputs = inInputs;
		outputs = inOutputs;
		hidden  = inNumOfNeuronsInHiddenLayers;

        stateOfLife = 99;
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
				Neuron* hiddenneuron = neuronCreator->CreateHiddenNeuron(layers[0], OutputNeuronsFunc);
				HiddenLayer.push_back(hiddenneuron);
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

Brain::Brain(const Json& object)
{
    Json newObject = object["Brain"]["Layers"];
    inputs = static_cast<size_t>(object["Brain"]["Inputs"]);
    outputs = static_cast<size_t>(object["Brain"]["Outputs"]);
    hidden = static_cast<size_t>(object["Brain"]["Hidden"]);

    if(inputs > 0 || outputs > 0)
    {
        NetworkFunction* InputNeuronsFunc = new Sigmoid;
        NetworkFunction* OutputNeuronsFunc = new Sigmoid;

        std::vector<Neuron*> inputLayer;
        std::vector<Neuron*> outputLayer;
        neuronCreator = new PerceptronNeuronCreator;

        for (size_t inner = 0; inner < outputs; inner++)
            outputLayer.push_back(neuronCreator->CreateOutputNeuron(OutputNeuronsFunc));
        layers.push_back(outputLayer);

        for (size_t inner = 0; inner < 2; inner++)
        {
            std::vector<Neuron*> HiddenLayer;
            for (size_t j = 0; j < hidden; j++)
            {
                Neuron* hiddenneuron = neuronCreator->CreateHiddenNeuron(layers[0], OutputNeuronsFunc);
                HiddenLayer.push_back(hiddenneuron);
            }
            layers.insert(layers.begin(),HiddenLayer);
        }

        for (size_t inner = 0; inner < inputs; inner++)
        {
            inputLayer.push_back(neuronCreator->CreateInputNeuron(layers[0], InputNeuronsFunc));
        }
        layers.insert(layers.begin(),inputLayer);
        algorithm = new TrainAlgorithm(this);
        algorithm->WeightsInitialization(object);
    }
    else
    {
        throw std::logic_error("Error in Brain constructor:"
                               "The number of input and output neurons has to be more than 0");
    }
}

Brain& Brain::operator=(const Brain& newBrain)
{
    if (this != &newBrain)
    {
        neuronCreator = newBrain.neuronCreator;
        algorithm = newBrain.algorithm;
        layers = newBrain.layers;
        inputs = newBrain.inputs;
        outputs = newBrain.outputs;
        hidden = newBrain.hidden;
    }
    return *this;
}

std::vector<Neuron*> Brain::GetLayer(size_t index) const
{
    return layers[index];
}

size_t Brain::Size() const
{
    return layers.size();
}

std::vector<Neuron*> Brain::GetOutputLayer() const
{
    return layers[layers.size() - 1];
}

std::vector<Neuron*> Brain::GetInputLayer() const
{
    return layers[0];
}

size_t Brain::GetInputs() const
{
    return inputs;
}

void Brain::Train()
{
    algorithm->Train(this);
}

const std::vector<double> Brain::CreateVectorInput(const std::vector<Hexagon*>& SurroundingObjects) const
{
    std::vector<double > input;
    for (auto& a : SurroundingObjects)
    {
        std::map<Hexagon::Type, double > values = {{Hexagon::Type::FOOD, 0},{Hexagon::Type::POISON, 0}, {Hexagon::Type::PIXEL, 0}};
        if (a != nullptr)
        {
            if (a->GetType() != Hexagon::Type::WATER && a->GetType() != Hexagon::Type::WALL)
                values[a->GetType()] = 1;
        }
        for (auto& b : values)
            input.push_back(b.second);
    }
    return input;
}

double Brain::Think(const std::vector<Hexagon*>& surroundingObjects3) const
{
    std::vector<double> input = CreateVectorInput(surroundingObjects3);
    input.push_back(stateOfLife);
    //  input.push_back(sigmoid);
    std::srand(std::time(nullptr));
    double result = 0;
    for (size_t i = 0; i < GetLayer(1).at(0)->GetNumOfInputLinks(); ++i)
    {
        for (size_t k = 0; k < input.size(); ++k)
        {
            result += GetLayer(1).at(i)->GetInputLinks().at(k)->GetWeight() * input[k];
        }
        GetLayer(1).at(i)->SetSumOfWeights(result);
        result = 0;
    }
    for (size_t i = 0; i < GetLayer(2).at(0)->GetNumOfInputLinks(); ++i)
    {
        for (size_t k = 0; k < GetLayer(1).size(); ++k)
        {
            result += GetLayer(2).at(i)->GetInputLinks().at(k)->GetWeight() * GetLayer(1).at(k)->GetSumOfWeights();
        }
        result = GetLayer(2).at(i)->Process(result);
        GetLayer(2).at(i)->SetSumOfWeights(result);
        result = 0;
    }
    result = 0;
    double sumresult  = 0;
    for (size_t i = 0; i < GetOutputLayer().size() ; ++i)
    {
        for (size_t k = 0; k < GetLayer(2).size(); ++k)
        {
            result += GetLayer(3).at(i)->GetInputLinks().at(k)->GetWeight() * GetLayer(2).at(k)->GetSumOfWeights();
        }
        GetOutputLayer().at(i)->Process(result);
        GetOutputLayer().at(i)->SetSumOfWeights(result);
        sumresult += result;
        result = 0;
    }
    return GetLayer(1).at(1)->Process(sumresult);
}

Hexagon* Brain::GetSolution(const std::vector<Hexagon*>& surroundingObjects6) const
{
    std::vector<Hexagon*> sObjectsCopy = surroundingObjects6;
    std::srand(std::time(NULL));
    std::vector<double> values;
    int diff = 0;

    for (size_t i = 0; i < surroundingObjects6.size(); ++i)
    {
        std::vector<Hexagon*> vec(sObjectsCopy.begin(), sObjectsCopy.begin() + 3);
        Hexagon* hex = sObjectsCopy.back();
        sObjectsCopy.insert(sObjectsCopy.begin(), hex);
        sObjectsCopy.erase(sObjectsCopy.begin() + surroundingObjects6.size() - 1);

        //  Think(vec, values);

        values.push_back(Think(vec));
        ++diff;
    }

    auto it = std::max_element(values.begin(), values.end());
    size_t result = (size_t)(it - values.begin());
    if (result == 7)
        return nullptr;
    sObjectsCopy.clear();
    for (size_t i = 0; i < values.size() - 1; ++i)
    {
        if (*it == values[i])
        {
            sObjectsCopy.push_back(surroundingObjects6[i]);
        }
    }
    if (sObjectsCopy.size() > 1)
        result = intrand(0, sObjectsCopy.size());
    return sObjectsCopy[result];
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

void Brain::UpdateStateOfLife(double newState)
{
    stateOfLife = 1 - GetLayer(1).at(1)->Process(newState);
}

const Json Brain::getJson() const
{
    Json j;
    j["Inputs"] = inputs;
    j["Outputs"] = outputs;
    j["Hidden"] = hidden;
    Json jsonForlayers;
    Json jj;
    for (size_t indOfLayer = 0; indOfLayer < layers.size() - 1; indOfLayer++)
    {
        for (size_t indOfNeuron = 0; indOfNeuron < layers[indOfLayer].size(); indOfNeuron++)
        {
            Json neuronState = layers[indOfLayer].at(indOfNeuron)->getJson();
            jj.push_back(neuronState);
        }
        jsonForlayers.push_back(jj);
        jj.clear();
    }
    j["Layers"] = jsonForlayers;
    return j;
}