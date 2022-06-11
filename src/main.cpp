
#include <bits/stdc++.h>
#include <regex>

#include "include/dosen.h"
#include "include/kelas.h"
#include "include/mahasiswa.h"
#include "include/person.h"
#include "include/tendik.h"

std::regex regexTglLahir =
    std::regex("(0?[1-9]|[12][0-9]|3[0-1])-(0?[1-9]|1[0-2])-\\d{4}");

void addMhsHandler (
        std::set<Mahasiswa, std::less<>>& rMhs,
        std::set<Kelas, std::less<>>& rKelas
    ) {

    // Form Isi Data
    std::string id, name, nrp, tglLahir, dept;
    int thnMsk;
    fflush(stdin);
    std::cout << "ID         : ";
    std::getline(std::cin, id);
    std::cout << "Name       : ";
    std::getline(std::cin, name);
    std::cout << "NRP        : ";
    std::getline(std::cin, nrp);

    do {
        std::cout << "Tgl. Lahir (format: dd-mm-yyyy): ";
        std::getline(std::cin, tglLahir);
        if (std::regex_match(tglLahir, regexTglLahir)) break;
        std::cout << "Format Tanggal Lahir Salah!" << std::endl;
    } while (true);

    std::cout << "Departemen : ";
    std::getline(std::cin, dept);
    std::cout << "Thn. Masuk : ";
    std::cin >> thnMsk;

    // Masukkan ke set
    std::pair<std::set<Mahasiswa, std::less<void>>::iterator, bool> tmpMhs = 
        rMhs.insert(Mahasiswa(id, name, tglLahir, nrp, dept, thnMsk));
    
    // Enroll ke kelas
    Mahasiswa& mhs = (Mahasiswa&)*(tmp.first);
    if (!tmp.second)
        std::cout << "[ERROR] Mahasiswa dengan ID: " << mhs.getId() << " Telah berada pada sistem ini." << std::endl;
    bool enroll = true;
    while (enroll) {
        std::cout << "1. Enroll ke kelas" << std::endl;
        std::cout << "2. Kembali" << std::endl;
        int choice;
        std::cout << "Pilihan > ";
        std::cin >> choice;
        fflush(stdin);
        switch (choice) {
            case 1: {
                // form kelas
                std::string id;
                std::cout << "ID Kelas   : ";
                std::getline(std::cin, id);
                std::set<Kelas>::iterator it = rKelas.find(id);
                if (it == rKelas.end()) { // Kelas tidak ditemukan
                    std::cout << "[ERROR] Kelas dengan ID: " << id << " tidak ditemukan" << std::endl;
                    break;
                } else if (mhs.enroll((Kelas&)*it) == true) { // Berhasil Enroll
                    std::cout << "Mahasiswa dengan ID: " << mhs.getId() << " berhasil teregistrasi ke kelas " << id << std::endl;
                    break;
                } else { // Mahasiswa telah berada di kelas ini
                    std::cout << "[ERROR] Mahasiswa dengan ID: " << mhs.getId() << " telah berada ke kelas " << id << std::endl;
                    break;
                }
                std::cout << "[ERROR] Unhandled Error: " << std::endl;
                break;
            }

            case 2:
                enroll = false;
                break;
        }
    }
}

void addDosenHandler(
        std::set<Dosen, std::less<>>& rDosen,
        std::set<Kelas, std::less<>>& rKelas
    ) {
    // Form isi data
    std::string id, name, npp, tglLahir, dept;
    int pend;
    fflush(stdin);
    std::cout << "ID         : ";
    std::getline(std::cin, id);
    std::cout << "Name       : ";
    std::getline(std::cin, name);
    std::cout << "NPP        : ";
    std::getline(std::cin, npp);

    do {
        std::cout << "Tgl. Lahir (format: dd-mm-yyyy): ";
        std::getline(std::cin, tglLahir);
        if (std::regex_match(tglLahir, regexTglLahir)) break;
        std::cout << "Format Tanggal Lahir Salah!" << std::endl;
    } while (true);

    std::cout << "Departemen : ";
    std::getline(std::cin, dept);
    std::cout << "Pendidikan : ";
    std::cin >> pend;

    // Masukkan ke set
    std::pair<std::set<Dosen, std::less<void>>::iterator, bool> tmp = 
        rDosen.insert(Dosen(id, name, tglLahir, npp, dept, pend));

    // Enroll ke kelas
    Dosen& dsn = (Dosen&)*(tmp.first);
    if (!tmp.second)
        std::cout << "[ERROR] Dosen dengan ID: " << dsn.getId() << 
                    " Telah berada pada sistem ini." << std::endl;
    bool enroll = true;
    while (enroll) {
        std::cout << "1. Enroll ke kelas" << std::endl;
        std::cout << "2. Kembali" << std::endl;
        int choice;
        std::cout << "Pilihan > ";
        std::cin >> choice;
        fflush(stdin);
        switch (choice) {
            case 1: {
                std::string id;
                std::cout << "ID Kelas   : ";
                std::getline(std::cin, id);
                std::set<Kelas>::iterator it = rKelas.find(id);
                if (it == rKelas.end()) {
                    std::cout << "[ERROR] Kelas dengan ID: " << id << " tidak ditemukan" << std::endl;
                    break;
                } else if (dsn.enroll((Kelas&)*it) == true) {
                    std::cout << "Dosen dengan ID: " << dsn.getId() << " berhasil teregistrasi ke kelas " << id << std::endl;
                    break;
                } else {
                    std::cout << "[ERROR] Dosen dengan ID: " << dsn.getId() << " telah berada ke kelas " << id << std::endl;
                    break;
                }
                std::cout << "[ERROR] Unhandled Error: " << std::endl;
                break;
            }

            case 2:
                enroll = false;
                break;
        }
    }
}

