#pragma once
#include "MapaBase.h"
#include "PuntDeInteresBotigaSolucio.h"
#include "PuntDeInteresRestaurantSolucio.h"
#include "CamiSolucio.h"
#include "Util.h"
#include "BallTree.h"
#include "GrafSolucio.h"

class MapaSolucio : public MapaBase
{
private:
	typedef struct
	{
		std::string id;
		Coordinate c;
	} ndCami;

	std::vector<PuntDeInteresBase *> m_pdis;
	std::vector<CamiBase *> m_camins;
	std::vector<ndCami> ndCamins;
	Graf m_grafNodesCami;

public:
	MapaSolucio()
	{
		/*Coordinate c; c.lat = 41.4918606; c.lon = 2.1465411;
		m_pdis.push_back(new PuntDeInteresBotigaSolucio(c, "La Millor Caca Pastisseria", "bakery"));

		c.lat = 41.4902204; c.lon = 2.1406477;
		m_pdis.push_back(new PuntDeInteresRestaurantSolucio(c, "El Millor Caca Restaurant", "regional", true));

		m_camins.push_back(new CamiSolucio());*/
	}
	
	void getPdis(std::vector<PuntDeInteresBase *> &pdis)
	{
		// Omplim el vector que es retorna amb el vector que nosaltres tenim omplert
		while (!pdis.empty())
			pdis.pop_back();
		for (auto it = m_pdis.begin(); it != m_pdis.end(); ++it)
		{
			pdis.emplace_back(*it);
		}
		// Buidem el nostre vector perqu� s�n dades que ja hem donat
		auto it = m_pdis.begin();
		while (it != m_pdis.end())
		{
			it = m_pdis.erase(it);
		}
	}

