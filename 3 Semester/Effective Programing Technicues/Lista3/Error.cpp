#include "Error.h"

Error::Error()
{
	clear();
}

void Error::setError(eErrorCode code, std::string message)
{
	hasEror = true;
	erorCode = code;
	errorMessage = message;
}

void Error::clear()
{
	hasEror = false;
	errorMessage = "";
	erorCode = NONE;
}

bool Error::hasError() const
{
	return hasEror;
}

std::string Error::getMessage() const
{
	return errorMessage;
}

Error::eErrorCode Error::getCode() const
{
	return erorCode;
}