#include "BallTree.h"

void BallTree::construirArbre(const std::vector<Coordinate> &coordenades)
{

    
    // Assignar les coordenades que existeixen dins de la bola
    m_coordenades = coordenades;

    if (m_coordenades.empty())
        return;

    // Si només hi ha 1 coordenada, aquella és m_pivot
    if (m_coordenades.size() == 1)
    {
        m_pivot = coordenades[0];
        return;
    }

    // Calcular la coordenada punt central (punt C) del vector coordenades
    m_pivot = Util::calcularPuntCentral(m_coordenades);

    // Calcular totes les distàncies desde els nodes fins al punt C i obtenir el més llunyà (punt A)
    Coordinate puntA = getNodeLlunya(m_coordenades, m_pivot);
    // El radi de cada bola és la seva distància entre pivot i punt més llunyà
    m_radi = Util::DistanciaHaversine(puntA, m_pivot);

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

    }

    // Construir arbres a esquerra i dreta recursivament
    if (!leftNodes.empty())
    {
        // Crear BallTree per m_left
        m_left = new BallTree();

        // Assignar com a root el BallTree arrel
        m_left->setArrel(this);

        // Construir BallRoot per leftNodes
        m_left->construirArbre(leftNodes);
    }
    if (!rightNodes.empty())
    {
        m_right = new BallTree();
        m_right->setArrel(this);
        m_right->construirArbre(rightNodes);
    }

    if (m_root == nullptr)
        m_root = this;
}

void BallTree::inOrdre(std::vector<std::list<Coordinate>> &out)
{
    inOrdre(m_root, out);
}
void BallTree::inOrdre(BallTree *node, std::vector<std::list<Coordinate>> &out)
{
    if (node != nullptr)
    {
        if (m_left != nullptr)
        {
            inOrdre(node->m_left, out);
        }

        std::list<Coordinate> llistaCoords;
        for (auto it = node->m_coordenades.begin(); it != node->m_coordenades.end(); ++it)
        {
            llistaCoords.push_back(*it);
        }
        out.push_back(llistaCoords);

        if (m_right != nullptr)
        {
            inOrdre(node->m_right, out);
        }
    }
}

void BallTree::preOrdre(std::vector<std::list<Coordinate>> &out)
{
    preOrdre(m_root, out);
}
void BallTree::preOrdre(BallTree *node, std::vector<std::list<Coordinate>> &out)
{

    if (node != nullptr)
    {
        std::list<Coordinate> llistaCoords;
        for (auto it = node->m_coordenades.begin(); it != node->m_coordenades.end(); ++it)
        {
            llistaCoords.push_back(*it);
        }
        out.push_back(llistaCoords);

        if (m_left != nullptr)
        {
            preOrdre(node->m_left, out);
        }

        if (m_right != nullptr)
        {
            preOrdre(node->m_right, out);
        }
    }
}

void BallTree::postOrdre(std::vector<std::list<Coordinate>> &out)
{
    postOrdre(m_root, out);
}
void BallTree::postOrdre(BallTree *node, std::vector<std::list<Coordinate>> &out)
{
    if (node != nullptr)
    {
        if (m_left != nullptr)
        {
            postOrdre(node->m_left, out);
        }

        if (m_right != nullptr)
        {
            postOrdre(node->m_right, out);
        }

        std::list<Coordinate> llistaCoords;
        for (auto it = node->m_coordenades.begin(); it != node->m_coordenades.end(); ++it)
        {
            llistaCoords.push_back(*it);
        }
        out.push_back(llistaCoords);
    }
}

Coordinate BallTree::nodeMesProper(Coordinate targetQuery, Coordinate &Q, BallTree *ball)
{
    if (ball == m_root)
    {
        Q = Coordinate{0, 0};
    }

    double D1 = Util::DistanciaHaversine(ball->m_pivot, targetQuery);
    double D2 = Util::DistanciaHaversine(ball->m_pivot, Q);

    if (D1 - ball->m_radi >= D2)
    {
        return Q;
    }

    // Si la bola és una fulla
    if (ball->m_left == nullptr && ball->m_right == nullptr)
    {
        for (auto &coord : ball->m_coordenades)
        {
            if (Util::DistanciaHaversine(targetQuery, coord) < Util::DistanciaHaversine(targetQuery, Q))
            {
                Q = coord;
            }
        }
        return Q;
    }

    double Da = ball->m_left ? Util::DistanciaHaversine(targetQuery, ball->m_left->m_pivot) : std::numeric_limits<double>::max();
    double Db = ball->m_right ? Util::DistanciaHaversine(targetQuery, ball->m_right->m_pivot) : std::numeric_limits<double>::max();

    if (Da < Db)
    {
        Q = nodeMesProper(targetQuery, Q, ball->m_left);
        Q = nodeMesProper(targetQuery, Q, ball->m_right);
    }
    else
    {
        Q = nodeMesProper(targetQuery, Q, ball->m_right);
        Q = nodeMesProper(targetQuery, Q, ball->m_left);
    }
    return Q;
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