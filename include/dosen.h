#ifndef __DOSEN_HPP__
#define __DOSEN_HPP__

#include <bits/stdc++.h>
#include "include/person.h"

class Kelas;

class Dosen : public person {
private:
	std::string npp;
	std::string departemen;
	int pendidikan;
    std::set<Kelas*> kelas;

public:
	Dosen(const std::string& id, const std::string& nama, const std::string& tglLahir, const std::string& npp, const std::string& departemen, int pendidikan) :
        person(id, nama, tglLahir), npp(npp), departemen(departemen), pendidikan(pendidikan) {};

    const std::string& getNPP() {return this->npp;}
    const std::string& getDept() {return this->departemen;}
    const std::set<Kelas*>& getAllKelas() {return this->kelas;}
    
    int getPendidikan() {return this->pendidikan;}
	void setPendidikan(int pendidikan);

    bool enroll(Kelas& rKelas);
    bool unenroll(Kelas& rKelas);
    ~Dosen();
};

std::ostream& operator << (std::ostream& os, Dosen& dsn);
bool operator < (const Dosen& a, const Dosen& b);
bool operator < (const Dosen& a, const std::string& b);
bool operator < (const std::string& a, const Dosen& b);

#endif 
