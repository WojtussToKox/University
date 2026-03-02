#include "number.h"
#include <string>
#include <exception>
#include <stdexcept>

//ZAPYTAC O WYCIEKI PAMIECI CZY ICH CZASAMI NIE MA W TEORII NIE BO SIE TWORZY NA STOSIE ZAWSZE I USUWAJA SIE WRAZ Z WYJSCIEM Z FUNKCJI ALE NIE DO KONCA TO ROZUMIEM


const int Number::DEF_NUMBER_LENGTH = 10;
const int Number::DEF_BASE = 10;

void Number::validateAndSetBaseSystem(int base)
{
	if (base < 2 || base > 16) {
		errorInBaseInput = true;
		baseNumberSystem = DEF_BASE;
	}
	else {
		errorInBaseInput = false;
		baseNumberSystem = base;
	}
}


Number::Number() {
	numberLength = DEF_NUMBER_LENGTH;
	pNumberArr = new int[numberLength];
	isNegative = false;
	errorInBaseInput = false;
	baseNumberSystem = DEF_BASE;

	for (int i = 0; i < numberLength; i++) {
		pNumberArr[i] = 0;
	}
}

Number::Number(int base, int setNumberLength) {
	validateAndSetBaseSystem(base);
	numberLength = setNumberLength;
	pNumberArr = new int[numberLength];
	isNegative = false;

	for (int i = 0; i < numberLength; i++) {
		pNumberArr[i] = 0;
	}
}

Number::Number(int base){
	validateAndSetBaseSystem(base);
	numberLength = DEF_NUMBER_LENGTH;
	pNumberArr = new int[numberLength];
	isNegative = false;

	for (int i = 0; i < numberLength; i++) {
		pNumberArr[i] = 0;
	}
}

Number::Number(const Number& pOther) {
	numberLength = pOther.numberLength;
	isNegative = pOther.isNegative;
	pNumberArr = new int[numberLength];
	baseNumberSystem = pOther.baseNumberSystem;
	errorInBaseInput = pOther.errorInBaseInput;

	for (int i = 0; i < numberLength; i++) {
		pNumberArr[i] = pOther.pNumberArr[i];
	}
}

Number::~Number() {
	delete[] pNumberArr;
}



//void Number::operator=(const Number& pOtherNum)
//Problemy tego kodu:
//Wyciek pamiêci oryginalny wskaznik na pNumberArr nigdy nie jest usuwany (Tracony)
//num1 i num2 dziel¹ t¹ sam¹ pamiêæ dynamiczna pod wstaznikiem pOtherNum
//obiekty num1 i num2 gdy sa usuwane pod koniec dzialania programu usuwamy dwa razy ten sam wskaznik - mega lipa blad krytyczny
//Usuniecie naszego destruktora rozwiazuje ten problem pochopnie, gdyz nie jest ju¿ problem u usunieciu drugi raz wskaznika, lecz teraz mamy 2 wycieki pamieci
//void Number::operator=(const Number& pOtherNum)
//{
//	pNumberArr = pOtherNum.pNumberArr;
//	numberLength = pOtherNum.numberLength;
//}

Number& Number::operator=(const Number& pOtherNum) {
	if (this == &pOtherNum) {
		return *this;                //num1 = num1
	}
	numberLength = pOtherNum.numberLength;
	isNegative = pOtherNum.isNegative;
	int* pNewNumberArr = new int[numberLength];
	baseNumberSystem = pOtherNum.baseNumberSystem;

	for (int i = 0; i < numberLength; i++) {
		pNewNumberArr[i] = pOtherNum.pNumberArr[i];
	}
	delete[] pNumberArr;

	pNumberArr = pNewNumberArr;
	adjustNumberLength();
	return *this;
}

Number& Number::operator=(const int value) {
	delete[] pNumberArr;
	numberLength = 0;

	int tempValue;
	if (value < 0) {
		isNegative = true;
		tempValue = std::abs(value);
	}
	else {
		isNegative = false;
		tempValue = value;
	}

	int temp = tempValue;

	do {
		numberLength++;
		temp /= baseNumberSystem;
	} while (temp > 0);

	pNumberArr = new int[numberLength];

	for (int i = 0; i < numberLength; i++) {
		pNumberArr[i] = tempValue % baseNumberSystem;
		tempValue /= baseNumberSystem;
	}

	return *this;
}



std::string Number::toStr() {
	std::string result = "";

	char hex_chars[] = "0123456789ABCDEF";

	for (int i = numberLength - 1; i >= 0; i--) {
		result += hex_chars[pNumberArr[i]];
	}
	if (isNegative) {
		// Wstawiamy znak '-' na pocz¹tku stringa
		result.insert(0, 1, '-');
	}

	return result;
}

