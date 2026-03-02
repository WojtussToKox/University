#include <iostream>
#include <string>
#include <vector>
#include "AlgebraicTree.h"
#include "Result.h"
#include "Error.h"
#include "FileSaver.h"

void printTestResult(std::string testName, Result<AlgebraicTree*, Error> result)
{
    std::cout << "--------------------------------------------------" << std::endl;
    if (result.isSuccess())
    {
        std::cout << "STATUS: [SUKCES]" << std::endl;

        AlgebraicTree* tree = result.getValue();

        std::cout << "Wynikowe drzewo (prefix): " << tree->toStringTree() << std::endl;
    }
    else
    {
        std::cout << "STATUS: [BLAD] (Zgodnie z oczekiwaniem dla blednej formuly)" << std::endl;
        std::cout << "Znalezione bledy:" << std::endl;

        std::vector<Error*>& errors = result.getErrors();
        for (size_t i = 0; i < errors.size(); i++)
        {
            std::cout << "  " << i + 1 << ". " << errors[i]->getErrorMessage() << std::endl;
        }
    }
    std::cout << "--------------------------------------------------" << std::endl << std::endl;
}

void testZadanie5()
{

    // 1. Test dla zwyk³ego inta (Wersja ogólna)
    Result<int, Error> resInt = Result<int, Error>::fail(new Error("B³¹d obliczeñ dla inta"));
    FileSaver<int, Error>::saveToFile("wynik_int_blad.txt", resInt);
    std::cout << "Zapisano 'wynik_int_blad.txt' (powinien zawierac blad)." << std::endl;

    // 2. Test dla Drzewa - SUKCES
    std::string formulaOk = "+ 5 2";
    Result<AlgebraicTree*, Error> resTreeOk = AlgebraicTree::buildTree(formulaOk);

    FileSaver<AlgebraicTree*, Error>::saveToFile("wynik_drzewo_ok.txt", resTreeOk);
    std::cout << "Zapisano 'wynik_drzewo_ok.txt' (powinien zawierac formule '+ 5 2')." << std::endl;

    // 3. Test dla Drzewa - BLAD
    std::string formulaBad = "+ 5 + + 6"; // Brakuje argumentu
    Result<AlgebraicTree*, Error> resTreeBad = AlgebraicTree::buildTree(formulaBad);
    
    FileSaver<AlgebraicTree*, Error>::saveToFile("wynik_drzewo_blad.txt", resTreeBad);
    std::cout << "Zapisano 'wynik_drzewo_blad.txt' (powinien zawierac opis bledu)." << std::endl;
}

int main()
{
    std::string validFormula = "+ * 5 sin x 2"; 
    std::string invalidFormula = "+ 5 * smieci_na_koncu @#$ 50";
    std::string dirtyFormula = "5 50 5";

    Result<AlgebraicTree*, Error> r1 = AlgebraicTree::buildTree(validFormula);
    printTestResult("Statyczna - Poprawna formula", r1);
    std::cout << "Stan obiektu: " << r1.getValue()->toStringTree() << std::endl;

    Result<AlgebraicTree*, Error> r2 = AlgebraicTree::buildTree(invalidFormula);
    printTestResult("Statyczna - Bledna formula (nadmiar znakow)", r2);
    if (r2.isSuccess()) {
        std::cout << "Stan obiektu: " << r2.getValue()->toStringTree() << std::endl;
    }
    else {
        std::cout << "Brak utworzonego obiektu. " << std::endl;
    }

    Result<AlgebraicTree*, Error> r3 = AlgebraicTree::buildTree(dirtyFormula);
    printTestResult("Statyczna - Bledna formula (nadmiar znakow)", r3);



    AlgebraicTree myTree;

    Result<AlgebraicTree*, Error> r4 = myTree.buildTreeFromFormula(validFormula);
    printTestResult("Niestatyczna - Poprawna formula", r4);
    Result<AlgebraicTree*, Error> r5 = myTree.buildTreeFromFormula(invalidFormula);
    printTestResult("Niestatyczna - Bledna formula", r5);
    Result<AlgebraicTree*, Error> r6 = myTree.buildTreeFromFormula(dirtyFormula);
    printTestResult("Niestatyczna - Bledna formula (nadmiar znakow)", r6);

    std::cout << "Stan obiektu: " << myTree.toStringTree() << std::endl;


    testZadanie5();

    return 0;
}