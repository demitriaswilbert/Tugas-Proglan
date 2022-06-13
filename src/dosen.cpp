#include <bits/stdc++.h>
#include "include/kelas.h"
#include "include/dosen.h"

void Dosen::setPendidikan(int pendidikan)
{
	this->pendidikan = pendidikan;
}

Dosen::~Dosen() {
	for(Kelas *const i : this->kelas)
        { this->unenroll(*i); }
}

bool Dosen::enroll(Kelas& rKelas) 
{
    if(this->kelas.find(&rKelas) == this->kelas.end()) {
        this->kelas.insert(&rKelas);
        rKelas.addDosen(*this);
        return true;
    }
    return false;
}

bool Dosen::unenroll(Kelas& rKelas) 
{
    if(this->kelas.find(&rKelas) != this->kelas.end()) {
        this->kelas.erase(&rKelas);
        rKelas.removeDosen(*this);
        return true;
    }
    return false;
}

std::ostream& operator << (std::ostream& os, const Dosen& dsn) {
    os << "Dosen( " << (person&)dsn << ", NRP: " << dsn.getNPP() << ", Dept: " 
                        << dsn.getDept() << ", Pendidikan: " << dsn.getPendidikan() << ", Kelas Sekarang: {";
    os << printIdPtr(dsn.getAllKelas().begin(), dsn.getAllKelas().end()) << "})";
    return os;
}


bool operator < (const Dosen& a, const Dosen& b) {
    return ((person&)a).getId() < ((person&)b).getId();
}

bool operator < (const Dosen& a, const std::string& b) {
    return ((person&)a).getId() < b;
}
bool operator < (const std::string& a, const Dosen& b) {
    return a < ((person&)b).getId();
}