Number Number::convertToBase(int newBase) const
{
	Number result(newBase);
	

	long long decimalValue = 0;
	long long power = 1;

	for (int i = 0; i < numberLength; ++i) {
		decimalValue += pNumberArr[i] * power;
		power *= baseNumberSystem;
	}

	if (isNegative) {
		decimalValue = -decimalValue;
	}

	result = decimalValue;

	return result;
}



void Number::adjustNumberLength() {
	int newLength = numberLength;

	while (newLength > 1 && pNumberArr[newLength - 1] == 0) {
		newLength--;
	}

	if (newLength < numberLength) {
		int* pNewArr = new int[newLength];
		for (int i = 0; i < newLength; i++) {
			pNewArr[i] = pNumberArr[i];
		}
		delete[] pNumberArr;
		pNumberArr = pNewArr;
		numberLength = newLength;
	}

	// Jeœli liczba jest 0, upewniamy siê, ¿e nie jest oznaczona jako ujemna
	if (numberLength == 1 && pNumberArr[0] == 0) {
		isNegative = false;
	}
}



int Number::compareAbs(const Number& a, const Number& b) {
	if (a.numberLength != b.numberLength)
		return (a.numberLength > b.numberLength) ? 1 : -1;
	for (int i = a.numberLength - 1; i >= 0; --i) {
		if (a.pNumberArr[i] != b.pNumberArr[i])
			return (a.pNumberArr[i] > b.pNumberArr[i]) ? 1 : -1;
	}
	return 0;
}

Number Number::addAbs(const Number& a, const Number& b) {


	Number copyB = b;
	if (a.baseNumberSystem != copyB.baseNumberSystem) {
		copyB = b.convertToBase(a.baseNumberSystem);
	}

	int maxLen = std::max(a.numberLength, copyB.numberLength) + 1;

	Number result(a.baseNumberSystem, maxLen);


	int carry = 0;
	for (int i = 0; i < result.numberLength; i++) {
		int sum = carry;
		if (i < a.numberLength) sum += a.pNumberArr[i];
		if (i < copyB.numberLength) sum += copyB.pNumberArr[i];
		result.pNumberArr[i] = sum % result.baseNumberSystem;
		carry = sum / result.baseNumberSystem;
	}

	result.adjustNumberLength();
	return result;
}
// zakladamy ze przekazemy a >= b
Number Number::subAbs(const Number& bigger, const Number& lesser)
{	
	Number copyLesser = lesser;
	if (bigger.baseNumberSystem != copyLesser.baseNumberSystem) {
		copyLesser = lesser.convertToBase(bigger.baseNumberSystem);
	}


	Number tempBigger = bigger; // Tworzymy modyfikowalna kopie a
	Number result(bigger.baseNumberSystem, bigger.numberLength);

	for (int i = 0; i < tempBigger.numberLength; i++) {
		int diff = tempBigger.pNumberArr[i] - (i < copyLesser.numberLength ? copyLesser.pNumberArr[i] : 0);
		if (diff < 0) {
			diff += result.baseNumberSystem;
			tempBigger.pNumberArr[i + 1] -= 1; // Modyfikujemy kopie bo przekazalismy const a
		}
		result.pNumberArr[i] = diff;
	}	

	result.adjustNumberLength();
	return result;
}

Number Number::operator-() const {
	Number result = *this; // U¿ywa konstruktora kopiuj¹cego
	if (result.numberLength != 1 || result.pNumberArr[0] != 0) { // Nie negujemy 0
		result.isNegative = !result.isNegative;
	}
	return result;
}

bool Number::operator==(const Number& pOtherNumber) {
	if (baseNumberSystem != pOtherNumber.baseNumberSystem) {
		return (*this == pOtherNumber.convertToBase(baseNumberSystem));
	}
	if (isNegative != pOtherNumber.isNegative || numberLength != pOtherNumber.numberLength) {
		return false;
	}
	for (int i = 0; i < numberLength; ++i) {
		if (pNumberArr[i] != pOtherNumber.pNumberArr[i]) {
			return false;
		}
	}
	return true;
}

bool Number::operator==(int value) {
	Number temp(baseNumberSystem);       
	temp = value;      
	return *this == temp; 
}

bool Number::operator<(const Number& pOtherNumber)
{
	if (baseNumberSystem != pOtherNumber.baseNumberSystem) {
		return (*this < pOtherNumber.convertToBase(baseNumberSystem));
	}

	//rozne znaki
	if (isNegative != pOtherNumber.isNegative) {
		return isNegative;
	}
	
	//rozne dlugosci
	if (numberLength != pOtherNumber.numberLength) {
		if (!isNegative) { // Obie dodatnie
			return numberLength < pOtherNumber.numberLength;
		}
		else { // Obie ujemne
			// -10 (<) -5. D³u¿sza jest mniejsza.
			return !(numberLength < pOtherNumber.numberLength);
		}
	}

	//rozne liczby
	for (int i = numberLength - 1; i >= 0; i--) {
		if (pNumberArr[i] != pOtherNumber.pNumberArr[i]) {
			if (!isNegative) { // Obie dodatnie
				return pNumberArr[i] < pOtherNumber.pNumberArr[i];
			}
			else { // Obie ujemne
				// -15 (<) -12. Mniejsza cyfra oznacza wiêksz¹ liczbê.
				return pNumberArr[i] > pOtherNumber.pNumberArr[i];
			}
		}
	}
	//jesli nic nie rozni to rowne
	return false;
}

