#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <string>
#include "AmaProduct.h"
#include "Product.h"
#include "Errormessage.h"
#define TAB '\t'

using namespace std;

namespace sict{
	AmaProduct::AmaProduct(char tagfile){

		fileTag_ = tagfile;

	}

	const char*AmaProduct::unit()const{

		return unit_;

	}

	void AmaProduct::unit(const char* value){

		strcpy(unit_, value);

	}


	std::fstream& AmaProduct::store(std::fstream& file, bool addNewLine)const{

		file << fileTag_ << ',' << sku() << ',' << name() << ',' << price() << ',' << int(taxed()) << ',' << quantity() << ',' << unit() << ',' << qtyNeeded();

		if (addNewLine == true){

			file << endl;

		}

		return file;
	}
	std::fstream& AmaProduct::load(std::fstream& file){


		char buf[1001];
		double dbuf;
		int ibuf;
		
		if (file.is_open()){

			while (file.good() && !file.eof()){


				file.width(MAX_SKU_LEN);
				file.setf(std::ios::left);
				file >> buf; 
				sku(buf);
				
				

				file.setf(std::ios::left);
				file.width(20);
				file.ignore(9);
				file >> buf; 
				name(buf);
			

				file.setf(std::ios::right);
				file.setf(std::ios::fixed);
				file.width(7);
				file.precision(2);
				file.ignore(30);
				file >> dbuf; 
				price(dbuf); 
			

				file.setf(std::ios::right);
				file.width(4);
				file.ignore(10, ',');
				file >> ibuf;
				quantity(ibuf);
				

				file.unsetf(std::ios::right);
				file.width(10);
				file.ignore(16, ',');
				file >> buf;
				unit(buf);
				

				file.setf(std::ios::right);
				file.width(4);
				file.ignore(17, ',');
				file >> ibuf; 
				qtyNeeded(ibuf);
				
			}
		}

		file.close();

		return file;
	}
	std::ostream& AmaProduct::write(std::ostream& os, bool linear)const{

		char* temp = 0;

		if (!(err_.isClear())){

			os << err_.message();
			return os;

		}

		else{

			if (linear){
				os.setf(std::ios::left);
				os.width(MAX_SKU_LEN);
				os << sku() << '|';
				os.setf(std::ios::left);
				os.width(20);
				temp = name();
				temp[0] = toupper(temp[0]);
				os << temp << '|';
				os.setf(std::ios::right);
				os.setf(std::ios::fixed);
				os.width(7);
				os.precision(2);
				os << cost() << '|';
				os.setf(std::ios::right);
				os.width(4);
				os << quantity() << '|';
				os.unsetf(std::ios::right);
				os.width(10);
				os << unit() << '|';
				os.setf(std::ios::right);
				os.width(4);
				os << qtyNeeded() << '|';

			}
			else{

				if (taxed()){

					os << "Sku: " << sku() << endl;
					temp = name();
					temp[0] = tolower(temp[0]);
					os << "Name: " << temp << endl;
					os << "Price: " << price() << endl;
					os << "Price after tax: " << cost() << endl;
					os << "Quantity On Hand: " << quantity() << " " << unit() << "s" << endl;
					os << "Quantity Needed: " << qtyNeeded() << endl;
				}

				else{

					os << "Sku: " << sku() << endl;
					temp = name();
					temp[0] = tolower(temp[0]);
					os << "Name: " << temp << endl;
					os << "Price: " << price() << endl;
					os << "Price after tax: " << "N/A" << endl;
					os << "Quantity On Hand: " << quantity() << " " << unit() << endl;
					os << "Quantity Needed:" << qtyNeeded() << endl;
				}
			}

			return os;

		}
	}
	std::istream& AmaProduct::read(std::istream& is){

		char buf[MAX_SKU_LEN];
		char YN;
		double dbuf;
		int ibuf;

		cout << "Sku: ";
		is >> buf;
		sku(buf);
		cout << "Name: ";
		is >> buf;
		name(buf);
		cout << "Unit: ";
		is >> buf;
		unit(buf);
		cout << "Taxed? (y/n): ";
		is >> YN;

		if (YN == 'Y' || YN == 'y' || YN == 'N' || YN == 'n'){

			taxed(YN);

			cout << "Price: ";
			is >> dbuf;

			price(dbuf);

			if (!(is.fail())){

				cout << "Quantity On hand: ";
				is >> ibuf;

				quantity(ibuf);

				if (!(is.fail())){

					cout << "Quantity Needed: ";
					is >> ibuf;

					qtyNeeded(ibuf);

					if (!(is.fail())){

						err_.clear();
						return is;

					}

					else{

						err_.message("Invalid Quantity Needed Entry");
						is.clear();
						is.setstate(ios::failbit);

					}
				}

				else{

					err_.message("Invalid Quantity Entry");
					is.clear();
					is.setstate(ios::failbit);

				}
			}
			else{

				err_.message("Invalid Price Entry");
				is.clear();
				is.setstate(ios::failbit);

			}
		}
		else{

			err_.message("Only (Y)es or (N)o are acceptable");
			is.clear();
			is.setstate(ios::failbit);

		}

		return is;
	}
}
