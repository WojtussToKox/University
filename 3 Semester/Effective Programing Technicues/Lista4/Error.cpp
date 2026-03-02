#include "Error.h"

Error::Error()
{
	errorMessage = "";
}

Error::Error(const std::string& errorMess)
{
	errorMessage = errorMess;
}

Error::Error(const Error& otherError)
{
	errorMessage = otherError.errorMessage;
}

Error::~Error()
{
}

std::string Error::getErrorMessage() const
{
	return errorMessage;
}

void Error::setErrorMessage(const std::string& newErrorMess)
{
	errorMessage = newErrorMess;
}
