#include "Car.h"
#include <ostream>
namespace sict{

	void Car::speed(int value){

		speed_ = value;

		if (value > maxSpeed_){

			maxSpeed_ = value;
		}

		else
		{
			value = 0;
		}

	}

	int Car::maxSpeed() const{
		return maxSpeed_;
	}

	int Car::speed()const{
		return speed_;
	}
	

	Car::Car(int value){

		maxSpeed_ = value;
		speed_ = 0;
	}

	std::ostream& operator<<(std::ostream& ostr, Car& c){

		return c.display(ostr);



	}

}