	void getCamins(std::vector<CamiBase *> &camins)
	{
		while (!camins.empty())
			camins.pop_back();
		for (auto it = m_camins.begin(); it != m_camins.end(); ++it)
		{
			camins.emplace_back(*it);
		}
		auto it = m_camins.begin();
		while (it != m_camins.end())
		{
			it = m_camins.erase(it);
		}
	}
	void parsejaXmlElements(std::vector<XmlElement> &xmlElements)
	{
		// COMEN�AR MIRANT SI �S NODE O WAY
		// SI �S NODE AGAFAR COORD I MIREM SI �S NODE INTERES O NODE CAMI
		// SI �S CAMI EL GUARDEM AMB HASH OBERT AMB EL SEU ID
		// SI �S INTERES MIREM SI �S SHOP O AMENITY
		// SI �S SHOP, NOU PDIBS, SI ES AMENITY, NOU PDIRS
		// SI �S WAY, MIREM QUE SIGUI HIGHWAY I BUSQUEM ELS NODES GUARDATS AMB EL ID CORRESPONENT I FEM UN CAMISOLUCIO

		for (auto it = xmlElements.begin(); it != xmlElements.end(); ++it)
		{

			// MIRAR SI �S NODE O WAY
			if ((*it).id_element == "node")
			{
				// SI �S NODE AGAFAR COORD I MIRAR SI T� ATRIBUT NAME
				Coordinate c;
				std::string id;
				for (int i = 0; i < (*it).atributs.size(); i++)
				{
					if ((*it).atributs[i].first == "lat")
						c.lat = std::stod((*it).atributs[i].second);
					else if ((*it).atributs[i].first == "lon")
						c.lon = std::stod((*it).atributs[i].second);
					else if ((*it).atributs[i].first == "id")
						id = (*it).atributs[i].second;
				}

				// BUSCAR SI T� NOM ( PER FER MENYS FOR() GUARDEM ALTRES FILLS, SI ELS T�, PEL CAS QUE TINGUI NOM )
				std::string nom = "undefinit";
				std::string tipus = "undefinit";
				std::string opening_hours = "undefinit";
				bool esShop = false;
				bool esRestaurant = false;
				bool esCami = false;
				bool wheelchair = false;
				for (int i = 0; i < (*it).fills.size() && !esCami; i++)
				{
					if ((*it).fills[i].first == "tag")
					{
						std::pair<std::string, std::string> tagValor = Util::kvDeTag((*it).fills[i].second);
						// SI �S NODE CAM� FEM BREAK
						if (tagValor.first == "highway" || tagValor.first == "public_transport" || tagValor.first == "entrance" || tagValor.first == "access")
							esCami = true;
						// SI T� NOM, EL GUARDEM
						else if (tagValor.first == "name")
							nom = tagValor.second;
						// PERMET WHEELCHAIR?
						else if (tagValor.first == "wheelchair")
						{
							if (tagValor.second == "yes")
								wheelchair = true;
						}
						// �S SHOP, RESTAURANT O RES? si �s shop opening_hours i tipus=tipus de shop, si �s restaurant tipus=tipus de cuisine
						else if (tagValor.first == "shop")
						{
							esShop = true;
							tipus = tagValor.second;
						}
						else if (tagValor.first == "amenity")
						{
							if (tagValor.second == "restaurant")
								esRestaurant = true;
						}
						else if (tagValor.first == "cuisine")
							tipus = tagValor.second;
						else if (tagValor.first == "opening_hours")
							opening_hours = tagValor.second;
					}
				}

				// NODE DE CAM� SON NODES SENSE NOM, SENSE TAGS(EQUIVAL A SENSE NOM), O AMB TAGS ESPECIFICS(bool esCami)
				if (nom == "undefinit" || esCami)
				{
					ndCami nd;
					nd.id = id;
					nd.c.lat = c.lat;
					nd.c.lon = c.lon;

					bool repetit = false;				// COMPROVAR QUE NO INSERIM NODES REPETITS
					for (auto& it : ndCamins) {
						if (it.c.lat == nd.c.lat && it.c.lon == nd.c.lon) {
							repetit = true;
							break;
						}
					}
					if (!repetit) {
						ndCamins.push_back(nd);			  // AFEGIM NODE CAMI AL VECTOR ndCamins PER POSTERIORMENT TROBAR-LOS QUAN UN <way> ELS NECESSITI
						m_grafNodesCami.afegirNode(nd.c); // Afegim el node camí al graf de nodes cami
					}
				}

				// NODE DE INTER�S S�N ELS QUE TENEN NOM I NO SON CAMI, PER� NMES BUSQUEM QUE SIGUIN SHOP O AMENITY RESTAURANT
				else if (esShop)
					m_pdis.push_back(new PuntDeInteresBotigaSolucio(c, nom, tipus, opening_hours, wheelchair));
				else if (esRestaurant)
					m_pdis.push_back(new PuntDeInteresRestaurantSolucio(c, nom, tipus, wheelchair));
			}
			else if ((*it).id_element == "way")
			{
				// SI �S WAY MIREM QUE SIGUI HIGHWAY
				bool esHighway = false;
				for (int i = 0; i < (*it).fills.size() && !esHighway; i++)
				{
					if ((*it).fills[i].first == "tag")
					{
						std::pair<std::string, std::string> tagValor = Util::kvDeTag((*it).fills[i].second);
						if (tagValor.first == "highway")
							esHighway = true;
					}
				}
				if (esHighway)
				{
					// CREEM UN VECTOR DE COORDENADES I BUSQUEM TOTS ELS NODES REFERITS ALS FILLS
					std::vector<Coordinate> c;
					std::string ref;
					for (int i = 0; i < (*it).fills.size(); i++)
					{
						if ((*it).fills[i].first == "nd")
						{
							// COM AGAFEM EL NUMERO DE REF?
							ref = (*it).fills[i].second[0].second;

							// AGAFAR REF, BUSCAR-LO AL VECTOR NDCAMINS I AFEGIR LES SEVES COORDENADES AL VECTOR C
							bool trobat = false;
							for (auto it = ndCamins.begin(); it != ndCamins.end() && !trobat; ++it)
							{
								if (it->id == ref)
								{
									c.push_back(it->c);
									trobat = true;
								}
							}
						}
					}
					m_grafNodesCami.inserirAresta(c); // Inserir distàncies entre cada parella de nodes del vector com a arestes amb pesos
					m_camins.push_back(new CamiSolucio(c));
				}
			}
		}
	}

	// Metode a implementar de la segona part
	CamiBase * buscaCamiMesCurt(PuntDeInteresBase *desde, PuntDeInteresBase *a);
};

