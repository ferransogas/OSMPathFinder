#pragma once
#include "CamiBase.h"
class CamiSolucio : public CamiBase
{
private:
	std::vector<Coordinate> m_cami;
public:
	CamiSolucio() {
		/*Coordinate c;
		float lat[4] = { 41.4928803,41.4929072,41.4933070,41.4939882 };
		float lon[4] = { 2.1452381 ,2.1452474 ,2.1453852 ,2.1456419 };
		for (int i = 0; i < 4; ++i) {
			c.lat = lat[i];
			c.lon = lon[i];
			m_cami.push_back(c);
		}*/
	}
	CamiSolucio(std::vector<Coordinate> cami) {
		for (auto it = cami.begin(); it != cami.end(); ++it) {
			Coordinate c;
			c.lat = it->lat;
			c.lon = it->lon;
			m_cami.push_back(c);
		}
	}

	std::vector<Coordinate> getCamiCoords() {
		return m_cami;
	}
};

