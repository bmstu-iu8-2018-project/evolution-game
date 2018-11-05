#ifndef NETWORKFUNCTION_H_
#define NETWORKFUNCTION_H_

#include <math.h>

class NetworkFunction
{
public:
  NetworkFunction() = default;
  virtual ~NetworkFunction() = default;
  virtual const double Process(const double) = 0;
  virtual const double Derivative(double) = 0;
};


class Sigmoid
        : public NetworkFunction
{
public:
  const double Process(const double x) override
  {
      return (1 / (1 + exp(-x)));
  };
  const double Derivative(const double x) override
  {
      return Process(x) * (1 - Process(x));
  };
};


#endif


