#ifndef KELAS_HPP
#define KELAS_HPP

#include <bits/stdc++.h>
#include "include/global.h"

class Mahasiswa;
class Dosen;
class Matkul;

class Kelas {
    private:
    std::string id;
    std::set<Mahasiswa*, std::less<>> recMhs;
    std::set<Dosen*, std::less<>> recDosen;
    Matkul* matkul = NULL;
    public:
    Kelas(const std::string& id) : id(id), matkul(NULL) {}

    void setId(const std::string& aId) {id = aId;}
    const std::string& getId() const {return id;}

    bool addMhs(Mahasiswa& rMhs);
    bool removeMhs(Mahasiswa& rMhs);
    std::set<Mahasiswa*, std::less<>>& getRecMhs() const {
        return (std::set<Mahasiswa*, std::less<>>&)recMhs;
    }


    bool setMatkul(Matkul& rMatkul);
    Matkul* getMatkul() const {return matkul;}
    bool removeMatkul();

    bool addDosen(Dosen& rDosen);
    bool removeDosen(Dosen& rDosen);
    std::set<Dosen*, std::less<>>& getRecDosen() const {
        return (std::set<Dosen*, std::less<>>&)recDosen;
    }


    Mahasiswa* getMhsById(const std::string& id) const;
    Dosen* getDosenById(const std::string& id) const;

    
    bool operator==(Kelas& other) { return this->id == other.getId(); }
    bool operator>(Kelas& other) { return this->id > other.getId(); }
    bool operator<(Kelas& other) { return this->id < other.getId(); }
    bool operator>(const std::string& other) { return this->id > other; }
    bool operator<(const std::string& other) { return this->id < other; }

    ~Kelas();

};

bool operator < (const Kelas& a, const Kelas& b);
std::ostream& operator << (std::ostream& os, const Kelas& kls);
bool operator < (const Kelas& a, const std::string& b);
bool operator < (const std::string& a, const Kelas& b);

#endif // KELAS_HPP