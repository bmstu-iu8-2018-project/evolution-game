#ifndef TRAINALGORITHM_H_
#define TRAINALGORITHM_H_

#include <vector>

class Brain;

class TrainAlgorithm
{
public:
    TrainAlgorithm() = default;
    ~TrainAlgorithm() = default;
    explicit TrainAlgorithm(Brain*);
	void Train();
	void WeightsInitialization();
private:
	void CommonInitialization();
    Brain* brain;
};

#endif
