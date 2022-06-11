#ifndef __MAHASISWA_HPP__
#define __MAHASISWA_HPP__


#include <bits/stdc++.h>
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
	int getSemester();

	void setSKSLulus(int skslulus);
	int getSKSLulus();

	const std::string& getNRP();
	const std::string& getDept();
    int getThnMsk();

	void hitungIPK();
    float getIPK();

	float getIPS(int semester);

    bool enroll(Kelas& rKelas);
    bool unenroll(Kelas& rKelas);


	const std::vector<float>& getAllIPS();
    const std::map<Kelas*, float>& getAllKelas();

    
};

std::ostream& operator << (std::ostream& os, Mahasiswa& mhs);
bool operator < (const Mahasiswa& a, const Mahasiswa& b);
bool operator < (const Mahasiswa& a, const std::string& b);
bool operator < (const std::string& a, const Mahasiswa& b);

#endif
