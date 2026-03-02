#include "Evaluator.h"
#include <iostream>
#include "../Individual/Individual.h"
const double Evaluator::PENALTY_FACTOR = 1000.0;

const std::string Evaluator::KEYWORD_EOF = "EOF";
const std::string Evaluator::KEYWORD_NAME = "NAME";
const std::string Evaluator::KEYWORD_DIMENSION = "DIMENSION";
const std::string Evaluator::KEYWORD_CAPACITY = "CAPACITY";
const std::string Evaluator::KEYWORD_VEHICLES = "VEHICLES";
const std::string Evaluator::KEYWORD_PERMUTATION = "PERMUTATION";
const std::string Evaluator::KEYWORD_NODE_COORD_SECTION = "NODE_COORD_SECTION";
const std::string Evaluator::KEYWORD_DEMAND_SECTION = "DEMAND_SECTION";
const std::string Evaluator::KEYWORD_DEPOT_SECTION = "DEPOT_SECTION";

const std::string Evaluator::SECTION_COORDS = "COORDS";
const std::string Evaluator::SECTION_DEMAND = "DEMAND";
const std::string Evaluator::SECTION_DEPOT = "DEPOT";
const std::string Evaluator::SECTION_EOF = "EOF";

const std::string Evaluator::ERROR_OPEN_FILE = "Could not open file: ";
const std::string Evaluator::ERROR_EMPTY_FILE = "File empty.";
const std::string Evaluator::ERROR_MISSING_K = "Missing 'k' (vehicles count).";

// Funkcja statyczna (prywatna dla pliku), ¿eby nie zaœmiecaæ klasy
static double calculateDistance(const Node& n1, const Node& n2) {
    double dx = n1.x - n2.x;
    double dy = n1.y - n2.y;
    return std::sqrt(dx * dx + dy * dy);
}

// Funkcja pomocnicza do pomijania bia³ych znaków i opcjonalnego dwukropka
static void skipColon(std::stringstream& ss) {
    char nextChar = ss.peek();

    // Pomiñ spacje i tabulatory
    while (!ss.eof() && (nextChar == ' ' || nextChar == '\t')) {
        ss.get(); // skonsumuj znak
        nextChar = ss.peek();
    }

    // Jeœli trafiliœmy na dwukropek, zjedz go
    if (nextChar == ':') {
        ss.get();
    }
}

Evaluator::Evaluator()
    : capacity(0), dimension(0), vehiclesCount(0), depotId(0)
{
}

