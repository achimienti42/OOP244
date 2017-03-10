#include "ErrorMessage.h"
#include <cstring>
namespace sict{

	ErrorMessage::ErrorMessage(){

		char *message_ = nullptr;

	}

	ErrorMessage::ErrorMessage(const char* errorMessage){

		char* message_ = nullptr;
		message(errorMessage);

	}

	ErrorMessage& operator=(const char* errorMessage){

		delete[] = message_;
		message_ = new char[strlen(errorMessage) + 1];
		message_ = errorMessage;
		return *this;

	}




}