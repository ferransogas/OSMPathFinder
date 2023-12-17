#ifndef GRAF_SOLUCIO_H
#define GRAF_SOLUCIO_H

#include <vector>
#include <string>
#include <cstdio>

class Graf
{
public:
    Graf();
    Graf(const std::vector<std::string>& nodes, const std::vector<std::vector<int>>& parelles_nodes);
    ~Graf();

    size_t getNumNodes() { return m_numNodes; }
    void setNumNodes(int numNodes) { m_numNodes = numNodes; }
    
    void inserirAresta(int posNode1, int posNode2);
    void eliminarAresta(int posNode1, int posNode2);

    void afegirNode(const std::string& node);
    void eliminarNode(const std::string& node);

    std::vector<std::vector<int>> cicles();
    void mostra();

private:
    void crearMatriu(const std::vector<std::vector<int>>& parelles);

protected:
    std::vector<std::string> m_nodes;
    std::vector<std::vector<int>> m_matriuAdj;
    size_t m_numNodes;
    size_t m_numArestes;
};

#endif //GRAF_SOLUCIO_H

