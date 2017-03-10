#ifndef SICT_SPORTCAR_H_
#define SICT_SPORTCAR_H_
#include "Car.h"

namespace sict{
  class SportCar : public Car  {
  private:
	  int noOfPassengers_;

  public:
	  SportCar();
	  SportCar(int maxSpeed, int numOfPassengers);

    // implementations of Vehicle's pure virtual methods
	  void accelerate();
	  void brake();
	  virtual std::ostream& display(std::ostream& ostr) const;

  };
}
#endif