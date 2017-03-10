#ifndef SICT__STREAMABLE_H_
#define SICT__STREAMABLE_H_
#include <iostream>
#include <fstream>
namespace sict{
	class Streamable{

	public:

		virtual std::fstream& store(std::fstream&, bool addNewLine = true)const;
		virtual std::fstream& load(std::fstream& file);
		virtual std::ostream& write(std::ostream& os, bool linear);
		virtual std::istream& read(std::istream& is);



	};
}
#endif