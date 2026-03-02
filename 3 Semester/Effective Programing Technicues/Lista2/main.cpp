
#include <iostream>
#include "number.h"
#include <exception>
// DZIWNA SPRAWA PRZY TESTOWANIU, JEST I TAK OGRANICZENIE DO WIELKOSCI INTA CZY MAMY ROBIC TAK BY PRZEKAZAC STRINGA I POTEM GO ZAMIENIC NA INTA W TABLICY
// SMIESZNIE BO GDY LICZBA > MAX INT TO JEDZIE DALEJ OD MIN INT = -2147483647 I GO ZWIEKSZA TYLE ILE JEST WIEKSZA LICZBA 2x MAX INT + 2 DAJE 0 ( +1 za przejscie do min inta, +1 za 0)
int main()
{
    //Number num1, num2, num3, num4, num5;
    //num1 = 2147483647;
    //num2 = 2147483647;
    //num3 = num1 * 2;
    //num4 = (2147483647 * 2);
    //num5 = num1 * num2;
    //std::cout << num1.toStr() << '\n';
    //std::cout << num2.toStr() << '\n';
    //std::cout << num3.toStr() << '\n';
    //std::cout << num4.toStr() << '\n';
    //std::cout << num5.toStr() << "\n\n\n\n";

    //Number test = 2; // Dlaczego to przyjmuje jakby parametr dla kostruktora
    //std::cout << test.toStr() << '\n';
    //test = 2; //A to juz wartosc
    //std::cout << test.toStr() << "\n\n\n\n";

    //Number zero;

    //zero = 0;
    //std::cout << zero.toStr() << '\n';

    //std::cout << "ZERO == 0 -> " << (zero==0) << "\n\n\n\n";
    /*try {
        Number test(-2);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what();
    }*/

    Number a(10), b(16);
    a = 26;
    b = 10;
    std::cout << "a -> " << a.toStr() << "\n";
    std::cout << "b -> " << b.toStr() << "\n";
    std::cout << "b < a -> " << (b < a) << "\n";
    std::cout << "a + b -> " << (a + b).toStr() << "\n";
    std::cout << "a - b -> " << (a - b).toStr() << "\n";
    std::cout << "a * b -> " << (a * b).toStr() << "\n";
    std::cout << "b -> " << b.toStr() << "\n";
    Number c;

    c = a = b = 16;
    c = a + b;
    std::cout << "a -> " << a.toStr() << "\n";
    std::cout << "b -> " << b.toStr() << "\n";
    std::cout << "c -> " << c.toStr() << "\n";
    Number test(10);
    test = Number::addAbs(a, b);
    std::cout << "test = addAbs(a,b) -> " << test.toStr() << "\n";
    test = 0;
    std::cout << "proba dzielenia przez 0 -> ";
    try {
        std::cout << (a / test).toStr() << "\n";
    }
    catch (std::runtime_error e) {
        std::cout << e.what() << "\n";
    }
}

