
#include <bits/stdc++.h>
#include <regex>

#include "include/dosen.h"
#include "include/kelas.h"
#include "include/mahasiswa.h"
#include "include/person.h"
#include "include/tendik.h"

#define InfoBatal() {std::cout << "[INFO] Ketik \'kembali\' untuk membatalkan pendaftaran" << std::endl;}

#define regexTglLahir "(0?[1-9]|[12][0-9]|3[0-1])-(0?[1-9]|1[0-2])-\\d{4}"
#define regexEmail "(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"

class Form {
    const char* prompt;
    std::string* buf;
    const char* regex;
    public:
    Form(const char* prompt, std::string *buf, const char* regex = NULL) 
        : prompt(prompt), buf(buf), regex(regex) {}
    Form(const std::string& prompt, std::string *buf, const char* regex = NULL) 
        : prompt(prompt.c_str()), buf(buf), regex(regex) {}
    int eval() {
        std::cout << prompt;
        std::fflush(stdin);
        std::getline(std::cin, *buf); 
        if (*buf == "Kembali") return 0;
        if (regex == NULL) return 2;
        return (((int)std::regex_match(*buf, std::regex(regex))) + 1);
    }
};

bool fillForm(std::vector<Form>& vForm) {
    for (Form& i : vForm) {
        while (int result = i.eval()) {
            if(result == 2) break;
            if(result == 1) 
                std::cout << "[ERROR] Format Salah!" << std::endl;
            else return false;
        }
    }
    return true;
}

void addMhsHandler (
        std::set<Mahasiswa, std::less<>>& rMhs,
        std::set<Kelas, std::less<>>& rKelas
    ) {

    // Form Isi Data
    std::string id, name, nrp, tglLahir, dept, thnMsk;
    InfoBatal();
    
    std::vector<Form> form = { 
        {"Email ID   : ", &id, regexEmail}, {"Name       : ", &name, ".{1,}"}, 
        {"NRP        : ", &nrp, "\\d{1,}"}, 
        {"Tgl. Lahir (format: dd-mm-yyyy): ", &tglLahir, regexTglLahir}, 
        {"Departemen : ", &dept, ".{1,}"}, {"Thn. Masuk : ", &thnMsk, "\\d{1,}"}
    };
    if(!fillForm( form )) return;

    // Masukkan ke set
    std::pair<std::set<Mahasiswa, std::less<void>>::iterator, bool> tmp = 
        rMhs.insert(Mahasiswa(id, name, tglLahir, nrp, dept, std::stoi(thnMsk)) );
    
    // Enroll ke kelas
    Mahasiswa& mhs = (Mahasiswa&)*(tmp.first);
    if (!tmp.second)
        std::cout   << "[WARNING] Mahasiswa dengan email: " << mhs.getId() 
                    << " Telah berada pada sistem ini." << std::endl;
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
                    std::cout   << "[ERROR] Kelas dengan ID: " << id 
                                << " tidak ditemukan" << std::endl;
                } else if (mhs.enroll((Kelas&)*it) == true) { // Berhasil Enroll
                    std::cout   << "Mahasiswa dengan ID: " << mhs.getId() 
                                << " berhasil teregistrasi ke kelas " 
                                << id << std::endl;
                } else { // Mahasiswa telah berada di kelas ini
                    std::cout   << "[WARNING] Mahasiswa dengan ID: " 
                                << mhs.getId() << " telah berada ke kelas " 
                                << id << std::endl;
                }
                break;
            }

            default: enroll = false;
        }
    }
}

