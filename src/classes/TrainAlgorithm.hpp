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
	void Train() const;
	void WeightsInitialization() const;
private:
	void CommonInitialization() const;
    Brain* brain;
};

#endif
