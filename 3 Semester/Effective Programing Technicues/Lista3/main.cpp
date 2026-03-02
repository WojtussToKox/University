//Inicjalizacja pustego wektora
//pRoot = NULL


#include <iostream>
#include "Interface.h"


int main()
{
    AlgebraicTree first, second, result;

    first.buildTreeFromFormula("+ a b");
    second.buildTreeFromFormula("* 2 1");

    result = first + second;

    std::cout << first.toStringTree() << "\n\n";
    std::cout << second.toStringTree() << "\n\n";
    std::cout << result.toStringTree() << "\n\n";

    result = second + first;
    std::cout << result.toStringTree() << "\n\n";

    Interface interface;
    interface.run(); 
    return 0;
}
