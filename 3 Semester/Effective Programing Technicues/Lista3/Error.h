#pragma once
#include <string>
class Error
{
public:
	enum eErrorCode {
		NONE = 0,
		EMPTY_TREE,
		INVALID_ARGS,
		COMPUTATION_ERROR
	};

private:
	bool hasEror;
	std::string errorMessage;
	eErrorCode erorCode;

public:
	
	Error();

	
	void setError(eErrorCode code, std::string message);
	void clear();

	
	bool hasError() const;
	std::string getMessage() const;
	eErrorCode getCode() const;
};
