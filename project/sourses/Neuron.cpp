#include "Neuron.hpp"

Neuron::Neuron()
        :   function(new Sigmoid),
            sumOfWeights(0)
{}


Neuron::Neuron(NetworkFunction* func)
        :   function(func),
            sumOfWeights(0)
{}

Neuron::Neuron(std::vector<Neuron*>& neuronsLinks, NetworkFunction* func)
{
    function = func;
    sumOfWeights = 0;
    for (size_t i = 0; i < neuronsLinks.size(); i++)
    {
        auto* pLink = new Link(neuronsLinks[i], 0);
        linksToNeurons.push_back(pLink);
        neuronsLinks[i]->SetInputLink(pLink);
    }
}

Neuron::Neuron(const Neuron& n)
{
    function = n.function;
    inputLinks = n.inputLinks;
    linksToNeurons = n.linksToNeurons;
    sumOfWeights = n.sumOfWeights;
}

Neuron::~Neuron()
{
    delete function;
}

Link* Neuron::at(const size_t& index) const
{
    return linksToNeurons[index];
}

void Neuron::Input(double deltaWeight)
{
    sumOfWeights += deltaWeight;
}

double Neuron::Fire() const
{
    for (size_t inner = 0; inner < GetNumOfLinks(); inner++)
    {
        Link* pCurrentLink = linksToNeurons[inner];
        Neuron* pCurrentNeuronLinkedTo = pCurrentLink->GetNeuronLinkedTo();

        const double dWeight = pCurrentLink->GetWeight();
        double	dCharge = sumOfWeights;
        double 	dXi =  (function->Process(dCharge));
        double 	dOutput = dXi*dWeight;
        pCurrentNeuronLinkedTo->Input(dOutput);
    }
    return sumOfWeights;
}

std::vector<Link*> Neuron::GetLinksToNeurons() const
{
    return linksToNeurons;
}

size_t Neuron::GetNumOfLinks() const
{
    return linksToNeurons.size();
}

size_t Neuron::GetNumOfInputLinks() const
{
    return inputLinks.size();
}

double Neuron::GetSumOfWeights() const
{
    return sumOfWeights;
}

std::vector<Link*> Neuron::GetInputLinks() const
{
    return inputLinks;
}

void Neuron::ResetSumOfWeights()
{
    sumOfWeights = 0;
}

double Neuron::Process() const
{
    return function->Process(sumOfWeights);
}

double Neuron::Process(double x) const
{
    return function->Process(x);
}

double Neuron::Derivative() const
{
    return function->Derivative(sumOfWeights);
}

void Neuron::SetLinkToNeuron(Link* newLLink)
{
    linksToNeurons.push_back(newLLink);
}

void Neuron::SetSumOfWeights(double x)
{
    sumOfWeights = function->Process(x);
}

void Neuron::SetInputLink(Link* newLLink)
{
    inputLinks.push_back(newLLink);
}

const Json Neuron::getJson() const
{
    Json j;
    for (size_t iNumOfOutLinks = 0; iNumOfOutLinks < linksToNeurons.size(); iNumOfOutLinks++)
    {
        j.push_back(linksToNeurons.at(iNumOfOutLinks)->GetWeight());
    }
    return j;
}


