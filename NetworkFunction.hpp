#ifndef NETWORKFUNCTION_H_
#define NETWORKFUNCTION_H_

#include <math.h>

class NetworkFunction
{
public:
  NetworkFunction() = default;
  virtual ~NetworkFunction() = default;
  virtual double Process(const double)
  {
      return 0;
  }
  virtual double Derivative(double)
  {
      return 0;
  }
};


class Sigmoid
        : public NetworkFunction
{
public:
  double Process(const double x) override
  {
      return (1 / (1 + exp(-x)));
  };
  double Derivative(const double x) override
  {
      return Process(x) * (1 - Process(x));
  };
};


#endif


