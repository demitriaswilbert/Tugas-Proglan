#include <bits/stdc++.h>
#include "include/person.h"

void person::setId(const std::string& id)
{
	this->id = id;
}

const std::string& person::getId() 
{
	return this->id;
}

void person::setNama(const std::string& nama)
{
	this->nama = nama;
}

const std::string& person::getNama()
{
	return this->nama;
}

void person::setTglLahir(const std::string& TglLahir)
{
	this->tglLahir = TglLahir;
}

const std::string& person::getTglLahir()
{
	return this->tglLahir;
}

bool operator < (const person& a, const person& b) {
    return ((person&)a).getId() < ((person&)b).getId();
}
bool operator < (const person& a, const std::string& b) {
    return ((person&)a).getId() < b;
}
bool operator < (const std::string& a, const person& b) {
    return a < ((person&)b).getId();
}


