#ifndef TRAINALGORITHM_H_
#define TRAINALGORITHM_H_

#include <vector>
#include </home/mariasolovyova/CLionProjects/Evolution/tools/json/single_include/nlohmann/json.hpp>

using Json = nlohmann::json;

class Brain;

class TrainAlgorithm
{
public:
    TrainAlgorithm() = default;
    ~TrainAlgorithm() = default;
    explicit TrainAlgorithm(Brain*);
	void Train(Brain*);
	void WeightsInitialization();
    void WeightsInitialization(const Json&);
private:
	void CommonInitialization();
    Brain* brain;
};

#endif
