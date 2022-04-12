#include <iostream>
#include <vector>
#include "include/mahasiswa.hpp"


mahasiswa::mahasiswa(std::string id, std::string nama, int dd, int mm, int yy, 
				std::string nrp, std::string departemen, int tahunmasuk)
		: person(id, nama, dd, mm, yy), nrp(nrp), departemen(departemen), tahunmasuk(tahunmasuk)
{
	this->ipk = 0.0;
	this->semesterke = 1;
	this->skslulus = 0;

	this->ips = std::vector<float>(14,0);
}

void mahasiswa::setSemester(int semesterke)
{
	this->semesterke = semesterke;
}

int mahasiswa::getSemester()
{
	return this->semesterke;
}

void mahasiswa::setSKSLulus(int skslulus)
{
	this->skslulus = skslulus;
}

int mahasiswa::getSKSLulus()
{
	return this->skslulus;
}

void mahasiswa::hitungIPK()
{
    float sum = 0.0f;
    for(int i = 1; i < this->semesterke; i++)
    {
        sum += (float)(this->ips[i-1]) / (this->semesterke-1);
    }
    this->ipk = sum;
}

void mahasiswa::setIPS(int semester, float ips)
{
	// semester mulai dari 1
	if (semester < 15 && semester > 0) {
		this->ips[semester-1] = ips;
		this->hitungIPK();
	}
}

float mahasiswa::getIPS(int semester)
{
	if (semester < 15 && semester > 0)
		return this->ips[semester-1];

	return -1.0;
}

float mahasiswa::getIPK()
{
	return this->ipk;
}

std::vector<float> mahasiswa::getAllIPS()
{
	return this->ips;
}

std::string mahasiswa::getNRP()
{
    return this->nrp;
}

std::string mahasiswa::getDept()
{
    return this->departemen;
}

int mahasiswa::getThnMsk()
{
    return this->tahunmasuk;
}