void addDosenHandler(
        std::set<Dosen, std::less<>>& rDosen,
        std::set<Kelas, std::less<>>& rKelas
    ) {
    // Form isi data
    std::string id, name, npp, tglLahir, dept, pend;
    
    std::vector<Form> form = { 
        {"Email ID   : ", &id, regexEmail}, {"Name       : ", &name, ".{1,}"}, 
        {"NPP        : ", &npp, "\\d{1,}"}, 
        {"Tgl. Lahir (format: dd-mm-yyyy: ", &tglLahir, regexTglLahir}, 
        {"Departemen : ", &dept, ".{1,}"}, {"Thn. Masuk : ", &pend, "\\d{1,}"}
    };
    if(!fillForm( form )) return;

    // Masukkan ke set
    std::pair<std::set<Dosen, std::less<void>>::iterator, bool> tmp = 
        rDosen.insert(Dosen(id, name, tglLahir, npp, dept, std::stoi(pend)));

    // Enroll ke kelas
    Dosen& dsn = (Dosen&)*(tmp.first);
    if (!tmp.second)
        std::cout << "[WARNING] Dosen dengan ID: " << dsn.getId() << 
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
                    std::cout   << "[ERROR] Kode kelas: " << id 
                                << " tidak ditemukan" << std::endl;
                } else if (dsn.enroll((Kelas&)*it) == true) {
                    std::cout   << "Dosen dengan email: " << dsn.getId() 
                                << " berhasil teregistrasi ke kelas " << id 
                                << std::endl;
                } else {
                    std::cout   << "[WARNING] Dosen dengan email: " 
                                << dsn.getId() << " telah berada ke kelas " 
                                << id << std::endl;
                }
                break;
            }

            default: enroll = false;
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
    
    std::vector<Form> form = { 
        {"Kode Kelas : ", &id, ".{1,}"}, {"Departemen : ", &dept, ".{1,}"}
    };
    if(!fillForm( form )) return;

    // Masukkan ke set
    std::pair<std::set<Kelas, std::less<>>::iterator, bool> tmp = 
        rKelas.insert(Kelas(id, dept));

    // Enroll Mahasiswa dan dosen
    Kelas& kls = (Kelas&)*(tmp.first);
    if (!tmp.second)
        std::cout   << "[WARNING] Kelas dengan Kode: " 
                    << kls.getId() << " Telah berada pada sistem ini." 
                    << std::endl;

    bool enroll = true;
    while (enroll) {
        std::cout << std::endl;
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
                std::cout << "Email ID   : ";
                std::getline(std::cin, id);
                std::set<Mahasiswa>::iterator it = rMhs.find(id);
                if (it == rMhs.end()) {
                    std::cout   << "[ERROR] Mahasiswa dengan email: " 
                                << id << " tidak ditemukan" << std::endl;
                } else if (kls.addMhs((Mahasiswa&)*it) == true) {
                    std::cout   << "Mahasiswa dengan email : " 
                                << id << " berhasil teregistrasi di kelas " 
                                << kls.getId() << std::endl;
                } else {
                    std::cout   << "[WARNING] Mahasiswa dengan email : " 
                                << id << " telah berada di kelas " 
                                << kls.getId() << std::endl;
                }
                break;
            }

            case 2: { // Enroll Dosen
                std::string id;
                std::cout << "ID         : ";
                std::getline(std::cin, id);
                std::set<Dosen>::iterator it = rDosen.find(id);
                if (it == rDosen.end()) {
                    std::cout   << "[ERROR] Dosen dengan email: " 
                                << id << " tidak ditemukan" << std::endl;
                } else if (kls.addDosen((Dosen&)*it) == true) {
                    std::cout   << "Dosen dengan email : " << id 
                                << " berhasil teregistrasi di kelas " 
                                << kls.getId() << std::endl;
                } else {
                    std::cout   << "[ERROR] Dosen dengan email : " 
                                << id << " telah berada di kelas " 
                                << kls.getId() << std::endl;
                }
                break;
            }

            default: enroll = false;
        }
    }
}

void removeMhsHandler(std::set<Mahasiswa, std::less<>>& rMhs) {
    std::string id;
    do {
        std::cout << "Email ID   : ";
        std::getline(std::cin, id);
        if (std::regex_match(id, std::regex(regexEmail))) break;
        std::cout << "[ERROR] Format Email Salah!" << std::endl;
    } while (true);
    std::set<Mahasiswa>::iterator it = rMhs.find(id);
    if (it == rMhs.end()) {
        std::cout   << "[ERROR] Mahasiswa dengan email: " 
                    << id << " tidak ditemukan" << std::endl;
    } else if (rMhs.erase(*it) == 1) {
        std::cout   << "Mahasiswa dengan email : " 
                    << id << " berhasil dihapuskan dari sistem " << std::endl;
    } else {
        std::cout   << "[ERROR] Mahasiswa dengan email : " 
                    << id << " gagal dihapus " << std::endl;
    }
}

