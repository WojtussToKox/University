#pragma once

#include <vector>
#include <string>
#include <stdexcept>

#include "..\Pointer\MyUniquePtr.h"
#include "..\Error\Error.h"

template <typename T, typename E>
class Result {
private:
    
    MyUniquePtr<T> value;
    std::vector<MyUniquePtr<E>> vErrors;
    bool success;


    // Konstruktor prywatny - przejmuje w³asnoœæ wskaŸników (move)
    Result(bool isSuccess, MyUniquePtr<T> val, std::vector<MyUniquePtr<E>>&& errors)
        : success(isSuccess), value(std::move(val)), vErrors(std::move(errors)) {
    }

public:
    static Result<T, E> Success(T* pValue);
    static Result<T, E> Failure(E* error);
    static Result<T, E> Failure(std::vector<MyUniquePtr<E>>&& errors);

    bool isSuccess() const { return success; }
    bool isFailure() const { return !success; }

    // Zwraca obiekt b³êdu zamiast samego stringa
    const Error& getErrorMessages() const;


    const std::vector<MyUniquePtr<E>>& getErrorsVector() const { return vErrors; }

    // Pobranie wartoœci
    T& getValue() const;

    // Dostêp przez strza³kê
    T* operator->() const { return value.get(); }
    T& operator*() const { return *value; }

    operator bool() const { return success; }
};


template<typename T, typename E>
inline Result<T, E> Result<T, E>::Success(T* pValue)
{
    std::vector<MyUniquePtr<E>> emptyErrors;
    return Result(true, MyUniquePtr<T>(pValue), std::move(emptyErrors));
}

template<typename T, typename E>
inline Result<T, E> Result<T, E>::Failure(E* error)
{
    std::vector<MyUniquePtr<E>> errs;
    errs.push_back(MyUniquePtr<E>(error));
    return Result(false, MyUniquePtr<T>(nullptr), std::move(errs));
}

template<typename T, typename E>
inline Result<T, E> Result<T, E>::Failure(std::vector<MyUniquePtr<E>>&& errors)
{
    return Result(false, MyUniquePtr<T>(nullptr), std::move(errors));
}

template<typename T, typename E>
inline const Error& Result<T, E>::getErrorMessages() const
{
    std::string fullMsg;
    for (const auto& ptr : vErrors) {
        if (ptr.get()) fullMsg += ptr->toString() + "\n";
    }
    return fullMsg;
}

// Zak³adamy ¿e u¿ytkownik sprawdzi isSuccess
template<typename T, typename E>
inline T& Result<T, E>::getValue() const
{
    return *value;
}





// Specjalizacja Result dla typu void (brak zwracanej wartoœci)
template <typename E>
class Result<void, E> {
private:

    std::vector<MyUniquePtr<E>> vErrors;
    bool success;

    // Konstruktor prywatny
    Result(bool isSuccess, std::vector<MyUniquePtr<E>>&& errors)
        : success(isSuccess), vErrors(std::move(errors)) {
    }

public:
    static Result<void, E> Success();

    static Result<void, E> Failure(E* error);
    static Result<void, E> Failure(std::vector<MyUniquePtr<E>>&& errors);

    bool isSuccess() const { return success; }
    bool isFailure() const { return !success; }

    std::string getErrorMessage() const;

    const std::vector<MyUniquePtr<E>>& getErrorsVector() const { return vErrors; }

    operator bool() const { return success; }
};

// --- IMPLEMENTACJE METOD ---

template<typename E>
inline Result<void, E> Result<void, E>::Success()
{
    std::vector<MyUniquePtr<E>> emptyErrors;
    return Result(true, std::move(emptyErrors));
}

template<typename E>
inline Result<void, E> Result<void, E>::Failure(E* error)
{
    std::vector<MyUniquePtr<E>> errs;
    // Pakujemy surowy wskaŸnik w MyUniquePtr
    errs.push_back(MyUniquePtr<E>(error));
    return Result(false, std::move(errs));
}

template<typename E>
inline Result<void, E> Result<void, E>::Failure(std::vector<MyUniquePtr<E>>&& errors)
{
    return Result(false, std::move(errors));
}

template<typename E>
inline std::string Result<void, E>::getErrorMessage() const
{
    std::string fullMsg;
    for (const auto& ptr : vErrors) {
        // Zak³adamy, ¿e klasa E (Error) ma metodê toString()
        if (ptr.get()) fullMsg += ptr->toString() + "\n";
    }
    return fullMsg;
}