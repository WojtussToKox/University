#pragma once
#include <vector>
#include <random>
#include "..\Evaluator\Evaluator.h"

class Individual {
public:
    // Konstruktor losowy
    Individual(int genotypeSize, int numberOfVehicles, std::mt19937& rd);
    Individual(const std::vector<int>& newGen, double fitness);
    // Konstruktor kopiuj¹cy i przenosz¹cy (potrzebne do vectora populacji)
    Individual(const Individual& other);
    Individual(Individual&& other) noexcept;
    Individual& operator=(const Individual& other);
    Individual& operator=(Individual&& other) noexcept;

    double calculateFitness(Evaluator& evaluator);
    void mutate(int numberOfVehicles,double mutProb, std::mt19937& rng);
    std::pair<Individual, Individual> crossover(const Individual& other, double crossProb, std::mt19937& rng) const;

    // Gettery
    const std::vector<int>& getGenotype() const { return genotype; }
    double getFitness() const { return fitness; }

    // Metoda pomocnicza do ustawiania genotypu (dla dzieci z crossovera)
    void setGenotype(const std::vector<int>& newGen);


private:
    std::vector<int> genotype;
    double fitness;
    bool isEvaluated; // Flaga, czy fitness jest aktualny
};