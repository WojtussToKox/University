#pragma once
#include <string>

class Error
{
public:
	Error();
	Error(const std::string& errorMess);
	Error(const Error& otherError);

	virtual ~Error();
		
	std::string getErrorMessage() const;
	void setErrorMessage(const std::string& newErrorMess);

private:
	std::string errorMessage;
};

