#include "GrafSolucio.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <stack>
#include <limits>

const int Graf::DISTMAX{std::numeric_limits<int>::max()};

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
    // Tots els nodes del vector estan rel·lacionats entre ells, el seus pesos són les DistanciaHaversine()

    // Recorrem les files de la matriu
    for (int i = 0; i < m_numNodes; ++i)
    {
        // Recorrem les coordenades del vector node
        for (int j = 0; j < nodes.size(); ++j)
        {
            // Busquem si node de la matriu i node del vector correspon
            if (m_nodes[i].lat == nodes[j].lat && m_nodes[i].lon == nodes[j].lon)
            {
                // Recorrem les columnes de la matriu
                // m=i+1 ja que el graf és simètric
                for (int m = i + 1; m < m_numNodes; ++m)
                {
                    // Recorrem les coordenades del vector node per enllaçar-les a la coordenada de posicio j
                    // n=j+1 ja que el graf és simètric
                    for (int n = j + 1; n < nodes.size(); ++n)
                    {
                        // Busquem si node de la matriu i node del vector correspon
                        if (m_nodes[m].lat == nodes[n].lat && m_nodes[m].lon == nodes[n].lon)
                        {
                            // Inserim en la posicio [i][m] de la matriu la relació ponderada amb valor DistanciaHaversine() de entre nodes [j] i [n]
                            m_matriuAdj[i][m] = Util::DistanciaHaversine(nodes[j], nodes[n]);
                            m_matriuAdj[m][i] = Util::DistanciaHaversine(nodes[n], nodes[j]);
                            m_numArestes++;
                        }
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
    std::vector<int> dist;
    std::vector<size_t> anterior;

    size_t node_inicial = -1, node_final = -1;
    bool trobats = false;
    for (int i = 0; i < m_numNodes && !trobats; ++i)
    {
        if (m_nodes[i].lat == a.lat && m_nodes[i].lon == a.lon)
            node_inicial = i;
        if (m_nodes[i].lat == b.lat && m_nodes[i].lon == b.lon)
            node_final = i;
        if (node_inicial != -1 && node_final != -1)
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

void Graf::dijkstra(int node_inicial, int node_final, std::vector<int> dist, std::vector<size_t> anterior)
{
    dist.resize(m_numNodes, DISTMAX);
    dist[node_inicial] = 0;
    std::vector<bool> visitat;
    visitat.resize(m_numNodes, false);
    anterior.resize(m_numNodes, -1);
    anterior[node_inicial] = node_inicial;

    for (int i = 0; i < m_numNodes - 1; ++i)
    {
        int actual = minDistance(dist, visitat);
        visitat[actual] = true;
        if (actual == node_final)
            return;
        for (int j = 0; j < m_numNodes; ++j)
        {
            if (!visitat[j] && m_matriuAdj[actual][j] != 0 && dist[actual] + m_matriuAdj[actual][j] < dist[j])
            {
                dist[j] = dist[actual] + m_matriuAdj[actual][j];
                anterior[j] = actual;
            }
        }
    }
}

size_t Graf::minDistance(const std::vector<int> &dist, const std::vector<bool> &visitat) const
{
    // Initialize min value
    int min = DISTMAX;
    size_t minIndex = -1;

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
