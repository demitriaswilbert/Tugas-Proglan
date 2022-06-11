#ifndef __TENDIK_HPP__
#define __TENDIK_HPP__

#include <bits/stdc++.h>
#include "include/person.h"


class Tendik : public person {
private:
	std::string npp;
	std::string unit;

public:
	Tendik(std::string id, std::string nama, const std::string& tglLahir, std::string npp, std::string unit);

	void setUnit(std::string unit);
	std::string getUnit();	
	std::string getNPP();	
};

bool operator < (const Tendik& a, const Tendik& b);
bool operator < (const Tendik& a, const std::string& b);
bool operator < (const std::string& a, const Tendik& b);

#endif
