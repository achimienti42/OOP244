#ifndef SICT_PRODUCT_H_
#define SICT_PRODUCT_H_
#include "general.h"

namespace sict{

	class Product : Streamable{
		
	private:
		char sku_[MAX_SKU_LEN + 1];
		char *name_;
		double price_;
		bool taxed_;
		int quantity_;
		int qtyNeeded_;

	public:
		Product();
		Product(const char *sku, const char *name, int quantity = 0, double price = 0, bool tax = true);
		void Copy(const Product& P);
		Product& operator=(const Product& P);
		virtual ~Product();

		void sku(char* sku);
		void price(double price);
		void name(char* name);
		void taxed(bool taxed);
		void quantity(int quantity);
		void qtyNeeded(int qtyNeeded);

		const char *sku()const;
		double price()const;
		const char *name()const;
		bool taxed()const;
		int quantity()const;
		int qtyNeeded()const;
		double cost()const;

		bool isEmpty()const;

		bool operator == (char *sku);
		int operator += (int product);
		int operator -= (int quantity);

		
	};

	std::ostream& operator<<(std::ostream& os, const Product& b);
	std::istream& operator>>(std::istream& is, Product &b);

	double operator += (double& cost, const Product& p);
}
#endif