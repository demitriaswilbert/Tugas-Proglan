#include "include/kelas.h"
#include "include/matkul.h"
#include "include/mahasiswa.h"
#include "include/dosen.h"


Mahasiswa* Kelas::getMhsById(const std::string& id) const {
    for(Mahasiswa* i : recMhs) {
        if (i->getId() == id)
            return i;
    }
    return NULL;
}
Dosen* Kelas::getDosenById(const std::string& id) const {
    for(Dosen* i : recDosen) {
        if (i->getId() == id)
            return i;
    }
    return NULL;
}


bool Kelas::setMatkul(Matkul& rMatkul) {
    if (this->matkul != &rMatkul) {
        if (this->matkul != NULL) {
            this->matkul->removeKelas(*this);
        }
        this->matkul = &rMatkul;
        rMatkul.addKelas(*this);
        return true;
    }
    return false;
}

bool Kelas::removeMatkul() {
    if (this->matkul != NULL) {
        this->matkul->removeKelas(*this);
        this->matkul = NULL;
        return true;
    }
    return false;
}


bool Kelas::addMhs(Mahasiswa& rMhs) {
    if(this->recMhs.find(&rMhs) == this->recMhs.end()) {
        this->recMhs.insert(&rMhs);
        rMhs.enroll(*this);
        return true;
    }
    return false;
}

bool Kelas::removeMhs(Mahasiswa& rMhs) {
    if(this->recMhs.find(&rMhs) != this->recMhs.end()) {
        this->recMhs.erase(&rMhs);
        rMhs.unenroll(*this);
        return true;
    }
    return false;
}

bool Kelas::addDosen(Dosen& rDosen) {
    if(this->recDosen.find(&rDosen) == this->recDosen.end()) {
        this->recDosen.insert(&rDosen);
        rDosen.enroll(*this);
        return true;
    }
    return false;
}
bool Kelas::removeDosen(Dosen& rDosen) {
    if(this->recDosen.find(&rDosen) != this->recDosen.end()) {
        this->recDosen.erase(&rDosen);
        rDosen.unenroll(*this);
        return true;
    }
    return false;
}

std::ostream& operator << (std::ostream& os, const Kelas& kls) {
    os << "Kelas( id: " << kls.getId() << ", Dosen: {"
       << printIdPtr(kls.getRecDosen().begin(), kls.getRecDosen().end()) 
       << "}, Mahasiswa: {"
       << printIdPtr(kls.getRecMhs().begin(), kls.getRecMhs().end()) << "})";
    return os;
}

bool operator < (const Kelas& a, const Kelas& b) {
    return ((Kelas&)a).getId() < ((Kelas&)b).getId();
}

bool operator < (const Kelas& a, const std::string& b) {
    return ((Kelas&)a).getId() < b;
}
bool operator < (const std::string& a, const Kelas& b) {
    return a < ((Kelas&)b).getId();
}

Kelas::~Kelas() {
	for(Mahasiswa *const i : this->recMhs)
        { this->removeMhs(*i); }
	for(Dosen *const i : this->recDosen)
        { this->removeDosen(*i); }
    this->removeMatkul();
}