#include "include/matkul.h"
#include "include/kelas.h"
#include "include/mahasiswa.h"
#include "include/dosen.h"

bool Matkul::addKelas(Kelas& kelas) {
    if(this->recKelas.find(&kelas) == this->recKelas.end()) {
        this->recKelas.insert(&kelas);
        kelas.setMatkul(*this);
        return true;
    }
    return false;
}

bool Matkul::removeKelas(Kelas& kelas) {
    if(this->recKelas.find(&kelas) != this->recKelas.end()) {
        this->recKelas.erase(&kelas);
        kelas.removeMatkul();
        return true;
    }
    return false;
}

bool operator < (const Matkul& a, const Matkul& b) {
    return ((Matkul&)a).getId() < ((Matkul&)b).getId();
}
std::ostream& operator << (std::ostream& os, Matkul& mkl) {
    os  << "Matkul( ID: " << mkl.getId() << ", SKS: " << mkl.getSKS() 
        << ", Kelas: {";
}
bool operator < (const Matkul& a, const std::string& b) {
    return ((Matkul&)a).getId() < b;
}
bool operator < (const std::string& a, const Matkul& b) {
    return a < ((Matkul&)b).getId();
}

Matkul::~Matkul() {
    for(Kelas* i : this->getRecKelas()) {
        i->removeMatkul();
    }
}