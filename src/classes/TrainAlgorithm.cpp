#include <random>

#include "Brain.hpp"
#include "TrainAlgorithm.hpp"


double doublerand(double a, double b)
{
    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(a, b);
    return dis(e);
}

void TrainAlgorithm::CommonInitialization()
{
    for (size_t innerOfLayers = 0; innerOfLayers < brain->size(); innerOfLayers++)
    {
        for (size_t innerOfNeurons = 0; innerOfNeurons < brain->GetLayer(innerOfLayers).size(); innerOfNeurons++)
        {
            Neuron* currentNeuron = brain->GetLayer(innerOfLayers).at(innerOfNeurons);
            for (size_t innerOfLinks = 0; innerOfLinks < currentNeuron->GetNumOfLinks(); innerOfLinks++)
            {
                Link* currentLink = currentNeuron->at(innerOfLinks);
                double randWeight = doublerand(0, 1);
                currentLink->SetWeight(randWeight);
            }
        }
    }
}

void TrainAlgorithm::WeightsInitialization()
{
    CommonInitialization();

}

TrainAlgorithm::TrainAlgorithm(Brain* newBrain)
{
    brain = newBrain;
}

void TrainAlgorithm::Train()
{
    if (this == nullptr)
        return;
    for (size_t innerOfLayers = 0; innerOfLayers < brain->size(); innerOfLayers++)
    {
        for (size_t innerOfNeurons = 0; innerOfNeurons < brain->GetLayer(innerOfLayers).size(); innerOfNeurons++)
        {
            Neuron* currentNeuron = brain->GetLayer(innerOfLayers).at(innerOfNeurons);
            for (size_t innerOfLinks = 0; innerOfLinks < currentNeuron->GetNumOfLinks(); innerOfLinks++)
            {
                Link* currentLink = currentNeuron->at(innerOfLinks);
                double randWeight = doublerand(0, 1) / 10;
                currentLink->SetWeight(randWeight);
            }
        }
    }
    ///  mNeuralNetwork->UpdateWeights();
    //  mNeuralNetwork->ResetCharges();
}

