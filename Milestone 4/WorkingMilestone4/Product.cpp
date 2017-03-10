#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include "Product.h"
#include "general.h"
#include "Streamable.h"

using namespace std;

namespace sict{

	
	Product::Product(){

		sku_[0] = 0;
		name_ = 0;
		price_ = 0;
		taxed_ = 0;
		quantity_ = 0;
		qtyNeeded_ = 0;

	}

	Product::Product(const char *sku, const char *name, int quantity, double price, bool tax){

		strcpy(sku_, sku);

		name_ = new char[DISPLAY_LINES];

		strcpy(name_, name);
		quantity_ = 0;
		price_ = price;
		taxed_ = tax;

	}
		
	void Product::Copy(const Product& P){

		strcpy(sku_, P.sku_);

		name_ = new char[DISPLAY_LINES];

		strcpy(name_, P.name_);;
		quantity_ = P.quantity_;
		price_ = P.price_;
		taxed_ = P.taxed_;
		qtyNeeded_ = P.qtyNeeded_;

	}

	Product::~Product(){

		name_ = nullptr;
		delete[] name_;

	}

	Product& Product::operator=(const Product& P){

		Copy(P);
		return *this;

	}

	void Product::sku(char *sku){

		strcpy(sku_, sku);

	}
	void Product::price(double price){

		price_ = price;

	}
	void Product::name(char *name){

		name_ = new char[DISPLAY_LINES];
		if (name_ != nullptr){
			strcpy(name_, name);
		}

	}
	void Product::taxed(bool taxed){

		taxed_ = taxed;

	}
	void Product::quantity(int quantity){

		quantity_ = quantity;

	}
	void Product::qtyNeeded(int qtyNeeded){

		qtyNeeded_ = qtyNeeded;

	}

	const char* Product::sku()const{

		return sku_;
	}
	double Product::price()const{

		return price_;
	}
	const char* Product::name()const{

		return name_;
	}
	bool Product::taxed()const{

		return taxed_;
	}
	int Product::quantity()const{

		return quantity_;
	}
	int Product::qtyNeeded()const{

		return qtyNeeded_;
	}
	double Product::cost()const{

		if (taxed_){

			return price_ * TAX;
		}
		else{

			return price_;

		}
	 
	}

	bool Product::isEmpty()const{

		if (sku_[0] == 0 && name_ == nullptr && price_ == 0 && quantity_ == 0 && qtyNeeded_ == 0){
			return true;
		}
		else{

			return false;
		}

	}

	bool Product::operator == (char *sku){

		return strcmp(sku_, sku) == 0;

	}
	int Product::operator += (int product){

		int temp = 0;
		temp = quantity_ + product;
		return quantity_;
		
	}
;
	int Product::operator -= (int quantity){

		int temp = 0;
		temp = quantity_ + quantity;
		return quantity_;

	}

	double operator += (double& cost, const Product& p){

		double temp = 0;
		temp = p.quantity() * p.cost();
		return temp;

	}

	std::ostream& operator<<(std::ostream& os, const Product& b){

		return b.write(os, true);

	}

	std::istream& operator>>(std::istream& is, Product& b){

		return b.read(is);

	}

}