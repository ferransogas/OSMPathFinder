#pragma once
#include "PuntDeInteresBase.h"

class PuntDeInteresRestaurantSolucio : public PuntDeInteresBase
{
private:
	std::string m_cuisine;
	bool m_wheelchair;

public:
	PuntDeInteresRestaurantSolucio() : m_cuisine("undefinit"), m_wheelchair(false) {}
	PuntDeInteresRestaurantSolucio(Coordinate coord, std::string nom="undefinit", std::string cuisine = "undefinit", bool wheelchair = false) : PuntDeInteresBase(coord, nom), m_cuisine(cuisine), m_wheelchair(wheelchair) {}
	
	std::string getName() { return PuntDeInteresBase::getName(); }
	unsigned int getColor() {
		if (m_cuisine == "pizza" && m_wheelchair) return 0x03FCBA;
		else if (m_cuisine == "chinese") return 0xA6D9F7;
		else if (m_wheelchair) return 0x251351;
		else return PuntDeInteresBase::getColor();
	}
};

