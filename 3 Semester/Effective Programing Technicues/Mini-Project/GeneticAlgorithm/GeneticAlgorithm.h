#pragma once
#include <vector>
#include "..\Individual\Individual.h"
#include "..\Evaluator\Evaluator.h"
#include "..\Result\Result.h"

class GeneticAlgorithm {
public:

    GeneticAlgorithm(int popSize, double crossProb, double mutProb, int maxIterations);

    // Metoda inicjalizuj¹ca populacjê
    Result<void, Error> initialize(const std::string& instancePath);

    // G³ówna pêtla algorytmu 
    void run();

    std::vector<int> getBestSolution() const;
    double getBestFitness() const;

private:

    static const int LOG_INTERVAL = 100;

    int popSize;
    double crossProb;
    double mutProb;
    int maxIterations;

    Evaluator evaluator; //Tutaj siê wywo³a automatycznie Evaluator()
    std::vector<Individual> population;
    std::vector<int> bestGenotype;
    double bestFitness;

    std::mt19937 rng; // Generator liczb losowych dla algorytmu

    // Metoda pomocnicza: Selekcja turniejowa - wybór rodzica
    const Individual& selectParent();
};