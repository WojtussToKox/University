#pragma once
#include <string>

class Error {
public:
    enum class Code {
        OK = 0,
        FILE_OPEN_FAILED,
        INVALID_DATA_FORMAT,
        EMPTY_FILE,
        MISSING_SECTION,
        UNKNOWN
    };

private:
    Code code;
    std::string errorMessage;

public:
    // Konstruktor domyœlny
    Error();

    // Konstruktor z parametrami
    Error(Code code, const std::string& message);

    // Destruktor wirtualny
    virtual ~Error();

    // Gettery
    Code getCode() const;
    std::string getMessage() const;

    // Metoda pomocnicza
    std::string toString() const;
};