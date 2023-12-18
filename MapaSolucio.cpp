#include "MapaSolucio.h"

CamiBase *MapaSolucio::buscaCamiMesCurt(PuntDeInteresBase *desde, PuntDeInteresBase *a)
{

    // Convertir vector ndCamins que conté tots els nodes camí a vector<Coordinate>
    // per tal de que sigui funcional amb BallTree::construirArbre()
    std::vector<Coordinate> coordNdCamins;
    for (auto &it : ndCamins)
    {
        coordNdCamins.push_back(it.c);
    }

    // Crear BallTree dels nodes camí obtinguts en el vector i guardats a ndCamins
    BallTree *btNodes = new BallTree;
    std::vector<Coordinate> hola;
    hola.push_back(Coordinate{1.2,3.4});
    hola.push_back(Coordinate{5.6,7.8});
    hola.push_back(Coordinate{9.0,1.2});

    btNodes->construirArbre(hola); // Si li passo hola, un vector amb poques coordenades, funciona; si li passo coordNdCamins, un vector amb moltes coordeandes, segmentation fault)

    return new CamiSolucio(hola);
}
