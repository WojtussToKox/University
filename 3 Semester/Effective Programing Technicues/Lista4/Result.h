#pragma once
#include <vector>

template <typename T, typename E>
class Result
{
public:
	Result();
	Result(const T& value);
	Result(E* pError);
	Result(std::vector<E*>& vNewErrors);
	Result(const Result<T, E>& otherResult);

	~Result();

	static Result<T, E> ok(const T& value);
	static Result<T, E> fail(E* pError);
	static Result<T, E> fail(std::vector<E*>& vNewErrors);

	Result<T, E>& operator=(const Result<T, E>& otherResult);

	bool isSuccess();

	T getValue();

	std::vector<E*>& getErrors();

private:
	T* pValue;
	std::vector<E*> vErrors;
};

template<typename T, typename E>
inline Result<T, E>::Result()
{
	pValue = NULL;
}

template<typename T, typename E>
inline Result<T, E>::Result(const T& value)
{
	pValue = new T(value);
}

template<typename T, typename E>
inline Result<T, E>::Result(E* pError)
{
	pValue = NULL;
	vErrors.push_back(pError);
}

template<typename T, typename E>
inline Result<T, E>::Result(std::vector<E*>& vNewErrors)
{
	pValue = NULL;
	for (int i = 0; i < vNewErrors.size(); i++) {
		vErrors.push_back(new E(*vNewErrors[i]));
	}
}

template<typename T, typename E>
inline Result<T, E>::Result(const Result<T, E>& otherResult)
{
	if (otherResult.pValue != NULL) {
		pValue = new T(*otherResult.pValue);
	}
	else {
		pValue = NULL;
	}

	for (int i = 0; i < otherResult.vErrors.size(); i++) {
		vErrors.push_back(new E(*otherResult.vErrors[i]));
	}
}

template<typename T, typename E>
inline Result<T, E>::~Result()
{
	if (pValue != NULL) {
		delete pValue;
	}
	for (int i = 0; i < vErrors.size(); i++) {
		delete vErrors[i];
	}
	vErrors.clear();
}

template<typename T, typename E>
inline Result<T, E> Result<T, E>::ok(const T& value)
{
	return Result<T, E>(value);
}




template<typename T, typename E>
inline Result<T, E> Result<T, E>::fail(E* pError)
{
	return Result<T, E>(pError);
}

template<typename T, typename E>
inline Result<T, E> Result<T, E>::fail(std::vector<E*>& vNewErrors)
{
	return Result<T, E>(vNewErrors);
}

template<typename T, typename E>
inline Result<T, E>& Result<T, E>::operator=(const Result<T, E>& otherResult)
{
	if (this == &otherResult) {
		return *this;
	}

	if (pValue != NULL) {
		delete pValue;
		pValue = NULL;
	}
	for (int i = 0; i < vErrors.size(); i++) {
		delete vErrors[i];
	}
	vErrors.clear();

	if (otherResult.pValue != NULL) {
		pValue = new T(*otherResult.pValue);
	}

	for (size_t i = 0; i < otherResult.vErrors.size(); i++) {
		vErrors.push_back(new E(*otherResult.vErrors[i]));
	}

	return *this;

}

template<typename T, typename E>
inline bool Result<T, E>::isSuccess()
{
	return vErrors.empty();
}

template<typename T, typename E>
inline T Result<T, E>::getValue()
{
	//Zakladamy ¿e u¿ytkownik sprawdzil isSucces
	return *pValue;
}

template<typename T, typename E>
inline std::vector<E*>& Result<T, E>::getErrors()
{
	return vErrors;
}









template <typename E>
class Result<void, E>
{
public:
	Result();
	Result(E* pError);
	Result(std::vector<E*>& vNewErrors);
	Result(const Result<void, E>& otherResult);
	~Result();

	static Result<void, E> ok();
	static Result<void, E> fail(E* pError);
	static Result<void, E> fail(std::vector<E*>& vNewErrors);

	Result<void, E>& operator=(const Result<void, E>& otherResult);

	bool isSuccess();
	std::vector<E*>& getErrors();

private:
	std::vector<E*> vErrors;
};


template <typename E>
inline Result<void, E>::Result()
{
}

template <typename E>
inline Result<void, E>::Result(E* pError) {
	vErrors.push_back(pError);
}

template <typename E>
inline Result<void, E>::Result(std::vector<E*>& vNewErrors)
{
	for (size_t i = 0; i < vNewErrors.size(); i++) {
		vErrors.push_back(new E(*vNewErrors[i]));
	}
}

template <typename E>
inline Result<void, E>::Result(const Result<void, E>& otherResult)
{
	for (int i = 0; i < otherResult.vErrors.size(); i++) {
		vErrors.push_back(new E(*otherResult.vErrors[i]));
	}
}

template <typename E>
inline Result<void, E>::~Result()
{
	for (int i = 0; i < vErrors.size(); i++) {
		delete vErrors[i];
	}
	vErrors.clear();
}

template<typename E>
inline Result<void, E> Result<void, E>::ok()
{
	return Result<void, E>();
}

template<typename E>
inline Result<void, E> Result<void, E>::fail(E* pError)
{
	return Result<void, E>(pError);
}

template<typename E>
inline Result<void, E> Result<void, E>::fail(std::vector<E*>& vNewErrors)
{
	return Result<void, E>(vNewErrors);
}

template<typename E>
inline Result<void, E>& Result<void, E>::operator=(const Result<void, E>& otherResult)
{
	if (this == &otherResult) {
		return *this;
	}

	for (int i = 0; i < vErrors.size(); i++) {
		delete vErrors[i];
	}
	vErrors.clear();

	for (int i = 0; i < otherResult.vErrors.size(); i++) {
		vErrors.push_back(new E(*otherResult.vErrors[i]));
	}

	return *this;
}

template<typename E>
inline bool Result<void, E>::isSuccess()
{
	return vErrors.empty();
}


template<typename E>
inline std::vector<E*>& Result<void, E>::getErrors()
{
	return vErrors;
}

