#ifndef MATKUL_HPP
#define MATKUL_HPP

#include <bits/stdc++.h>

class Kelas;

class Matkul {
    private:
    std::string id;
    float sks;

    std::set<Kelas*, std::less<>> recKelas;
    
    public:
    Matkul(const std::string& id, float sks) : id(id), sks(sks) { }

    void setId(const std::string& aId) {id = aId;}
    const std::string& getId() {return id;}

    void setSKS(float sks) {this->sks = sks;}
    float getSKS() {return this->sks;}

    bool addKelas(Kelas& rKelas);
    bool removeKelas(Kelas& rKelas);

    std::set<Kelas*, std::less<>>& getRecKelas() {return recKelas;}

    
    bool operator==(Matkul& other) { return this->id == other.getId(); }
    bool operator>(Matkul& other) { return this->id > other.getId(); }
    bool operator<(Matkul& other) { return this->id < other.getId(); }
    bool operator>(const std::string& other) { return this->id > other; }
    bool operator<(const std::string& other) { return this->id < other; }

    ~Matkul();

};

bool operator < (const Matkul& a, const Matkul& b);
std::ostream& operator << (std::ostream& os, Matkul& mkl);
bool operator < (const Matkul& a, const std::string& b);
bool operator < (const std::string& a, const Matkul& b);

#endif // MATKUL_HPP