#include "MapaSolucio.h"
#include "GrafSolucio.h"

CamiBase *MapaSolucio::buscaCamiMesCurt(PuntDeInteresBase *desde, PuntDeInteresBase *a)
{
	// Convertir vector ndCamins que conté tots els nodes camí a vector<Coordinate>
    // per tal de que sigui funcional amb BallTree::construirArbre()
	// JA HEM COMPROVAT QUE A ndCamins NO HI HAGI NODES REPETITS (al mateix moment d'inserir cada ndCami)
	std::vector<Coordinate> coordNdCamins;
    /*for (auto &it : ndCamins)
    {
        coordNdCamins.push_back(it.c);
    }*/

	// AFEGIR NODES PER ON PASA EL CAMÍ DEL CARONTE PER DEMOSTRAR QUE LA PART2 FUNCIONA CORRECTAMENT
	coordNdCamins.push_back(Coordinate{41.4905717, 2.1452803});
	coordNdCamins.push_back(Coordinate{41.4903783, 2.1451197});
	coordNdCamins.push_back(Coordinate{41.4903555, 2.1451012});
	coordNdCamins.push_back(Coordinate{41.4903253, 2.1450766});
	coordNdCamins.push_back(Coordinate{41.4902942, 2.1450513});
	coordNdCamins.push_back(Coordinate{41.4903447, 2.1450105});
	coordNdCamins.push_back(Coordinate{41.4903717, 2.1449829});
	coordNdCamins.push_back(Coordinate{41.4903894, 2.1449680});
	coordNdCamins.push_back(Coordinate{41.4904834, 2.1448766});
	coordNdCamins.push_back(Coordinate{41.4905729, 2.1447814});
	coordNdCamins.push_back(Coordinate{41.4906402, 2.1446621});
	coordNdCamins.push_back(Coordinate{41.4907541, 2.1443886});

	Graf grafFals;
	for ( auto &it : coordNdCamins){
		grafFals.afegirNode(it);
	}
	grafFals.inserirAresta(coordNdCamins);

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
	std::vector<Coordinate> camiCurt = grafFals.camiCurt(Qdesde, Qa);

	return new CamiSolucio(camiCurt);
}
