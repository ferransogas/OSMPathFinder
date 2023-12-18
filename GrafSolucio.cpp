#include "GrafSolucio.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <stack>
#include <limits>

const double Graf::DISTMAX{std::numeric_limits<double>::max()};
const int Graf::INTMAX{ std::numeric_limits<int>::max() };

Graf::Graf()
{
    m_numNodes = 0;
    m_numArestes = 0;
}

Graf::~Graf()
{
}

void Graf::inserirAresta(std::vector<Coordinate> nodes)
{
    // Cada node està rel·lacionat amb el següent del vector
    
    // Recorrer els nodes i del vector
    for (int i = 0; i < nodes.size() - 1; ++i) {
        // Per cada node, recórrer els nodes m la matriu
        for (int m = 0; m < m_numNodes; ++m) {
            // Quan trobi el m==i que coincideix, recórrer els nodes n de la matriu
            if (m_nodes[m].lat == nodes[i].lat && m_nodes[m].lon == nodes[i].lon) {
                for (int n = 0; n < m_numNodes; ++n) {
                    // Per cada node de la matriu, comprovar si coincideix n==i+1 amb el següent node del vector
                    if (m_nodes[n].lat == nodes[i + 1].lat && m_nodes[n].lon == nodes[i + 1].lon) {
                        // Si coincideix, s'afegeix aresta a [m][n] amb pes distanciaHaversine(i,i+1)
                        m_matriuAdj[m][n] = Util::DistanciaHaversine(nodes[i], nodes[i + 1]);
                        m_matriuAdj[n][m] = Util::DistanciaHaversine(nodes[i + 1], nodes[i]);
                    }
                }
            }
        }
    }
}

void Graf::eliminarAresta(int posNode1, int posNode2)
{
    m_matriuAdj[posNode1][posNode2] = 0;
    m_matriuAdj[posNode2][posNode1] = 0;
}

void Graf::afegirNode(const Coordinate &node)
{
    // Busquem que el node no existeixi per no afegir repetits
    bool trobat = false;
    for (auto it = m_nodes.begin(); it < m_nodes.end() && !trobat; ++it)
    {
        if (it->lat == node.lat && it->lon == node.lon)
        {
            trobat = true;
        }
    }

    if (!trobat)
    {
        // Afegir node al vector m_nodes
        m_nodes.push_back(node);

        // Afegir una fila per aquell nou node
        m_matriuAdj.push_back(std::vector<double>(m_numNodes));

        // Indicar que tenim un node més
        m_numNodes++;

        // Afegir un 0 (no relació) per cada node
        for (int i = 0; i < m_numNodes; i++)
            m_matriuAdj[i].push_back(0);
    }
}

void Graf::eliminarNode(const Coordinate &node)
{
    // Busquem la posició del node a esborrar
    std::vector<Coordinate>::iterator it;

    bool trobat = false;
    for (it = m_nodes.begin(); it < m_nodes.end() && !trobat; ++it)
    {
        if (it->lat == node.lat && it->lon == node.lon)
        {
            trobat = true;
        }
    }

    // Eliminem el node del vector de nodes i de la matriu d'adjacència
    if (trobat)
    {
        // Posició en el vector del node a borrar guardada a pos
        size_t pos = distance(m_nodes.begin(), it);

        // Eliminem el node del vector de nodes
        m_nodes.erase(m_nodes.begin() + pos);

        // Eliminem la fila i la columna de la matriu d'adjacència corresponents a aquest node
        m_matriuAdj.erase(m_matriuAdj.begin() + pos);

        for (int i = 0; i < m_numNodes; i++)
        {
            m_matriuAdj[i].erase(m_matriuAdj[i].begin() + pos);
        }

        // Indicar que tenim un node menys
        m_numNodes--;
    }
}

std::vector<Coordinate> Graf::camiCurt(const Coordinate &a, const Coordinate &b)
{
    std::vector<double> dist;
    std::vector<int> anterior;

    int node_inicial = INTMAX, node_final = INTMAX;
    bool trobats = false;
    for (int i = 0; i < m_numNodes && !trobats; ++i)
    {
        if (m_nodes[i].lat == a.lat && m_nodes[i].lon == a.lon)
            node_inicial = i;
        if (m_nodes[i].lat == b.lat && m_nodes[i].lon == b.lon)
            node_final = i;
        if (node_inicial != INTMAX && node_final != INTMAX)
            trobats = true;
    }

    dijkstra(node_inicial, node_final, dist, anterior);

    std::stack<Coordinate> cami;

    cami.push(m_nodes[node_final]);

    int it = node_final;
    while (it != node_inicial)
    {
        cami.push(m_nodes[anterior[it]]);
        it = anterior[it];
    }

    std::vector<Coordinate> vecCami;
    while (!cami.empty())
    {
        vecCami.push_back(cami.top());
        cami.pop();
    }

    return vecCami;
}

void Graf::dijkstra(int node_inicial, int node_final, std::vector<double>& dist, std::vector<int>& anterior)
{
    dist.resize(m_numNodes, DISTMAX);
    dist[node_inicial] = 0;
    std::vector<bool> visitat;
    visitat.resize(m_numNodes, false);
    anterior.resize(m_numNodes, INTMAX);
    anterior[node_inicial] = node_inicial;

    for (int i = 0; i < m_numNodes - 1; ++i)
    {
        int actual = minDistance(dist, visitat);
        visitat[actual] = true;
        if (actual == node_final)
            return;
        for (int j = 0; j < m_numNodes; ++j)
        {
            if (!visitat[j] && m_matriuAdj[actual][j] != 0 && dist[actual] != DISTMAX && m_matriuAdj[actual][j] != DISTMAX && dist[actual] + m_matriuAdj[actual][j] < dist[j])
            {
                dist[j] = dist[actual] + m_matriuAdj[actual][j];
                anterior[j] = actual;
            }
        }
    }
}

int Graf::minDistance(const std::vector<double> &dist, const std::vector<bool> &visitat) const
{
    double min = DISTMAX;
    int minIndex = INTMAX;

    for (int i = 0; i < m_numNodes; ++i)
    {
        if (!visitat[i] && dist[i] <= min)
        {
            min = dist[i];
            minIndex = i;
        }
    }

    return minIndex;
}
