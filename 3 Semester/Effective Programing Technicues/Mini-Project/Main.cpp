#include <iostream>
#include <vector>
#include "GeneticAlgorithm\GeneticAlgorithm.h" 

int main() {
    
   
    int popSize = 300;           // Rozmiar populacji 
    double crossProb = 0.7;      // Prawdopodobieñstwo krzy¿owania
    double mutProb = 0.02;       // Prawdopodobieñstwo mutacji
    int maxIterations = 10000;    // Warunek zatrzymania 

    GeneticAlgorithm ag(popSize, crossProb, mutProb, maxIterations);

    // 2. Œcie¿ka do pliku z danymi (umieœæ plik w folderze z projektem lub obok .exe)
    std::string instancePath = "lcvrp/Vrp-Set-A/A-n32-k5.lcvrp";
    Result<void, Error> initResult = ag.initialize(instancePath);

    if (initResult.isFailure()) {
        std::cerr << "Blad inicjalizacji!" << std::endl;

        const auto& errors = initResult.getErrorsVector();
        for (const auto& errPtr : errors) {
            if (errPtr.get()) {
                std::cerr << errPtr->toString() << std::endl;
            }
        }
        return -1; // Zakoñcz program z kodem b³êdu
    }

    std::cout << "Instancja wczytana poprawnie. Start optymalizacji..." << std::endl;

    // 4. Uruchomienie g³ównej pêtli algorytmu
    ag.run();

    // 5. Pobranie i prezentacja wyników 
    std::vector<int> bestSolution = ag.getBestSolution();

    if (bestSolution.empty()) {
        std::cerr << "Nie znaleziono rozwiazania (populacja byla pusta?)" << std::endl;
    }
    else {
        std::cout << "\n--- ZAKONCZONO ---" << std::endl;
        std::cout << "Najlepszy znaleziony genotyp (przydzial klientow do pojazdow):" << std::endl;

        for (size_t i = 0; i < bestSolution.size(); ++i) {
            std::cout << bestSolution[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "Wartosc funkcji celu (dlugosc tras): " << ag.getBestFitness() << std::endl;
    }

    

    return 0;
}