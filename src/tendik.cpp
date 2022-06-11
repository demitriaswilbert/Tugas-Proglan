#include <bits/stdc++.h>
#include "include/tendik.h"


Tendik::Tendik(std::string id, std::string nama, const std::string& tglLahir, std::string npp, std::string unit)
		: person(id, nama, tglLahir), npp(npp), unit(unit)
{
}

void Tendik::setUnit(std::string unit)
{
	this->unit = unit;
}

std::string Tendik::getUnit()
{
	return this->unit;
}


std::string Tendik::getNPP()
{
	return this->npp;
}

bool operator < (const Tendik& a, const Tendik& b) {
    return ((person&)a).getId() < ((person&)b).getId();
}
bool operator < (const Tendik& a, const std::string& b) {
    return ((person&)a).getId() < b;
}
bool operator < (const std::string& a, const Tendik& b) {
    return a < ((person&)b).getId();
}