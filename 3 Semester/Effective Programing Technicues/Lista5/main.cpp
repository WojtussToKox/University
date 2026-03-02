

#include <iostream>
#include "Interface.h"


int main()
{
    AlgebraicTree tree1, tree2, tree3, tree4, result;
    tree1.buildTreeFromFormula("+ + a a a");
    tree2.buildTreeFromFormula("+ + b b b");
    tree3.buildTreeFromFormula("+ + c c c");
    tree4.buildTreeFromFormula("+ + d d d");

    // Bez move semantics
    // Operator + tworzy temp tree N kopii ----- Dodawanie bez kopii  ----- return newTree N kopii  ----- Przypisanie do nowego kolejne N kopii
    // 
    // 
    // Z move semantics
    // Operator + tworzy temp tree N kopii ----- Dodawanie bez kopii  ----- return newTree - operator przeniesiena  ----- Przeniesienie bez dodatkowych kopii
    // 

    std::cout << "--- TEST: przypisanie ---\n";
    std::cout << "-------------------------\n";

    tree4 = tree3;
    std::cout << "\n" << tree4.toStringTree() << "\n";
    std::cout << tree3.toStringTree() << "\n";
    std::cout << "\n";


    std::cout << "--- TEST: std::move ---\n";
    std::cout << "------------------------\n";
    
    tree4 = std::move(tree3);
    std::cout << "\n" << tree4.toStringTree() << "\n";
    std::cout << tree3.toStringTree() << "\n";
    std::cout << "\n\n";



    std::cout << "=== TEST: Normalne dodawanie z Move Semantics ===\n";
    std::cout << "---------------------------------------------------\n";
    // Jedno Copy poniewarz tworzymy obiekt new Tree przy operatorze +
    result = tree1 + tree2;
    std::cout << "\n\n";



    std::cout << "=== TEST: Proba dodania bez Move Semantics ===\n";
    std::cout << "----------------------------------\n";
    // Wynik (tree1 + tree2) jest obiektem tymczasowym (R-value).
    // Normalnie uzylibysmy operator=(AlgebraicTree&&).
    // Ale rzutujemy go na (const AlgebraicTree&), wiec kompilator MUSI uzyc operator=(const AlgebraicTree&).
    // Tego Move Op nie da się ominąć bo + zwraca wartość
    result = static_cast<const AlgebraicTree&>(tree1 + tree2);
    std::cout << "\n\n";


    return 0;
}


// Czy mozna przechowywac wskaznik bardziej ogolny (np. void*)?
// Mozna uzyc void*, ale to niebezpieczne.
// Zalety: Wskaznik jest uniwersalny, moze wskazywac na dowolny typ.
// Wady: 'delete' na void* nie wywola destruktora obiektu, wiec jesli obiekt
// mial w srodku dynamiczna pamiec, to bedzie wyciek. Nie dzialaja tez operatory -> i *.

// Co sie stanie, gdy inteligentny wskaznik dostanie adres pamieci statycznej?
// Program sie wysypie (crash / undefined behavior).
// Wyjasnienie: Inteligentny wskaznik w destruktorze robi 'delete'.
// Instrukcji 'delete' mozna uzywac tylko na pamieci ze sterty (new), a nie ze stosu.
