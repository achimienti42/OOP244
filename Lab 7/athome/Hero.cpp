#include <iostream>
#include <cstring>
#include "Hero.h"
#define _CRT_SECURE_NO_WARNINGS 

namespace sict{

	Hero::Hero(){

		name_[0] = '\0';

		strength_ =  0 ;

	}

	Hero::Hero(const char* name, double strength){

		strcpy_s(name_, name);

		strength_ = strength;
	}

	double Hero::getStrength() const{

		if (isEmpty() == false){

			return strength_;

		}

		else{
			
			return 0;
		}

	}

	bool Hero::isEmpty() const{

		if (name_[0] == '\0' && strength_ == 0){

			return true;

		}

		else{

			return false;

		}

	}

	void Hero::display(std::ostream& ostr) const{

		double temp = 0;

		if (isEmpty()){


		}
		  else {

			  temp = strength_;

			if (temp < 1){

				temp = 0;

			}

			std::cout << name_ << " - " << temp << '\n';
		}

	}

	void Hero::operator-=(double strength){

		strength_ = strength_ - strength;

	}

	void Hero::operator+=(double strength){

		strength_ = strength_ + strength;

	}

	bool operator<(const Hero& a, const Hero& b){

		if (a.getStrength() > b.getStrength()){

			return false;

		}

		else{

			return true;
		

		}

	}


	double Hero::Empty(){

		if (isEmpty()){

			strength_ = 0;
		}

		return strength_;
	}

}
