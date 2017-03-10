#ifndef SICT_SUPERHERO_H_
#define SICT_SUPERHERO_H_
#include <iostream>
#include "Hero.h"

namespace sict{

	class SuperHero : public Hero{

	private:
		char name_[21];
		double strength_;
		double multi_;
	public:
		SuperHero();
		SuperHero(const char* name, double strength, double multi);
		double getStrength() const;
		void display(std::ostream& ostr) const;
		void operator*=(SuperHero &);
	};
}
#endif