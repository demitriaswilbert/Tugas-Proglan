#include <bits/stdc++.h>
#include <vector>
#include "include/kelas.h"
#include "include/mahasiswa.h"


Mahasiswa::Mahasiswa(const std::string& id, const std::string& nama, const std::string& tglLahir, 
				const std::string& nrp, const std::string& departemen, int tahunmasuk)
		: person(id, nama, tglLahir), nrp(nrp), departemen(departemen), tahunmasuk(tahunmasuk)
{
	this->ipk = 0.0;
	this->semesterke = 1;
	this->skslulus = 0;

	this->ips = std::vector<float>(14,0);
}

void Mahasiswa::setSemester(int semesterke)
{
	this->semesterke = semesterke;
}

int Mahasiswa::getSemester()
{
	return this->semesterke;
}

void Mahasiswa::setSKSLulus(int skslulus)
{
	this->skslulus = skslulus;
}

int Mahasiswa::getSKSLulus()
{
	return this->skslulus;
}

void Mahasiswa::hitungIPK()
{
    float sum = 0.0f;
    for(int i = 0; i < this->semesterke; i++)
    {
        sum += (float)(this->ips[i]) / (this->semesterke);
    }
    this->ipk = sum;
}

bool Mahasiswa::enroll(Kelas& rKelas)
{
    if(this->kelas_nilai.find(&rKelas) == this->kelas_nilai.end()) {
        this->kelas_nilai.insert({&rKelas, 0.0f});
        rKelas.addMhs(*this);
        return true;
    }
    return false;
}

bool Mahasiswa::unenroll(Kelas& rKelas)
{
    if(this->kelas_nilai.find(&rKelas) != this->kelas_nilai.end()) {
        this->kelas_nilai.erase(&rKelas);
        rKelas.removeMhs(*this);
        return true;
    }
    return false;
}

float Mahasiswa::getIPS(int semester)
{
	if (semester < 15 && semester > 0)
		return this->ips[semester-1];

	return -1.0;
}

float Mahasiswa::getIPK()
{
	return this->ipk;
}

const std::vector<float>& Mahasiswa::getAllIPS()
{
	return this->ips;
}
const std::map<Kelas*, float>& Mahasiswa::getAllKelas()
{
	return this->kelas_nilai;
}

const std::string& Mahasiswa::getNRP()
{
    return this->nrp;
}

const std::string& Mahasiswa::getDept()
{
    return this->departemen;
}

int Mahasiswa::getThnMsk()
{
    return this->tahunmasuk;
}

bool operator < (const Mahasiswa& a, const Mahasiswa& b) {
    return ((person&)a).getId() < ((person&)b).getId();
}

bool operator < (const Mahasiswa& a, const std::string& b) {
    return ((person&)a).getId() < b;
}
bool operator < (const std::string& a, const Mahasiswa& b) {
    return a < ((person&)b).getId();
}

std::ostream& operator << (std::ostream& os, Mahasiswa& mhs) {
    os << "Mahasiswa( " << (person&)mhs << ", NRP: " << mhs.getNRP() << ", Dept: " 
                        << mhs.getDept() << ", Thn. Masuk: " << mhs.getThnMsk() << ", Semester: " << mhs.getSemester() << ", SKS Lulus: " << mhs.getSKSLulus() << ", IPK: " << mhs.getIPK() << ", IPS: {";
    int i = 0;
    for(; i < mhs.getSemester(); i++) {
        if(i > 0) os << ", ";
        os << mhs.getAllIPS()[i];
    }
    if(i == 0)
        os << "Belum Mempunyai Nilai";
    os << "}, Kelas Sekarang: {";
    const std::map<Kelas *, float>& ref = mhs.getAllKelas();
    std::map<Kelas *, float>::const_iterator it = ref.begin();
    for(; it != ref.end(); ++it) {
        if(it != ref.begin()) os << ", ";
        os << it->first->getId() << ": " << it->second;
    }
    if(it == ref.begin())
        os << "Belum Mempunyai Kelas";
    os << "})";
    return os;
}



