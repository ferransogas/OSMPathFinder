#ifndef GRAF
#define GRAF

#include <vector>
#include <string>
#include <cstdio>
#include "Common.h"
#include "Util.h"
#include <limits>
#include <stack>

class Graf
{
public:
    Graf();
    ~Graf();

    size_t getNumNodes() { return m_numNodes; }

    void inserirAresta(std::vector<Coordinate> nodes);
    void eliminarAresta(int posNode1, int posNode2);

    void afegirNode(const Coordinate &node);
    void eliminarNode(const Coordinate &node);

    std::vector<Coordinate> camiCurt(const Coordinate &a, const Coordinate &b);

private:
    std::vector<Coordinate> m_nodes;
    std::vector<std::vector<double>> m_matriuAdj;
    size_t m_numNodes;
    size_t m_numArestes;

    void dijkstra(int node_inicial, int node_final, std::vector<int> dist, std::vector<size_t> anterior);
    size_t minDistance(const std::vector<int> &dist, const std::vector<bool> &visitat) const;
    static const int DISTMAX;
};

#endif // GRAF
