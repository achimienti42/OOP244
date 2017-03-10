#define CRT_SECURE_NO_WARNINGS
#include "AidApp.h"
#include "AmaProduct.h"
#include "AmaPerishable.h"
#include <iomanip>
#include <cstring>
#include <fstream>

using namespace std;
namespace sict{

	void AidApp::pause()const{
		
		cout << endl; 
		cout << "Press Enter to continue..." << endl;
		cin.ignore();
	}

	int AidApp::menu(){

		int menuvalue;

		cout << "Disaster Aid Supply Management Program" << endl;
		cout << "1- List products" << endl;
		cout << "2- Display product" << endl;
		cout << "3- Add non-perishable product" << endl;
		cout << "4- Add perishable product" << endl;
		cout << "5- Add to quantity of purchased products" << endl;
		cout << "0- Exit program" << endl;
		cout << "> ";

		cin >> menuvalue;

		if (menuvalue == 1 || menuvalue == 2 || menuvalue == 3 || menuvalue == 4 || menuvalue == 5 ||menuvalue == 0){

			return menuvalue;
		}
		else {
			pause();
			return -1;
		}
	}

	void AidApp::saveRecs() {

		if (retrieveAdd()){

			noOfProducts_++;

		}

		datafile_.open(filename_, ios::out);

		for (int i = 0; i < noOfProducts_; i++) {

			product_[i]->store(datafile_, true);

		}

		product_[noOfProducts_] = nullptr;
		datafile_.clear();
		datafile_.close();
	}

	void AidApp::loadRecs() {

		int i = 0;
		char type[20];

		datafile_.open(filename_, ios::in);

		if (datafile_.is_open()) {

			while (datafile_.good()) {

				datafile_.getline(type, 10, ',');

				if (type[0] == 'N') {

					product_[i] = new AmaProduct;
					product_[i]->load(datafile_);

					if (!datafile_.eof()){
						datafile_.getline(type, 10, '\n');
					}
					i++;
				}
				else if (type[0] == 'P') {

					product_[i] = new AmaPerishable;
					product_[i]->load(datafile_);

					if (!datafile_.eof()){
						datafile_.getline(type, 10, '\n');
					}
					i++;
				}
				type[0] = 0;
			}
		}
		else {
			datafile_.clear();
			datafile_.close();
			datafile_.open("aidapp.txt", ios::out);
			datafile_.close();
		}
		noOfProducts_ = i;
		datafile_.close();
	}

	void AidApp::listProducts()const{
		
		double totalcost = 0;

		cout << " Row | SKU    | Product Name       | Cost  | QTY| Unit     |Need| Expiry   " << endl;
		cout << "-----|--------|--------------------|-------|----|----------|----|----------" << endl;

		for (int i = 0; i < noOfProducts_; i++){

			if (((i % 10) == 0) && (i > 0)){

				pause();

			}

			cout.fill(' ');
			cout << setw(4) << right << (i + 1) << " | ";

			product_[i]->write(cout, true);

			cout << setprecision(2);
			totalcost += (product_[i]->cost() * product_[i]->quantity());
			cout << endl;

		}
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "Total cost of support: $" << setprecision(2) << totalcost << endl;
	}

	int AidApp::searchProducts(const char* sku)const{

		int skunum = 0;
		char temp[200];

		for (int i = 0; i < noOfProducts_; i++){

			strcpy_s(temp,product_[i]->sku());

			if (strcmp(temp, sku) == 0){

				skunum = i;
				i = noOfProducts_ + 1;

			}
			else{

				skunum = -1;

			}
		}

		temp[0] = 0;
		return skunum;

	}

	void AidApp::addQty(const char* sku){

		int quantity = 0;
		char skunum[200];

		for (int i = 0; i < noOfProducts_; i++){

			strcpy_s(skunum, product_[i]->sku());

			if (strcmp(skunum, sku) == 0){


				
				product_[i]->write(cout, false);

				cout << endl << "Please enter the number of purchased items: ";
				cin >> quantity;

				if (quantity){

					if (quantity <= product_[i]->qtyNeeded() - product_[i]->quantity()){

						quantity += product_[i]->quantity();
						product_[i]->quantity(quantity);
						saveRecs();
						cout << "Updated!" << endl;
						return;

					}
					else{
						cout << "Too many items; only " << product_[i]->qtyNeeded() - product_[i]->quantity() << " is needed, please return the extra "
							<< (product_[i]->quantity() + quantity) - product_[i]->qtyNeeded() << " items." << endl;
						return;

					}
				}
				else{

					cout << "Invalid quantity value!" << endl;
					return;

				}
			}
		}
	}

	void AidApp::addProduct(bool isPerishable){
		
		if (isPerishable){

			product_[noOfProducts_] = new AmaPerishable;
			product_[noOfProducts_]->read(cin);

		}
		else{

			product_[noOfProducts_] = new AmaProduct;
			product_[noOfProducts_]->read(cin);

		}
	}

	AidApp::AidApp(const char filename[256]){

		strcpy_s(filename_, filename);
		noOfProducts_ = 0;
		product_[0] = nullptr;
		loadRecs();
		valueAdd(false);

	}

	int AidApp::run(){

		int option = menu();
		char sku[MAX_SKU_LEN];
		int skunum;
		bool retrieveAdd();

		if (product_[0] == nullptr){
			loadRecs();
		}

		if (option == 1){
			listProducts();
			pause();
			run();
		}

		else if (option == 2){
			cout << "Please enter the SKU: ";
			cin >> sku;
			skunum = searchProducts(sku);

			if (skunum != -1){

				product_[skunum]->write(cout, false);
				pause();
				run();
			}
			else{

				cout << "Not found!" << endl;
				pause();
				run();
			}
		}

		else if (option == 3){
			valueAdd(true);
			addProduct(false);
			saveRecs();
			pause();
			run();
		}

		else if (option == 4){
			valueAdd(true);
			addProduct(true);
			saveRecs();
			pause();
			run();
		}
		else if (option == 5){
			cout << "Please enter the SKU: ";
			cin >> sku;
			skunum = searchProducts(sku);

			if (skunum == -1){
				
				cout << "Not found!" << endl;
			}
			else{

				valueAdd(false);
				addQty(sku);

			}
			sku[0] = 0;
			pause();
			run();

		}

		if (option != 1 && option != 2 && option != 3 && option != 4 && option != 5 && option != 0){

			cout << "===Invalid Selection, try again.===";
			pause();
			run();
		}

	    if (option == 0){
			cout << "Goodbye!!" << endl;
		}
		

		return 0;
	}

	void AidApp::valueAdd(bool a){
		add = a;
	}

	bool AidApp::retrieveAdd(){
		return add;
	}
}