Number Number::operator+(const Number& pOtherNumber) const
{
	Number right = pOtherNumber;
	if (baseNumberSystem != pOtherNumber.baseNumberSystem) {
		right = pOtherNumber.convertToBase(baseNumberSystem);
	}

	Number result(baseNumberSystem);
	// Znak ten sam czyli dodac wartosci bezwzgl i znak wspolny
	if (isNegative == right.isNegative) {
		result = addAbs(*this, right);
		result.isNegative = isNegative;
	} else { // rozne znaki odejmij wieksza - mniejsza pod wzgledem wart BezWzgl i znak tej wiekszej
		int compare = compareAbs(*this, right);
		if (compare == 0) {
			result = 0;
		} else if (compare > 0) {
			result = subAbs(*this, right);
			result.isNegative = isNegative;
		} else {
			result = subAbs(right, *this);
			result.isNegative = right.isNegative;
		}
	}
	result.adjustNumberLength();
	return result;
}

Number Number::operator-(const Number& pOtherNumber) const
{
	//Tutaj nie trzeba sprawdzac bo wykorzystujemy operator + ktory sprawdza
	// A - B -> A + (-B) 
	return *this + (-pOtherNumber);
}

Number Number::operator*(const Number& pOtherNumber) const
{
	Number right = pOtherNumber;
	if (baseNumberSystem != pOtherNumber.baseNumberSystem) {
		right = pOtherNumber.convertToBase(baseNumberSystem);
	}

	int maxLength = numberLength + right.numberLength;
	Number result(baseNumberSystem, maxLength);
	
	result.isNegative = (isNegative != right.isNegative);

	// Czy warto uwzglednic ze X * 0 = 0 bo teraz i tak przechodzi

	// Mno¿enie pisemne
	for (int i = 0; i < numberLength; ++i) {
		int carry = 0;
		for (int j = 0; j < right.numberLength; ++j) {
			// Suma: obecna cyfra + iloczyn cyfr + przeniesienie z poprzedniego kroku
			int sum = result.pNumberArr[i + j] + (pNumberArr[i] * right.pNumberArr[j]) + carry;

			result.pNumberArr[i + j] = sum % baseNumberSystem; // Aktualna cyfra
			carry = sum / baseNumberSystem;                    // Nowe przeniesienie
		}
		// Dodajemy ostatnie przeniesienie na kolejnej pozycji
		result.pNumberArr[i + right.numberLength] += carry;
	}


	result.adjustNumberLength();
	return result;
}

Number Number::operator*(int value) const
{
	Number multiplier(baseNumberSystem);
	multiplier = value;
	return *this * multiplier;
}


Number Number::operator/(const Number& pOtherNumber) const
{
	Number divisor = pOtherNumber;
	if (baseNumberSystem != divisor.baseNumberSystem) {
		divisor = divisor.convertToBase(baseNumberSystem);
	}

	// Sprawdzenie dzielenia przez zero
	Number zero(baseNumberSystem);
	zero = 0;
	if (divisor == zero) {
		throw std::runtime_error("Division by zero");
	}

	// Przygotowanie wartoœci bezwzglêdnych
	Number dividend = *this;
	dividend.isNegative = false;
	divisor.isNegative = false;

	// Wynik i reszta
	Number result(baseNumberSystem, numberLength);
	Number remainder(baseNumberSystem);
	remainder = 0;

	if (compareAbs(dividend, divisor) < 0) {
		result = 0;
		return result;
	}


	for (int i = numberLength - 1; i >= 0; --i) {
		int* newArr = new int[remainder.numberLength + 1];
		for (int k = remainder.numberLength - 1; k >= 0; --k) {
			newArr[k + 1] = remainder.pNumberArr[k];
		}
		delete[] remainder.pNumberArr;
		remainder.pNumberArr = newArr;
		remainder.numberLength += 1;

		// Wstawiamy now¹ cyfrê z dzielnej na pocz¹tek
		remainder.pNumberArr[0] = pNumberArr[i];
		remainder.adjustNumberLength();

		int q = -1;
		Number temp;
		do {
			q++;
			temp = divisor * (q + 1);
		} while (compareAbs(temp, remainder) <= 0);

		result.pNumberArr[i] = q;
		remainder = remainder - (divisor * q);
	}

	result.isNegative = (isNegative != pOtherNumber.isNegative);
	result.adjustNumberLength();
	return result;
}
