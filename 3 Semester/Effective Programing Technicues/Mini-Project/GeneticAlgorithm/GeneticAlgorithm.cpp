#include "GeneticAlgorithm.h"
#include <limits>
#include <algorithm>
#include <iostream> // Do debugowania


GeneticAlgorithm::GeneticAlgorithm(int popSize, double crossProb, double mutProb, int maxIterations)
	: popSize(popSize),
	  crossProb(crossProb),
	  mutProb(mutProb) ,
	  maxIterations(maxIterations),
	  bestFitness(std::numeric_limits<double>::max())
{
	std::random_device rd;
	rng.seed(rd());
}

Result<void, Error> GeneticAlgorithm::initialize(const std::string& instancePath)
{
	Result<void, Error> loadResult = evaluator.LoadInstance(instancePath);

	if (loadResult.isFailure()) {
		return loadResult;
	}
	//1. Pobranie wymiarow
	int genotypeSize = evaluator.GetNumberOfClients();
	int numberOfVehicles = evaluator.GetNumberOfVehicles();


	//2. Reset stanu
	population.clear();
	population.reserve(popSize);
	bestFitness = std::numeric_limits<double>::max();
	bestGenotype.clear();


	//3. Tworzenie populacji looswej

	for (int i = 0; i < popSize; i++) {
		Individual ind(genotypeSize, numberOfVehicles, rng);

		double fitness = ind.calculateFitness(evaluator);

		if (fitness < bestFitness) {
			bestFitness = fitness;
			bestGenotype = ind.getGenotype();
		}

		population.push_back(std::move(ind));
	}

	return Result<void, Error>::Success();
}

void GeneticAlgorithm::run()
{
	if (population.empty()) return;

	int vehiclesCount = evaluator.GetNumberOfVehicles();

	for (int it = 0; it < maxIterations; it++) {
		if (it % LOG_INTERVAL == 0) {
			std::cout << it << ". Best Fitness so Far -> " << bestFitness << std::endl;
		}

		std::vector<Individual> newPopulation;
		newPopulation.reserve(popSize);


		while (newPopulation.size() < popSize) {
			const Individual& parent1 = selectParent();
			const Individual& parent2 = selectParent();

			std::pair<Individual, Individual> children = parent1.crossover(parent2, crossProb, rng);

			children.first.mutate(vehiclesCount, mutProb, rng);
			children.second.mutate(vehiclesCount, mutProb, rng);

			double fit1 = children.first.calculateFitness(evaluator);
			double fit2 = children.second.calculateFitness(evaluator);

			if (fit1 < bestFitness) {
				bestFitness = fit1;
				bestGenotype = children.first.getGenotype();
			}

			if (fit2 < bestFitness) {
				bestFitness = fit2;
				bestGenotype = children.second.getGenotype();
			}

			newPopulation.push_back(std::move(children.first));

			if (newPopulation.size() < popSize) {
				newPopulation.push_back(std::move(children.second));
			}
		}

		population = std::move(newPopulation);
	}
	Individual best(bestGenotype, bestFitness);
	evaluator.saveToPython(best, "Najlepszy.txt");
}
std::vector<int> GeneticAlgorithm::getBestSolution() const {
	return bestGenotype;
}

double GeneticAlgorithm::getBestFitness() const
{
	return bestFitness;
}

const Individual& GeneticAlgorithm::selectParent() {

	std::uniform_int_distribution<> dist(0, (int)population.size() - 1);

	int idx1 = dist(rng);
	int idx2 = dist(rng);

	// Pobieramy referencje do kandydatów
	const Individual& cand1 = population[idx1];
	const Individual& cand2 = population[idx2];

	// Problem minimalizacji: mniejszy fitness = lepszy
	if (cand1.getFitness() < cand2.getFitness()) {
		return cand1;
	}
	else {
		return cand2;
	}
}