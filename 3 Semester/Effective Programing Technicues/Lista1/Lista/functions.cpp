
/* PYTANIA
    1. Alokacja statyczna jest wtedy, gdy wpiszemy dwie deklaracje po sobie bez definicji, do czego ten wskaznik pokazuje
        A dynamiczna, jezeli przy tworzeniu od razu pokazujemy na co ma patrzec???

    2. Czy przy Dealokowaniu potrzebny jset delete[] pDTable[i]; zamiast delete pDTable[i]

    3.
*/

#include <iostream>
#include "table.h"

// const int FILL_VALUE = 34; // W przypadku gdybyœmy chcieli mieæ inna wartosc do wpisania a nie konkretna, lecz w tym cwiczeniu nazwa funkcji wymusza na nas u¿ycie 34
void dynamicAllocTableWithFillWith34(int tableSize) {

    if (tableSize <= 0) {
        std::cout << "Error: Podano niepoprawna wielkosc tablicy (" << tableSize << "). \n";
        return;
    }

    // int *pTable = new int[tableSize];
    int* pTable;
    pTable = new int[tableSize];


    for (int i = 0; i < tableSize; i++) {
        pTable[i] = 34;
        // pTable[i] = FILL_VALUE; // Gdybysmy chcieli miec dowolna wartosc zdefiniowana wczesniej a nie konkretnie 34.
    }

    std::cout << "Utworzono tabele o rozmiarze " << tableSize << ": \n";
    for (int i = 0; i < tableSize; i++) {
        std::cout << i + 1 << ". " << pTable[i] << '\n';
    }

    delete[] pTable;
}



//po int moga byc rowniez **& gdy przekazujemy referencje do wskaznika na tablice, tak jakbysmy przekazywali oryginalny wskaznik

//po int moga byc 3* gdyz chcemy przekazac wskaznik do czegos co wskazuje na tablice 2 wymiarowa ktora w sama sobie ma 2*
//  wtedy musimy przy wywo³ywaniu funkcji uzyæ funkcja(&nazwa, int, int) tak aby funkcja otrzyma³a adres wskaznika na którym operujemy
//  trzeba wtedy pamietac ze musimy w samej funkcji dodac jakby dodatkowy poziom gwiazdek, 
//  moje rozumienie logiki: otrzymujemy adres i najpierw mowimy komputerowi to na co patrzy ten adres to wskaznik na nowe tablica wskaznikow

bool allocTableTwoDimensional(int**& pDTable, int sizeX, int sizeY) {

    if (sizeX <= 0 or sizeY <= 0) {
        return false;
    }

    pDTable = new int* [sizeX];

    for (int i = 0; i < sizeX; i++) {
        pDTable[i] = new int[sizeY];
    }
    return true;
}
bool allocTableTwoDimensional(int*** pDTable, int sizeX, int sizeY) {

    if (sizeX <= 0 or sizeY <= 0) {
        return false;
    }

    *pDTable = new int* [sizeX];

    for (int i = 0; i < sizeX; i++) {
        (*pDTable)[i] = new int[sizeY];
    }
    return true;
}



//Logika dla *** taka sama jak dla alokacji
//Mozna zmniejszyc liczbe podanych parametrow o wielkosc Y danej tablicy dwuwymiarowej, gdyz potrzebyjemy tylko informacji ile jest
//"tablic w tablicy"
bool deAllocTableTwoDimensional(int**& pDTable, int sizeX, int sizeY) {
    if (sizeX <= 0 or sizeY <= 0) {
        return false;
    }

    for (int i = 0; i < sizeX; i++) {
        delete[] pDTable[i];
    }
    delete[] pDTable;
    return true;
}
bool deAllocTableTwoDimensional(int*** pDTable, int sizeX, int sizeY) {
    if (sizeX <= 0 or sizeY <= 0) {
        return false;
    }

    for (int i = 0; i < sizeX; i++) {
        delete[] (*pDTable)[i];
    }
    delete[] (*pDTable);
    return true;
}

// modyfikacja przez wskaŸnik
void vModTab(Table* pcTab, int iNewSize) {
    std::cout << "Wywolano wersje ze wskaznikiem\n";
    pcTab->setNewSize(iNewSize);
}

// modyfikacja przez wartosc (kopie)
void vModTab(Table cTab, int iNewSize) {
    std::cout << "Wywolano wersje przez wartosc\n";
    cTab.setNewSize(iNewSize);
}