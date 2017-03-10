#include <iostream>
#include <cstring>
#include "Hero.h"
#include "Superhero.h"
#define _CRT_SECURE_NO_WARNINGS 

namespace sict{

	SuperHero::SuperHero(){

		name_[0] = '\0';
		strength_ = 0;
		multi_ = 0;


	}

	double SuperHero::getStrength() const{
		
		return strength_ * multi_;

	}


	void SuperHero::operator*=(SuperHero &b){

		if (getStrength() < b.getStrength()){

			b.strength_ = b.strength_ + strength_;
			strength_ = Empty();

		}
		else{

			strength_ = strength_ + b.strength_;
			b.strength_ = b.Empty();


		}

	
	}

	void SuperHero::display(std::ostream&) const{

		if (strength_ < 1){

		std::cout << "deceased superhero \n";

		}
		else {

			std::cout << "living superhero" << name_ << " - " << strength_ << "\n";
		}
		
	}

	SuperHero::SuperHero(const char* name, double strength, double multi){

		strcpy_s(name_, name);
		strength_ = strength;
		multi_ = multi;


	}



}