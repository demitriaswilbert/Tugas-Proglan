#include <bits/stdc++.h>
#include "include/kelas.h"
#include "include/dosen.h"

void Dosen::setPendidikan(int pendidikan)
{
	this->pendidikan = pendidikan;
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

std::ostream& operator << (std::ostream& os, Dosen& dsn) {
    os << "Dosen( " << (person&)dsn << ", NRP: " << dsn.getNPP() << ", Dept: " 
                        << dsn.getDept() << ", Pendidikan: " << dsn.getPendidikan() << ", Kelas Sekarang: {";
    const std::set<Kelas *>& ref = dsn.getAllKelas();
    std::set<Kelas*>::iterator it = ref.begin();
    for(; it != ref.end(); ++it) {
        if(it != ref.begin()) 
            os << ", ";
        os << (*it)->getId();
    }
    if(it == ref.begin())
        os << "Belum Mempunyai Kelas";
    os << "})";
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
