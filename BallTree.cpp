#include "BallTree.h"

void BallTree::construirArbre(const std::vector<Coordinate> &coordenades)
{
    if (coordenades.empty())
        return;

    // Si només hi ha 1 coordenada, aquella és m_pivot
    if (coordenades.size() == 1)
    {
        m_pivot = coordenades[0];
        return;
    }

    // Calcular la coordenada punt central (punt C) del vector coordenades
    m_coordenades = coordenades;
    m_pivot = Util::calcularPuntCentral(m_coordenades);

    // Calcular totes les distàncies desde els nodes fins al punt C i obtenir el més llunyà (punt A)
    Coordinate puntA = getNodeLlunya(m_coordenades, m_pivot);

    // Calcular totes les distàncies desde els nodes fins al punt A i obtenir el més llunyà (punt B)
    Coordinate puntB = getNodeLlunya(m_coordenades, puntA);

    // Asignar nodes al fill esquerre o dret en funció de la seva distància de punt A i B
    std::vector<Coordinate> leftNodes, rightNodes;
    for (const auto &coord : m_coordenades)
    {
        double d1 = Util::DistanciaHaversine(coord, puntA);
        double d2 = Util::DistanciaHaversine(coord, puntB);

        if (d1 < d2)
            leftNodes.push_back(coord);
        else
            rightNodes.push_back(coord);

        m_radi = std::max(d1, d2); // Actualitzar el radi de la bola que conté tots els punts
    }

    // Construir arbres a esquerra i dreta recursivament
    if (!leftNodes.empty())
    {
        // Crear BallTree per m_left
        m_left = new BallTree();

        // Assignar com a root el BallTree arrel
        if (m_root == nullptr)
            m_left->setArrel(this);
        else
            m_left->setArrel(this->m_root);

        // Construir BallRoot per leftNodes
        m_left->construirArbre(leftNodes);
    }
    if (!rightNodes.empty())
    {
        m_right = new BallTree();
        if (m_root == nullptr)
            m_right->setArrel(this);
        else
            m_right->setArrel(this->m_root);
        m_right->construirArbre(rightNodes);
    }

    if (m_root == nullptr)
        m_root = this;
}

void BallTree::inOrdre(std::vector<std::list<Coordinate>> &out)
{
    inOrdre(m_root, out);
}
void BallTree::preOrdre(std::vector<std::list<Coordinate>> &out)
{
    preOrdre(m_root, out);
}

void BallTree::postOrdre(std::vector<std::list<Coordinate>> &out)
{
    postOrdre(m_root, out);
}

void BallTree::inOrdre(BallTree *node, std::vector<std::list<Coordinate>> &out)
{
    if (node != nullptr)
    {
        inOrdre(node->m_left, out);

        std::list<Coordinate> coordinateList;
        for (auto coord : node->m_coordenades)
        {
            coordinateList.push_back(coord);
        }
        out.push_back(coordinateList);

        inOrdre(node->m_right, out);
    }
}
void BallTree::preOrdre(BallTree *node, std::vector<std::list<Coordinate>> &out)
{
    if (node != nullptr)
    {
        std::list<Coordinate> coordinateList;
        for (auto coord : node->m_coordenades)
        {
            coordinateList.push_back(coord);
        }
        out.push_back(coordinateList);

        preOrdre(node->m_left, out);

        preOrdre(node->m_right, out);
    }
}
void BallTree::postOrdre(BallTree *node, std::vector<std::list<Coordinate>> &out)
{
    if (node != nullptr)
    {
        postOrdre(node->m_left, out);

        postOrdre(node->m_right, out);

        std::list<Coordinate> coordinateList;
        for (auto coord : node->m_coordenades)
        {
            coordinateList.push_back(coord);
        }
        out.push_back(coordinateList);
    }
}

Coordinate BallTree::nodeMesProper(Coordinate targetQuery, Coordinate &Q, BallTree *ball)
{
    // TODO: TASCA 3
}

Coordinate BallTree::getNodeLlunya(const std::vector<Coordinate> &coords, const Coordinate &pivot)
{
    double maxDist = 0;
    Coordinate nodeLlunya;
    for (const auto &coord : coords)
    {
        double dist = Util::DistanciaHaversine(coord, pivot);
        if (dist > maxDist)
        {
            maxDist = dist;
            nodeLlunya = coord;
        }
    }
    return nodeLlunya;
}
