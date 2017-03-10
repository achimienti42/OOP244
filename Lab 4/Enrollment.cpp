#include <iostream>
#include <cstring>
#include "Enrollment.h"
#define _CRT_SECURE_NO_WARNINGS

using namespace std;
namespace sict{
	bool Enrollment::isValid()const{
		return name_ && name_[0];
	}

	void Enrollment::setEmpty(){
		name_[0] = 0;
		code_[0] = 0;
		year_ = 0;
		semester_ = 0;
		slot_ = 0;
		enrolled_ = false;
	}

	bool Enrollment::isEnrolled() const{
		return enrolled_;
	}


	void Enrollment::display(bool nameOnly) const{
		if (isValid()){
			cout << name_;
			if (!nameOnly){
				cout << endl << code_ << ", Year: " << year_ << " semester: " << semester_ << " Slot: " << slot_ << endl;
				cout << "Status: " << (isEnrolled() ? "E" : "Not e") << "nrolled." << endl;
			}
		}
		else{
			cout << "InisValid enrollment!" << endl;
		}
	}
	void Enrollment::set(const char* name, const char* code, int year, int semester, int time, bool enrolled){


		if (name && code && name[0] != '\0' && code[0] != '\0' && year >= 2015 && semester > 0 && semester < 4 && time > 0 && time < 6){
			strcpy_s(name_, name);
			strcpy_s(code_, code);
			year_ = year;
			semester_ = semester;
			slot_ = time;
			enrolled_ = enrolled;
		}
		else
		{
			setEmpty();
		}


	}

	bool Enrollment::hasConflict(const Enrollment &other) const {

		bool valid = false;
		if (year_ == other.year_ && year_ != 0)
		{
			if (semester_ == other.semester_ && semester_ != 0)
			{
				if (slot_ == other.slot_ && slot_ != 0)
				{
					valid = true;
				}
			}
		}
		return valid;
	}

	Enrollment::Enrollment(){

		name_[0] = '\0';
		code_[0] = '\0';
		year_ = 0;
		semester_ = 0;
		slot_ = 0;
		enrolled_ = false;

	}
	Enrollment::Enrollment(const char* name, const char* code, int year, int semester, int time){

		set(name, code, year, semester, time);
		

	}
}

