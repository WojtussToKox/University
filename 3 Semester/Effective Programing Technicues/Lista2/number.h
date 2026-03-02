#pragma once
#include <iostream>
#include <string>


class Number {

private:
	int* pNumberArr;
	int numberLength;
	bool isNegative;
	int baseNumberSystem;
	bool errorInBaseInput;


	//Pomocnicze, static bo nie korzystaja z this
	static int compareAbs(const Number& a, const Number& b);
	void adjustNumberLength();
	void validateAndSetBaseSystem(int base);

public:

	static const int DEF_NUMBER_LENGTH;
	static const int DEF_BASE;

	Number();
	Number(int setBase, int setNumberLength);
	Number(int setBase);
	Number(const Number& pOtherNumber);
	~Number();


	Number& operator=(int value);
	
	// LE  -> void operator=(const Number& pcOther);
	//Dobrze
	Number& operator=(const Number& pcOther);


	std::string toStr();
	Number convertToBase(int newBase) const;

	

	static Number addAbs(const Number& a, const Number& b);
	static Number subAbs(const Number& a, const Number& b);
	Number operator-() const;
	bool operator==(const Number& pOtherNumber);
	bool operator==(const int value);
	bool operator<(const Number& pOtherNumber);

	Number operator+(const Number& pOtherNumber) const;
	Number operator-(const Number& pOtherNumber) const;
	Number operator*(const Number& pOtherNumber) const;
	Number operator/(const Number& pOtherNumber) const;
	Number operator*(int value) const;
};

