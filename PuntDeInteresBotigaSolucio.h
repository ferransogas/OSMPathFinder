#pragma once
#include "PuntDeInteresBase.h"
class PuntDeInteresBotigaSolucio : public PuntDeInteresBase
{
private:
	std::string m_shop;
	std::string m_opening_hours;
	bool m_wheelchair;

	bool getOpeningHours(std::string hours) {
		int pos = m_opening_hours.find(hours);
		if (pos == std::string::npos) return false;
		else return true;
	}

public:
	PuntDeInteresBotigaSolucio() : m_shop("undefinit"), m_opening_hours("undefinit"), m_wheelchair(false) {}
	PuntDeInteresBotigaSolucio(Coordinate coord, std::string nom="undefinit", std::string shop = "undefinit", std::string opening_hours = "undefinit", bool wheelchair = false) : PuntDeInteresBase(coord, nom), m_shop(shop), m_opening_hours(opening_hours), m_wheelchair(wheelchair) {}
	
	std::string getName() { return PuntDeInteresBase::getName(); }
	unsigned int getColor() {
		if (m_shop == "supermarket") return 0xA5BE00;
		else if (m_shop == "tobacco") return 0xFFAD69;
		else if (m_shop == "bakery" && m_wheelchair && getOpeningHours("06:00-22:00")) return 0x4CB944;
		else if (m_shop == "bakery") return 0xE85D75;
		else return 0xEFD6AC;
	}
};


