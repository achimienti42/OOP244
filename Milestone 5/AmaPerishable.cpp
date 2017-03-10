
#include "AmaPerishable.h"
using namespace std;
namespace sict{


	AmaPerishable::AmaPerishable() : AmaProduct(){

		AmaProduct(fileTag_) = 'P';

	}

	const Date AmaPerishable::expiry()const{
	
		return expiry_;
	
	
	}
	void AmaPerishable::expiry(const Date& value){

		expiry_ = value;

	}

	std::fstream& AmaPerishable::store(std::fstream& file, bool addNewLine = true)const{
	

		file << AmaPerishable() << ',' << sku() << ',' << name() << ',' << price() << ',' << int(taxed()) << ',' << quantity() << ',' << unit() << ',' << qtyNeeded() << ',' << expiry();

		if (addNewLine == true){

			file << endl;

		}

		return file;
	}

	std::fstream& AmaPerishable::load(std::fstream& file){
	
		file.open("amaPrd.txt", ios::in);

		char buf[2000];
		double dbuf;
		int ibuf;

		file >> buf;

		file >> buf;
		sku(buf);
		file >> buf;

		file >> buf;
		name(buf);
		file >> buf;

		file >> dbuf;
		price(dbuf);
		file >> buf;

		file >> ibuf;
		taxed(bool(ibuf));
		file >> buf;

		file >> ibuf;
		quantity(ibuf);
		file >> buf;

		file >> buf;
		unit(buf);
		file >> buf;

		file >> ibuf;
		qtyNeeded(ibuf);
		file >> buf;

		expiry();

		return file;
	}

	std::ostream& AmaPerishable::write(std::ostream& os, bool linear)const{

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
				os << expiry() << '|';

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
					os << "Expiry Date: " << expiry() << endl;
					os << "NO NEW LINE";
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
					os << "Expiry Date" << expiry() << endl;
					os << "NO NEW LINE";
				}
			}

			return os;
		}
	}

		std::istream& AmaPerishable::read(std::istream& is){

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
