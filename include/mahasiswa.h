#ifndef __MAHASISWA_HPP__
#define __MAHASISWA_HPP__


#include <bits/stdc++.h>
#include "include/global.h"
#include "include/person.h"

class Kelas;

class Mahasiswa : public person {
private:
	std::string nrp;
	std::string departemen;
	int tahunmasuk;
	int semesterke;
	int skslulus;
	float ipk;
	std::vector<float> ips;
    std::map<Kelas*, float> kelas_nilai;

public:
	Mahasiswa(const std::string& id, const std::string& nama, const std::string& tglLahir, 
					const std::string& nrp, const std::string& departemen, int tahunmasuk);

	void setSemester(int semesterke);
	int getSemester() const;

	void setSKSLulus(int skslulus);
	int getSKSLulus() const;

	const std::string& getNRP() const;
	const std::string& getDept() const;
    int getThnMsk() const;

	void hitungIPK();
    float getIPK() const;

	float getIPS(int semester) const;

    bool enroll(Kelas& rKelas);
    bool unenroll(Kelas& rKelas);


	std::vector<float>& getAllIPS() const;
    std::map<Kelas*, float>& getAllKelas() const;

    ~Mahasiswa();
};

std::ostream& operator << (std::ostream& os, const Mahasiswa& mhs);
bool operator < (const Mahasiswa& a, const Mahasiswa& b);
bool operator < (const Mahasiswa& a, const std::string& b);
bool operator < (const std::string& a, const Mahasiswa& b);

#endif
