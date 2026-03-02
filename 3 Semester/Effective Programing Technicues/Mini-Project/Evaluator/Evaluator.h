#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>
#include <limits>
#include <algorithm>
#include "..\Result\Result.h"

class Individual;

struct Node {
	int id;
	double x;
	double y;
	int demand;
};

class Evaluator {

public:

	Evaluator();

	Result<void, Error> LoadInstance(const std::string& path);
	double Evaluate(const std::vector<int>& genotype);
	int GetNumberOfClients() const;
	int GetNumberOfVehicles() const;

	static const double PENALTY_FACTOR;

	// --- STA£E PARSERA ---
	static const std::string KEYWORD_EOF;
	static const std::string KEYWORD_NAME;
	static const std::string KEYWORD_DIMENSION;
	static const std::string KEYWORD_CAPACITY;
	static const std::string KEYWORD_VEHICLES;
	static const std::string KEYWORD_PERMUTATION;
	static const std::string KEYWORD_NODE_COORD_SECTION;
	static const std::string KEYWORD_DEMAND_SECTION;
	static const std::string KEYWORD_DEPOT_SECTION;

	static const std::string SECTION_COORDS;
	static const std::string SECTION_DEMAND;
	static const std::string SECTION_DEPOT;
	static const std::string SECTION_EOF;

	static const std::string ERROR_OPEN_FILE;
	static const std::string ERROR_EMPTY_FILE;
	static const std::string ERROR_MISSING_K;

	void saveToPython(Individual& instance, const std::string& filename) const;

private:
	std::vector<Node> nodes;          // Lista wszystkich wêz³ów (indeks 0 to depot, bo ID s¹ od 1)
	std::vector<int> fixedPermutation; // Sta³a permutacja klientów wczytana z pliku

	std::vector<std::vector<double>> distanceMatrix;
	
	double getDistance(int i, int j) const {
		return distanceMatrix[i][j];
	}


	int capacity;                     // £adownoœæ pojazdu
	int dimension;                    // Liczba wszystkich wêz³ów (depot + klienci)
	int vehiclesCount;                // Liczba dostêpnych pojazdów (k)
	int depotId;
};