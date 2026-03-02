#include <iostream>
#include "table.h"

const std::string Table::DEF_NAME = "Nazwa Bazowa";
const int Table::DEF_SIZE = 10;

Table::Table() {
	
	tableName = DEF_NAME;
	tableSize = DEF_SIZE;
	pTable = new int[tableSize];

	std::cout << "bezp: '" << tableName << "'\n";
}

Table::Table(std::string tName, int tSize) {
	
	tableName = tName;
	tableSize = (tSize > 0) ? tSize : DEF_SIZE;

	pTable = new int[tableSize];

	std::cout << "parametr: '" << tableName << "'\n";
}

Table::Table(Table &pOtherTable) {

	tableName = pOtherTable.tableName + "_copy";
	tableSize = pOtherTable.tableSize;

	pTable = new int[tableSize];

	for (int i = 0; i < tableSize; i++) {
		pTable[i] = pOtherTable.pTable[i];
	}

	std::cout << "kopiuj: '" << tableName << "'\n";
}

Table::~Table() {

	std::cout << "usuwam: '" << tableName << "'\n";
	delete[] pTable;
}

void Table::setName(std::string newName) {
	
	tableName = newName;
}

bool Table::setNewSize(int newSize) {
	
	//w przypadku newSize jest mnieszy ni¿ tableSize ucinaæ czy nie pozwalaæ zmieniæ
	if (newSize <= 0) return false;

	int* pNewTable = new int[newSize];

	for (int i = 0; i < std::min(tableSize, newSize); i++) {
		pNewTable[i] = pTable[i];
	}

	delete[] pTable;

	pTable = pNewTable;
	tableSize = newSize;
	return true;
}//Tu siê usuwa pNewTable

int Table::getSize() {
	return tableSize;
}


Table* Table::pTableClone() {
	return new Table(*this);
}// zwroc nowy obiekt uzywajac konstruktora ktory kopiuje dana tablice (*this) przekaz adres obiektu (by uzyc okstruktora kopujacego) na ktorym zostala wykonana operacja kopiowania