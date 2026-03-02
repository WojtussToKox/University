#include "Error.h"
#include <string> 

Error::Error()
    : code(Code::OK), errorMessage("")
{
}

Error::Error(Code code, const std::string& message)
    : code(code), errorMessage(message)
{
}

Error::~Error() = default;

Error::Code Error::getCode() const {
    return code;
}

std::string Error::getMessage() const {
    return errorMessage;
}

std::string Error::toString() const {
    return "[Error " + std::to_string((int)code) + "] " + errorMessage;
}