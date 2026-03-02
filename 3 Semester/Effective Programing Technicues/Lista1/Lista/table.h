#pragma once

#include <iostream>
#include <string>

class Table {

private:
	std::string tableName;
	int* pTable;
	int tableSize;

	static const int DEF_SIZE;
	static const std::string DEF_NAME;

public:
	//Konstruktory
	Table();
	Table(std::string name, int size);
	Table(Table& pTable);

	//Dekonstruktor (~<nazwaKlasy>)
	~Table();

	//Metody
	void setName(std::string newName);
	bool setNewSize(int newTableSize);

	int getSize();

	Table* pTableClone();

};