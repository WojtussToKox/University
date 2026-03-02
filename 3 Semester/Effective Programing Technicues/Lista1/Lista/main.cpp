
/* PYTANIA
    1. Alokacja statyczna jest wtedy, gdy wpiszemy dwie deklaracje po sobie bez definicji, do czego ten wskaznik pokazuje
        A dynamiczna, jezeli przy tworzeniu od razu pokazujemy na co ma patrzec???

    2. Czy przy Dealokowaniu potrzebny jset delete[] pDTable[i]; zamiast delete pDTable[i]

    3.
*/

#include <iostream>
#include "functions.h"
#include "table.h"



int main()
{

    std::cout << "ZADANIE 1 \n";

    dynamicAllocTableWithFillWith34(10);

    dynamicAllocTableWithFillWith34(0);

    dynamicAllocTableWithFillWith34(-1);



    std::cout << "\n\n\n\nZADANIE 2 i 3 RAZEM \n";
    int** pDoubleTable;

    //opcja dla int**&
    std::cout << allocTableTwoDimensional(pDoubleTable, -2, 3) << "\n";
    std::cout << deAllocTableTwoDimensional(pDoubleTable, -2, 3) << "\n";

    //opcja dla int***
    std::cout << allocTableTwoDimensional(&pDoubleTable, 2, 3) << "\n";
    std::cout << deAllocTableTwoDimensional(&pDoubleTable, 2, 3) << "\n";


    std::cout << "\n\n\n\nZADANIE 4 \n";

    Table table;
    Table tableParam("Tablica z Parametrem", 20);
    Table tableCopy(table);

    table.setName("Moja Tablica");
    std::cout << table.setNewSize(-2) << "\n";
    std::cout << table.setNewSize(6) << "\n";


    std::cout << "\n\n\n";
    Table tab1("TablicaWskaznik", 5);
    Table tab2("TablicaWartosc", 5);

    std::cout << "\n\n\n";
    // przez wskaznik
    vModTab(&tab1, 10);
    std::cout << tab1.getSize()<< "\n";
    std::cout << "\n";

    // przez wartosc
    vModTab(tab2, 10);
    std::cout << tab2.getSize() << "\n";
    std::cout << "\n\n\n";


    Table* pTableClone = table.pTableClone();
    
    delete pTableClone; //musimy usunac tablice gdyz zostala utworzona dynamicznie

    return 0;
}//c++ automatycznie wywo³a destruktory obiektow utworzonych statycznie

