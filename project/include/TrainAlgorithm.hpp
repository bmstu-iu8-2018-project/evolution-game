#ifndef EVOLUTION_TRAINALGORITHM_HPP_
#define EVOLUTION_TRAINALGORITHM_HPP_

#include <vector>
#include <nlohmann/json.hpp>

using Json = nlohmann::json;

class Brain;


/// @brief Класс Алгоритма тренировки для мозга
class TrainAlgorithm
{
public:
	/// @brief Конструктор по умочанию
    TrainAlgorithm() = default;
	/// @brief Деструктор по умолчанию
    ~TrainAlgorithm() = default;
	/// @brief Конструктор, создающий алгоритм тренировки для мозга
	/// @param br указатель на мозг
    explicit TrainAlgorithm(Brain* br);
	/// @brief Функция, осуществляющая тренировку мозга
	/// @param br указатель на мозг
	void Train(Brain* br);
	/// @brief Функция, осуществляющая тренировку мозга
	void WeightsInitialization();
	/// @brief Функция, осуществляющая заполнение весов в соответствии со значениями в Json
	/// @brief значения весов
    void WeightsInitialization(const Json&);
private:
	/// @brief Функция, осуществляющая первоначальное заполнение весов
	void CommonInitialization();
	/// @brief указатель на мозг организма
    Brain* brain;
};

#endif  //  EVOLUTION_TRAINALGORITHM_HPP_
