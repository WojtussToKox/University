#pragma once

#include <iostream>
#include "table.h"

// Tworzenie tablicy i wypelnienie
void dynamicAllocTableWithFillWith34(int tableSize);

// funkcje Alokacji
bool allocTableTwoDimensional(int**& pDTable, int sizeX, int sizeY);
bool allocTableTwoDimensional(int*** pDTable, int sizeX, int sizeY);

// funkcje Dealokacji
bool deAllocTableTwoDimensional(int**& pDTable, int sizeX, int sizeY);
bool deAllocTableTwoDimensional(int*** pDTable, int sizeX, int sizeY);

void vModTab(Table* pcTab, int iNewSize);
void vModTab(Table cTab, int iNewSize);