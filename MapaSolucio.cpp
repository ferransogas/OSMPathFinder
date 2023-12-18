#include "MapaSolucio.h"
#include "GrafSolucio.h"

CamiBase *MapaSolucio::buscaCamiMesCurt(PuntDeInteresBase *desde, PuntDeInteresBase *a)
{
	// Convertir vector ndCamins que conté tots els nodes camí a vector<Coordinate>
    // per tal de que sigui funcional amb BallTree::construirArbre()
	// JA HEM COMPROVAT QUE A ndCamins NO HI HAGI NODES REPETITS (al mateix moment d'inserir cada ndCami)
	std::vector<Coordinate> coordNdCamins;
    for (auto &it : ndCamins)
    {
        coordNdCamins.push_back(it.c);
    }

	// Crear BallTree dels nodes camí obtinguts en el vector i guardats a ndCamins
	BallTree btNodes;
	btNodes.construirArbre(coordNdCamins);

	// 1. BallTree per trobar node camí més proper a desde
	Coordinate Qdesde;
	Qdesde = btNodes.nodeMesProper(desde->getCoord(), Qdesde, btNodes.getArrel());

	// 2. BallTree per trobar node camí més proper a a
	Coordinate Qa;
	Qa = btNodes.nodeMesProper(a->getCoord(), Qa, btNodes.getArrel());

	// 3. Buscar camí més curt amb dijkstra a m_grafNodesCami
	std::vector<Coordinate> camiCurt = m_grafNodesCami.camiCurt(Qdesde, Qa);

	return new CamiSolucio(camiCurt);
}
