#ifndef KELAS_HPP
#define KELAS_HPP

#include <bits/stdc++.h>

class Mahasiswa;
class Dosen;

class Kelas {
    private:
    std::string id;
    std::string dept;
    std::set<Mahasiswa*> recMhs;
    std::set<Dosen*> recDosen;
    public:
    Kelas(const std::string& id, const std::string& dept) : id(id), dept(dept) { }

    void setId(const std::string& aId) {id = aId;}
    const std::string& getId() {return id;}

    void setDept(const std::string& aDept) {dept = aDept;}
    const std::string& getDept() {return dept;}


    bool addMhs(Mahasiswa& rMhs);
    bool removeMhs(Mahasiswa& rMhs);
    const std::set<Mahasiswa*>& getRecMhs() {return recMhs;}


    bool addDosen(Dosen& rDosen);
    bool removeDosen(Dosen& rDosen);
    const std::set<Dosen*>& getRecDosen() {return recDosen;}


    Mahasiswa* getMhsById(const std::string& id);
    Dosen* getDosenById(const std::string& id);

    
    bool operator==(Kelas& other) { return this->id == other.getId(); }
    bool operator>(Kelas& other) { return this->id > other.getId(); }
    bool operator<(Kelas& other) { return this->id < other.getId(); }
    bool operator>(const std::string& other) { return this->id > other; }
    bool operator<(const std::string& other) { return this->id < other; }

};

bool operator < (const Kelas& a, const Kelas& b);
std::ostream& operator << (std::ostream& os, Kelas& kls);
bool operator < (const Kelas& a, const std::string& b);
bool operator < (const std::string& a, const Kelas& b);

#endif // KELAS_HPP