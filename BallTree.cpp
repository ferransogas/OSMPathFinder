#include "BallTree.h"

void BallTree::construirArbre(const std::vector<Coordinate> &coordenades)
{
    if (coordenades.empty())
        return;

    // Si només hi ha 1 corrdenada, aquella és m_pivot
    if (coordenades.size() == 1)
    {
        m_pivot = coordenades[0];
        return;
    }

    // Calcular la coordenada punt central (punt C) del vector coordenades
    m_pivot = Util::calcularPuntCentral(coordenades);

    // Calcular totes les distàncies desde els nodes fins al punt C i obtenir el més llunyà (punt A)
    Coordinate puntA = getNodeLlunya(coordenades, m_pivot);

    // Calcular totes les distàncies desde els nodes fins al punt A i obtenir el més llunyà (punt B)
    Coordinate puntB = getNodeLlunya(coordenades, puntA);

    // Asignar nodes al fill esquerre o dret en funció de la seva distància de punt A i B
    std::vector<Coordinate> leftNodes, rightNodes;
    for (const auto &coord : coordenades)
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
    if (!leftNodes.empty()){
        m_left = new BallTree();
        m_left->construirArbre(leftNodes);
    }
    if (!rightNodes.empty())
        m_right = new BallTree();
        m_right->construirArbre(rightNodes);
}

void BallTree::inOrdre(std::vector<std::list<Coordinate>> &out)
{
    // TODO: TASCA 2
}
void BallTree::preOrdre(std::vector<std::list<Coordinate>> &out)
{
    // TODO: TASCA 2
}

void BallTree::postOrdre(std::vector<std::list<Coordinate>> &out)
{
    // TODO: TASCA 2
}

Coordinate BallTree::nodeMesProper(Coordinate targetQuery, Coordinate &Q, BallTree *ball)
{
    // TODO: TASCA 3
}

Coordinate BallTree::getNodeLlunya(const std::vector<Coordinate> &coords, const Coordinate &pivot)
{
    double maxDist = 0;
    Coordinate furthestNode;
    for (const auto &coord : coords)
    {
        double dist = Util::DistanciaHaversine(coord, pivot);
        if (dist > maxDist)
        {
            maxDist = dist;
            furthestNode = coord;
        }
    }
    return furthestNode;
}
