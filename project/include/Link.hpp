#ifndef EVOLUTION_NEURALLINK_HPP_
#define EVOLUTION_NEURALLINK_HPP_

class Neuron;

/// @brief Класс Связи между нейронами
class Link
{
public:
    /// @brief Конструктор по умочанию
    Link();
    /// @brief Класс Клавиатуры
    /// @param neuronLinkedTo
    /// @param weightToNeuron
    explicit Link(Neuron* neuronLinkedTo, double weightToNeuron = 0);
    /// @brief Функция получения веса связи
    /// @return вес связи
    double GetWeight() const;
    /// @brief Функция установки веса
    /// @param weight новый вес связи
    void SetWeight(const double weight);
    /// @brief Функция установки связи с нейроном
    /// @param neuronLinkedTo нейрон, с которым следует установить связь
    void SetNeuronLinkedTo(Neuron* neuronLinkedTo);
    /// @brief Функция получения нейрона, к которому присоединена связь
    /// @return нейрон, к которому присоединена связь
    Neuron* GetNeuronLinkedTo() const;
    /// @brief Функция изменения веса связи
    /// @param delta значение, на которое изменяется занчение веса связи
    void UpdateWeight(const double delta);

private:
    /// @brief Значение веса,
  double weightToNeuron;
    /// @brief Класс Клавиатуры
  Neuron* neuronConnectedTo;
};

#endif  //  EVOLUTION_NEURALLINK_HPP_