void addKelasHandler(
        std::set<Kelas, std::less<>>& rKelas,
        std::set<Mahasiswa, std::less<>>& rMhs,
        std::set<Dosen, std::less<>>& rDosen
    ) {
    // Form isi
    std::string id, dept;
    fflush(stdin);
    std::cout << "ID         : ";
    std::getline(std::cin, id);
    std::cout << "Departemen : ";
    std::getline(std::cin, dept);
    Kelas kelas(id, dept);

    // Masukkan ke set
    std::pair<std::set<Kelas, std::less<>>::iterator, bool> tmp = rKelas.insert(Kelas(kelas));

    // Enroll Mahasiswa dan dosen
    Kelas& kls = (Kelas&)*(tmp.first);
    if (!tmp.second)
        std::cout << "[ERROR] Kelas dengan ID: " << kls.getId() << " Telah berada pada sistem ini." << std::endl;
    bool enroll = true;
    while (enroll) {
        std::cout << "1. Enroll Mahasiswa" << std::endl;
        std::cout << "2. Enroll Dosen" << std::endl;
        std::cout << "3. Kembali" << std::endl;
        int choice;
        std::cout << "Pilihan > ";
        std::cin >> choice;
        fflush(stdin);
        switch (choice) {
            case 1: { // Enroll Mahasiswa
                std::string id;
                std::cout << "ID         : ";
                std::getline(std::cin, id);
                std::set<Mahasiswa>::iterator it = rMhs.find(id);
                if (it == rMhs.end()) {
                    std::cout << "[ERROR] Mahasiswa dengan ID: " << id << " tidak ditemukan" << std::endl;
                    break;
                } else if (kls.addMhs((Mahasiswa&)*it) == true) {
                    std::cout << "Mahasiswa dengan ID : " << id << " berhasil teregistrasi di kelas " << kls.getId() << std::endl;
                    break;
                } else {
                    std::cout << "[ERROR] Mahasiswa dengan ID : " << id << " telah berada di kelas " << kls.getId() << std::endl;
                    break;
                }
                std::cout << "[ERROR] Unhandled Error: " << std::endl;
                break;
            }

            case 2: { // Enroll Dosen
                std::string id;
                std::cout << "ID         : ";
                std::getline(std::cin, id);
                std::set<Dosen>::iterator it = rDosen.find(id);
                if (it == rDosen.end()) {
                    std::cout << "[ERROR] Dosen dengan ID: " << id << " tidak ditemukan" << std::endl;
                    break;
                } else if (kls.addDosen((Dosen&)*it) == true) {
                    std::cout << "Dosen dengan ID : " << id << " berhasil teregistrasi di kelas " << kls.getId() << std::endl;
                    break;
                } else {
                    std::cout << "[ERROR] Dosen dengan ID : " << id << " telah berada di kelas " << kls.getId() << std::endl;
                    break;
                }
                std::cout << "[ERROR] Unhandled Error: " << std::endl;
                break;
            }
            case 3:
                enroll = false;
                break;
        }
    }
}

int main() {
    std::set<Kelas, std::less<>> recKelas;
    std::set<Mahasiswa, std::less<>> recMhs;
    std::set<Dosen, std::less<>> recDosen;

    while (1) {
        std::cout << "0. Keluar" << std::endl;
        std::cout << "1. Add Mahasiswa" << std::endl;
        std::cout << "2. Add Dosen" << std::endl;
        std::cout << "3. Add Kelas" << std::endl;
        std::cout << "4. Print Mahasiswa" << std::endl;
        std::cout << "5. Print Dosen" << std::endl;
        std::cout << "6. Print Kelas" << std::endl;
        int choice;
        std::cout << "Pilihan > ";
        std::cin >> choice;

        fflush(stdin);
        switch (choice) {

            case 1: { addMhsHandler(recMhs, recKelas); break; }
            case 2: { addDosenHandler(recDosen, recKelas); break; }
            case 3: { addKelasHandler(recKelas, recMhs, recDosen); }
            case 4: {
                for (const Mahasiswa& i : recMhs) {
                    std::cout << (Mahasiswa&)i << std::endl;
                }
                break;
            }
            case 5: {
                for (const Dosen& i : recDosen) {
                    std::cout << (Dosen&)i << std::endl;
                }
                break;
            }
            case 6: {
                for (const Kelas& i : recKelas) {
                    std::cout << (Kelas&)i << std::endl;
                }
                break;
            }
            default: break;
        }
    }
}