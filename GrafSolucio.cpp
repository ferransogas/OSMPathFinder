#include "GrafSolucio.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

Graf::Graf()
{
    m_numNodes = 0;
    m_numArestes = 0;
}

Graf::Graf(const std::vector<std::string>& nodes, const std::vector<std::vector<int>>& parelles_nodes)
{
    m_nodes = nodes;
    m_numNodes = m_nodes.size();
    m_numArestes = parelles_nodes.size();
    crearMatriu(parelles_nodes);
}

Graf::~Graf()
{
}

void Graf::crearMatriu(const std::vector<std::vector<int>>& parelles)
{
    m_matriuAdj.resize(m_numNodes);
    for (size_t i = 0; i < m_numNodes; i++)
    {
        m_matriuAdj[i].resize(m_numNodes, 0);
    }
    for(size_t i=0; i<parelles.size();i++){
        m_matriuAdj[parelles[i][0]][parelles[i][1]]=1;
        m_matriuAdj[parelles[i][1]][parelles[i][0]]=1;
    }
}

void Graf::inserirAresta(int posNode1, int posNode2)
{
    m_matriuAdj[posNode1][posNode2] = 1;
    m_matriuAdj[posNode2][posNode1] = 1;
}

void Graf::eliminarAresta(int posNode1, int posNode2)
{
    m_matriuAdj[posNode1][posNode2] = 0;
    m_matriuAdj[posNode2][posNode1] = 0;
}

void Graf::afegirNode(const std::string& node)
{
    //m_nodes.resize(m_numNodes);
    m_nodes.push_back(node);

    // add a row
    m_matriuAdj.push_back(std::vector<int>(m_numNodes));

    m_numNodes++;

    //m_matriuAdj.resize(m_numNodes);
    for (int i = 0; i < m_numNodes; i++) m_matriuAdj[i].push_back(0);
}

void Graf::eliminarNode(const std::string& node)
{
    //busquem la posició del node a esborrar
    std::vector<std::string>::iterator it;
    
    it = std::find(m_nodes.begin(), m_nodes.end(), node);

    //eliminem el node del vector de nodes i de la matriu d'adjacència
    if (it != m_nodes.end())
    {
        size_t pos = distance(m_nodes.begin(), it);
        // eliminem el node del vector de nodes
        m_nodes.erase(m_nodes.begin() + pos);

        // eliminem la fila i la columna de la matriu d'adjacència corresponents
        // a aquest node
        m_matriuAdj.erase(m_matriuAdj.begin() + pos);

        for (int i = 0; i < m_numNodes; i++)
        {
            m_matriuAdj[i].erase(m_matriuAdj[i].begin() + pos);
        }
        m_numNodes--;
    }
}

std::vector<std::vector<int>> Graf::cicles()
{
    std::vector<std::vector<int>> parades_cicles;

    // TODO IMPLEMENTAR
    for(int i = 0; i < m_numNodes; ++i){
        for(int j = i+1; j < m_numNodes; ++j){
            if(m_matriuAdj[i][j]==1){
                for(int m = j+1; m < m_numNodes; ++m){
                    if(m_matriuAdj[i][m]==1 && m_matriuAdj[j][m]==1){
                        parades_cicles.push_back({i,j,m});
                    }
                }
            }
        }
    }

    return parades_cicles;
}

void Graf::mostra()
{
    int mida_c = 4;
    // imprimim el nom dels vèrtexs
    std::cout << std::setw(mida_c) << " ";
    for (size_t j = 0; j < m_numNodes; j++)
    {
        std::cout << std::setw(mida_c) << m_nodes[j] << " ";
    }
    std::cout << std::endl;

    for (size_t i = 0; i < m_numNodes; i++)
    {
        std::cout << std::setw(10) << m_nodes[i] << " ";
        for (size_t j = 0; j < m_numNodes; j++)
        {
            std::cout << std::setw(mida_c) << m_matriuAdj[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

