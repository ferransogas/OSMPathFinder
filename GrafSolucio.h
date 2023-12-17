#ifndef GRAF
#define GRAF

#include <vector>
#include <string>
#include <cstdio>
#include "Common.h"
#include "Util.h"

class Graf
{
public:
    Graf();
    ~Graf();

    size_t getNumNodes() { return m_numNodes; }
    
    void inserirAresta(std::vector<Coordinate> nodes);
    void eliminarAresta(int posNode1, int posNode2);

    void afegirNode(const Coordinate& node);
    void eliminarNode(const Coordinate& node);

private:

protected:
    std::vector<Coordinate> m_nodes;
    std::vector<std::vector<double>> m_matriuAdj;
    size_t m_numNodes;
    size_t m_numArestes;
};

#endif //GRAF

