#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "Result.h"
#include "Error.h"
#include "AlgebraicTree.h" //By znac typ T = AlgerbaicTree

template<typename T, typename E>
class FileSaver {
public:
	static void saveToFile(const std::string& fileName, Result<T, E>& result);
};

template<typename T, typename E>
inline void FileSaver<T, E>::saveToFile(const std::string& fileName, Result<T, E>& result)
{
	std::ofstream textFile(fileName.c_str());
	if (!textFile.is_open()) {
		return; //Nie udalo sie otworzyc pliku
	}
	
	//result = fail wypisz bledy z result
	if (!result.isSuccess()) {
		std::vector<E*>& errors = result.getErrors();
		for (size_t i = 0; i < errors.size(); i++) {
			textFile << errors[i]->getErrorMessage() << "\n";
		}
	}

	//result = ok -> nic

	textFile.close();
}

template<typename E>
class FileSaver<AlgebraicTree*, E> {
public:
	static void saveToFile(const std::string& fileName, Result<AlgebraicTree*, E>& result);
};

template<typename E>
inline void FileSaver<AlgebraicTree*, E>::saveToFile(const std::string& fileName, Result<AlgebraicTree*, E>& result)
{
	std::ofstream textFile(fileName.c_str());
	if (!textFile.is_open()) {
		return; //Nie udalo sie otworzyc pliku
	}

	//result = fail wypisz bledy z result
	if (!result.isSuccess()) {
		std::vector<E*>& errors = result.getErrors();
		for (size_t i = 0; i < errors.size(); i++) {
			textFile << errors[i]->getErrorMessage() << "\n";
		}
	}
	else {//result = ok -> zapisz drzewo
		AlgebraicTree* tree = result.getValue();
		textFile << tree->toStringTree();
	}

	textFile.close();
}