void removeDosenHandler(std::set<Dosen, std::less<>>& rDosen) {
    std::string id;
    do {
        std::cout << "Email ID   : ";
        std::getline(std::cin, id);
        if (std::regex_match(id, std::regex(regexEmail))) break;
        std::cout << "[ERROR] Format Email Salah!" << std::endl;
    } while (true);
    std::set<Dosen>::iterator it = rDosen.find(id);
    if (it == rDosen.end()) {
        std::cout   << "[ERROR] Dosen dengan email: " 
                    << id << " tidak ditemukan" << std::endl;
    } else if (rDosen.erase(*it) == 1) {
        std::cout   << "Dosen dengan email : " 
                    << id << " berhasil dihapuskan dari sistem " << std::endl;
    } else {
        std::cout   << "[ERROR] Dosen dengan email : " 
                    << id << " gagal dihapus " << std::endl;
    }
}

void removeKelasHandler(std::set<Kelas, std::less<>>& rKelas) {
    std::string id;
    std::cout << "Kode Kelas : ";
    std::getline(std::cin, id);

    std::set<Kelas>::iterator it = rKelas.find(id);
    if (it == rKelas.end()) {
        std::cout   << "[ERROR] Kode Kelas: " 
                    << id << " tidak ditemukan" << std::endl;
    } else if (rKelas.erase(*it) == 1) {
        std::cout   << "Kode Kelas : " 
                    << id << " berhasil dihapuskan dari sistem " << std::endl;
    } else {
        std::cout   << "[ERROR] Kode Kelas : " 
                    << id << " gagal dihapus " << std::endl;
    }
}

int main() {
    std::set<Mahasiswa, std::less<>> recMhs;
    std::set<Dosen, std::less<>> recDosen;
    std::set<Kelas, std::less<>> recKelas;

    while (1) {
        std::system("cls");
        std::cout << "Jumlah Mahasiswa  : " << recMhs.size() << std::endl;
        std::cout << "Jumlah Dosen      : " << recDosen.size() << std::endl;
        std::cout << "Jumlah Kelas      : " << recKelas.size() << std::endl;
        std::cout << "0. Keluar" << std::endl;
        std::cout << "1. Add Mahasiswa" << std::endl;
        std::cout << "2. Add Dosen" << std::endl;
        std::cout << "3. Add Kelas" << std::endl;
        std::cout << "4. Remove Mahasiswa" << std::endl;
        std::cout << "5. Remove Dosen" << std::endl;
        std::cout << "6. Remove Kelas" << std::endl;
        std::cout << "7. Print Mahasiswa" << std::endl;
        std::cout << "8. Print Dosen" << std::endl;
        std::cout << "9. Print Kelas" << std::endl;
        int choice;
        std::cout << "Pilihan > ";
        std::cin >> choice;

        fflush(stdin);
        switch (choice) {

            case 1: { addMhsHandler(recMhs, recKelas); break; }
            case 2: { addDosenHandler(recDosen, recKelas); break; }
            case 3: { addKelasHandler(recKelas, recMhs, recDosen); break;}

            case 4: { removeMhsHandler(recMhs); break;}
            case 5: { removeDosenHandler(recDosen); break;}
            case 6: { removeKelasHandler(recKelas); break;}
            
            case 7: {
                for (const Mahasiswa& i : recMhs) {
                    std::cout << (Mahasiswa&)i << std::endl;
                }
                std::getc(stdin);
                break;
            }
            case 8: {
                for (const Dosen& i : recDosen) {
                    std::cout << (Dosen&)i << std::endl;
                }
                std::getc(stdin);
                break;
            }
            case 9: {
                for (const Kelas& i : recKelas) {
                    std::cout << (Kelas&)i << std::endl;
                }
                std::getc(stdin);
                break;
            }
            default: break;
        }
    }
}