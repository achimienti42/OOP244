#define _CRT_SECURE_NO_WARNINGS
#include "AmaPerishable.h"
#include <cstring>
#include <string>
using namespace std;
namespace sict{


	AmaPerishable::AmaPerishable(const char filetag){

		settag(filetag);

	}

	const Date& AmaPerishable::expiry()const{

		return expiry_;


	}
	void AmaPerishable::expiry(const Date& value){

		expiry_ = value;

	}

	std::fstream& AmaPerishable::store(std::fstream& file, bool addNewLine)const{

		AmaProduct::store(file, false);

		file << ',' << expiry_.year_ << '/' << expiry_.mon_ << '/' << expiry_.day_ << endl;
		if (addNewLine) {
			file << endl;
		}
		return file;

	}

	std::fstream& AmaPerishable::load(std::fstream& file){

		AmaProduct::load(file);

		int tempi = 0;

		file.ignore(1, ',');
		file >> tempi;
		expiry_.year_ = tempi;

		file.ignore(1, '/');
		file >> tempi;
		expiry_.mon_ = tempi;

		file.ignore(1, '/');
		file >> tempi;
		expiry_.day_ = tempi;

		return file;
	}

	std::ostream& AmaPerishable::write(std::ostream& os, bool linear)const{


		AmaProduct::write(os, linear);

		if (err_.isClear()){
			if (!linear){

				os << "Expiry date: ";

			}

			expiry().Date::write(os);
		}

		return os;
	}

	std::istream& AmaPerishable::read(std::istream& is){

		int error = NO_ERROR;
		char msg[30] = "No Error";
		int numday;

		Date temp;

		AmaProduct::read(is);

		if (err_.isClear()){

			cout << "Expiry date (YYYY/MM/DD): ";
			temp.Date::read(is);

			if (!is.fail()){
				
				if (temp.year_ < MIN_YEAR || temp.year_ > MAX_YEAR){

					error = YEAR_ERROR;
					is.setstate(ios::failbit);
					strcpy(msg, "Invalid Year in Date Entry");

				}
				else if (temp.mon_ < 1 || temp.mon_ > 12){

					error = MON_ERROR;
					is.setstate(ios::failbit);
					strcpy(msg, "Invalid Month in Date Entry");

				}

				else {

					numday = temp.mdays();

					if (temp.day_ > numday || temp.day_ < 1){

						error = DAY_ERROR;
						is.setstate(ios::failbit);
						strcpy(msg, "Invalid Day in Date Entry");
					}
				}
			}
			else {

				error = CIN_FAILED;
				is.setstate(ios::failbit);
				strcpy(msg, "Invalid Date Entry");

			}

			if (error != NO_ERROR){

				err_.message(msg);
			}

		}
		expiry(temp);
		return is;
	}
}
