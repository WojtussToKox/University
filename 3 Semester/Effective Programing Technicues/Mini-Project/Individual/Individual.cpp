#include "Individual.h"

Individual::Individual(int genotypeSize, int numberOfVehicles, std::mt19937& rng)
	: fitness(0.0), isEvaluated(false)
{
	
	std::uniform_int_distribution<> disDist(0, numberOfVehicles - 1);

	genotype.reserve(genotypeSize);
	for (int i = 0; i < genotypeSize; ++i) {
		genotype.push_back(disDist(rng));
	}
}

Individual::Individual(const std::vector<int>& newGen, double fitness)
	: fitness(fitness), isEvaluated(false)
{
	genotype = newGen;
	isEvaluated = false;
}

Individual::Individual(const Individual& other)
	: genotype(other.genotype),
	fitness(other.fitness),      
	isEvaluated(other.isEvaluated)
{
}

Individual::Individual(Individual&& other) noexcept
	: genotype(std::move(other.genotype)), // Przejêcie wskaŸnika wektora
	fitness(other.fitness),
	isEvaluated(other.isEvaluated)
{
	other.fitness = 0.0;
}

Individual& Individual::operator=(const Individual& other) {
	if (this != &other) {
		genotype = other.genotype;
		fitness = other.fitness;
		isEvaluated = other.isEvaluated;
	}
	return *this;
}

Individual& Individual::operator=(Individual&& other) noexcept{
	if (this != &other) {
		genotype = std::move(other.genotype);
		fitness = other.fitness;
		isEvaluated = other.isEvaluated;

		other.fitness = 0.0;
	}
	return *this;
}

double Individual::calculateFitness(Evaluator& evaluator) {
	if (isEvaluated) return fitness;

	fitness = evaluator.Evaluate(genotype);
	isEvaluated = true;
	return fitness;
}

void Individual::mutate(int numberOfVehicles, double mutProb, std::mt19937& rng)
{
	std::uniform_real_distribution<> probDist(0.0, 1.0);
	std::uniform_int_distribution<> valDist(0, numberOfVehicles - 1);

	for (int& gene : genotype) {
		if (probDist(rng) < mutProb) {
			gene = valDist(rng);
			isEvaluated = false;
		}
	}
}

std::pair<Individual, Individual> Individual::crossover(const Individual& other, double crossProb, std::mt19937& rng) const
{
	std::uniform_real_distribution<> probDist(0.0, 1.0);

	if (probDist(rng) > crossProb) {
		return std::make_pair(*this, other);
	}

	std::uniform_int_distribution<> cutDist(1, genotype.size() - 1);

	int cutPoint = cutDist(rng);

	Individual child1 = *this;
	Individual child2 = other;

	for (int i = cutPoint; i < genotype.size(); i++) {
		child1.genotype[i] = other.genotype[i];
		child2.genotype[i] = this->genotype[i];
	}

	child1.isEvaluated = false;
	child2.isEvaluated = false;

	return std::make_pair(std::move(child1), std::move(child2));
}

void Individual::setGenotype(const std::vector<int>& newGen)
{
	genotype = newGen;
	isEvaluated = false;
}
