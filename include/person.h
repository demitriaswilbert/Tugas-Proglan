#ifndef __PERSON_HPP__
#define __PERSON_HPP__

#include <bits/stdc++.h>
#include <regex>

class person {
private:
	std::string id;
	std::string nama;
	std::string tglLahir;

public:
	person(const std::string& id, const std::string& nama, const std::string& tglLahir) 
        : id(id), nama(nama), tglLahir(tglLahir) {
    }

	void setId(const std::string& id);
	const std::string& getId();

	void setNama(const std::string& nama);
	const std::string& getNama();

    void setTglLahir(const std::string& TglLahir);
    const std::string& getTglLahir();

    bool operator==(person& other) { return this->id == other.getId(); }
    bool operator>(person& other) { return this->id > other.getId(); }
    bool operator<(person& other) { return this->id < other.getId(); }
    bool operator>(const std::string& other) { return this->id > other; }
    bool operator<(const std::string& other) { return this->id < other; }
    friend std::ostream& operator << (std::ostream& os, person& psn) {
        os << "Person( ID: \"" << psn.getId() << "\", Nama: \"" << psn.getNama() << "\", Tgl. Lahir: " << psn.getTglLahir() << " )";
        return os;
    }
};

bool operator < (const person& a, const person& b);
bool operator < (const person& a, const std::string& b);
bool operator < (const std::string& a, const person& b);


#endif