Result<void, Error> Evaluator::LoadInstance(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open()){
        return Result<void, Error>::Failure(
            new Error(Error::Code::FILE_OPEN_FAILED, ERROR_OPEN_FILE + path)
        );
    }

    

    nodes.clear();
    fixedPermutation.clear();
    capacity = 0;
    dimension = 0;
    vehiclesCount = 0;
    depotId = 0;

    std::vector<int> rawPermutation;
    std::string line;
    std::string section = "";

    while (std::getline(file, line) && section != SECTION_EOF) {
        if (!line.empty()) {

            std::stringstream ss(line);
            std::string keyword;
            ss >> keyword;


            // Jeœli keyword to np. "DIMENSION:", usuwamy dwukropek z koñca
            if (!keyword.empty() && keyword.back() == ':') {
                keyword.pop_back();
            }

            // Zawsze próbujemy zjeœæ dwukropek, który móg³ zostaæ w strumieniu (np. "DIMENSION : 45")
            skipColon(ss);





            if (keyword == KEYWORD_NAME) {
                std::string nameValue;
                ss >> nameValue; // Wczytujemy np. "P-n45-k5"

                // Próba wyci¹gniêcia liczby pojazdów z nazwy (szukamy 'k')
                size_t kPos = nameValue.rfind('k');
                if (kPos != std::string::npos && kPos + 1 < nameValue.length()) {
                    try {
                        vehiclesCount = std::stoi(nameValue.substr(kPos + 1));
                    }
                    catch (...) {
                        // Jeœli b³¹d konwersji, vehiclesCount pozostaje 0
                    }
                }
            }
            else if (keyword == KEYWORD_DIMENSION) {
                ss >> dimension;
            }
            else if (keyword == KEYWORD_CAPACITY) {
                ss >> capacity;
            }
            else if (keyword == KEYWORD_VEHICLES) {
                ss >> vehiclesCount;
            }
            else if (keyword == KEYWORD_PERMUTATION) {
                int nodeId;
                while (ss >> nodeId) rawPermutation.push_back(nodeId);
            }
            else if (keyword == KEYWORD_NODE_COORD_SECTION) {
                section = SECTION_COORDS;
            }
            else if (keyword == KEYWORD_DEMAND_SECTION) {
                section = SECTION_DEMAND;
            }
            else if (keyword == KEYWORD_DEPOT_SECTION) {
                section = SECTION_DEPOT;
            }
            else if (keyword == KEYWORD_EOF) {
                section = SECTION_EOF;
            }

            if (section == SECTION_COORDS) {
                std::stringstream ls(line);
                int id;
                double x, y;
                if (ls >> id >> x >> y) {
                    if (nodes.size() < dimension) {
                        Node n;
                        n.id = id;
                        n.x = x;
                        n.y = y;
                        n.demand = 0;
                        nodes.push_back(n);
                    }
                }
            }

            else if (section == SECTION_DEMAND) {
                std::stringstream ls(line);
                int id, demand;
                if (ls >> id >> demand) {
                    if (id > 0 && id <= (int)nodes.size()) {
                        nodes[id - 1].demand = demand;
                    }
                }
            }

            else if (section == SECTION_DEPOT) {
                std::stringstream ls(line);
                int id;
                if (ls >> id && id != -1) {
                    depotId = id - 1; // Zapamiêtujemy, który to indeks (zazwyczaj wyjdzie 0)
                }
            }
        }
    }

    if (nodes.empty()) return Result<void, Error>::Failure(new Error(Error::Code::EMPTY_FILE, ERROR_EMPTY_FILE));
    if (vehiclesCount <= 0) return Result<void, Error>::Failure(new Error(Error::Code::INVALID_DATA_FORMAT, ERROR_MISSING_K));

    // Zabezpieczenie depotId
    if (depotId < 0 || depotId >= nodes.size()) depotId = 0;

    int nSize = (int)nodes.size();
    distanceMatrix.assign(nSize, std::vector<double>(nSize));
    for (int i = 0; i < nSize; ++i) {
        for (int j = 0; j < nSize; ++j) {
            distanceMatrix[i][j] = calculateDistance(nodes[i], nodes[j]);
        }
    }

    fixedPermutation.clear();

    if (!rawPermutation.empty()) {
        for (int id : rawPermutation) {
            int idx = id - 1; // ID na Index
            // Dodajemy tylko jeœli to nie jest depot!
            if (idx >= 0 && idx < nSize && idx != depotId) {
                fixedPermutation.push_back(idx);
            }
        }
    }
    else {
        for (int i = 0; i < nSize; ++i) {
            if (i != depotId) {
                fixedPermutation.push_back(i);
            }
        }
    }
    

    return Result<void, Error>::Success();
}

double Evaluator::Evaluate(const std::vector<int>& genotype)
{
    double totalDistance = 0.0;
    double penalty = 0.0;

    for (int v = 0; v < vehiclesCount; v++) {
        int previousNodeId = depotId;

        double routeDistance = 0.0;
        int currentLoad = 0;
        bool vehicleUsed = false;

        for (int i = 0; i < fixedPermutation.size(); i++) {
            if (genotype[i] == v) {
                vehicleUsed = true;
                int currentNodeIdx = fixedPermutation[i];

                // Czytamy odleg³oœæ z macierzy (np. Depot -> Klient 1)
                routeDistance += distanceMatrix[previousNodeId][currentNodeIdx];

                currentLoad += nodes[currentNodeIdx].demand;
                previousNodeId = currentNodeIdx; // Jesteœmy teraz u klienta
            }
        }

        if (vehicleUsed) {
            // Powrót: Ostatni klient -> DEPOT
            routeDistance += distanceMatrix[previousNodeId][depotId];

            totalDistance += routeDistance;

            if (currentLoad > capacity) {
                penalty += (currentLoad - capacity) * PENALTY_FACTOR;
            }
        }
    }

    return totalDistance + penalty;
}

