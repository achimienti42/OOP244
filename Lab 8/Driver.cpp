#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Driver.h"
using namespace std;
namespace sict{




	Driver::Driver(const char* name, Car& cRef): car_(cRef){

		strcpy(name_, name);
		car_ = cRef;

	}

	void Driver::drive(){

		car_.brake();
		car_.accelerate();
		showStatus();



	}
	void Driver::stop(){

		while (car_.speed() > 0){

			car_.brake();

		}

		showStatus();


	}

	void Driver::showStatus(){

		cout << name_ << " is driving this car." << endl;

		car_.display(cout) << endl;

	}

	


}