int Evaluator::GetNumberOfClients() const {
    return (int)fixedPermutation.size();
}

int Evaluator::GetNumberOfVehicles() const {
    return vehiclesCount;
}


void Evaluator::saveToPython(Individual& instance, const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << "import matplotlib.pyplot as plt\n\n";
    file << "def plot_routes():\n";

    // 1. Zapisujemy wspó³rzêdne u¿ywaj¹c indeksów z wektora nodes jako kluczy (0, 1, 2...)
    file << "    # Wspolrzedne (id_wezla: (x, y))\n";
    file << "    coords = {\n";
    for (int i = 0; i < nodes.size(); i++) {
        // Kluczem jest 'i' (indeks w wektorze), a nie nodes[i].id
        // Dziêki temu ³atwiej nam operowaæ na macierzach i wektorach w dalszej czêœci
        file << "        " << i << ": (" << nodes[i].x << ", " << nodes[i].y << "),\n";
    }
    file << "    }\n\n";

    // 2. Rysowanie punktów (Depot vs Klienci)
    // Depot (czerwony kwadrat)
    file << "    plt.plot(coords[" << depotId << "][0], coords[" << depotId << "][1], 'rs', markersize=10, label='Depot')\n";

    // Klienci (niebieskie kropki)
    file << "    for i in coords:\n";
    file << "        if i != " << depotId << ":\n";
    file << "            plt.plot(coords[i][0], coords[i][1], 'bo', markersize=5)\n\n";

    // 3. Dekodowanie tras z genotypu
    const std::vector<int>& genotype = instance.getGenotype();
    std::vector<std::vector<int>> truck_routes(vehiclesCount);

    // Genotyp mapuje siê 1:1 na fixedPermutation
    // genotype[i] mówi, który pojazd obs³uguje klienta wskazanego przez fixedPermutation[i]
    for (size_t i = 0; i < genotype.size(); i++) {
        int truck_id = genotype[i];

        // ZABEZPIECZENIE: Sprawdzamy czy genotyp pasuje rozmiarem do permutacji
        if (i < fixedPermutation.size()) {
            int node_index = fixedPermutation[i]; // Pobieramy prawdziwy indeks wêz³a

            // Upewniamy siê, ¿e truck_id jest poprawny
            if (truck_id >= 0 && truck_id < vehiclesCount) {
                truck_routes[truck_id].push_back(node_index);
            }
        }
    }

    std::string colors[] = { "'b'", "'g'", "'c'", "'m'", "'y'", "'k'" };

    file << "    # Generowanie Tras\n";
    for (int i = 0; i < vehiclesCount; i++) {
        if (truck_routes[i].empty()) continue;

        std::string color = colors[i % 6];

        file << "    # Trasa Pojazdu " << i + 1 << "\n";
        // Start w Depocie
        file << "    x = [coords[" << depotId << "][0]]\n";
        file << "    y = [coords[" << depotId << "][1]]\n";

        // Odwiedzanie klientów
        for (int client_idx : truck_routes[i]) {
            file << "    x.append(coords[" << client_idx << "][0])\n";
            file << "    y.append(coords[" << client_idx << "][1])\n";
        }

        // Powrót do Depota
        file << "    x.append(coords[" << depotId << "][0])\n";
        file << "    y.append(coords[" << depotId << "][1])\n";

        file << "    plt.plot(x, y, color=" << color << ", linestyle='-', linewidth=1.5, label='Trasa " << i + 1 << "')\n";
    }

    file << "\n    plt.title('Wizualizacja VRP - Fitness: " << instance.getFitness() << "')\n";
    file << "    plt.legend(loc='upper right', bbox_to_anchor=(1.15, 1))\n"; // Legenda nieco z boku
    file << "    plt.grid(True)\n";
    file << "    plt.show()\n\n";

    file << "if __name__ == '__main__':\n";
    file << "    plot_routes()\n";

    file.close();
}