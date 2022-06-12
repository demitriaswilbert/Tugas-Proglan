
#include <bits/stdc++.h>
#include <regex>

#include "include/dosen.h"
#include "include/kelas.h"
#include "include/mahasiswa.h"
#include "include/person.h"
#include "include/matkul.h"
#include "include/form.h"


#define InfoBatal "[INFO] Ketik \'kembali\' untuk kembali ke laman sebelumnya" 

#define regexTglLahir "(0?[1-9]|[12][0-9]|3[0-1])-(0?[1-9]|1[0-2])-\\d{4}"
#define regexEmail "(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"
#define regexFloat "^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)$"

static std::set<Mahasiswa, std::less<>> rMhs;
static std::set<Matkul, std::less<>> rMatkul;
static std::set<Dosen, std::less<>> rDosen;
static std::set<Kelas, std::less<>> rKelas;

template <typename T> std::string print (T begin, T end) {
    std::stringstream ss;
    if (begin == end) {
        ss << "{ Kosong }";
        return ss.str();
    } 
    ss << "{ ";
    for(T tmp = begin; tmp != end; ++tmp) {
        if(tmp != begin) ss << ", ";
        ss << (*tmp)->getId();
    }
    ss << " }";
    return ss.str();
}

void Mhs_enrollKelas ( Mahasiswa& mhs );
void Mhs_unenrollKelas ( Mahasiswa& mhs );
void Dosen_enrollKelas(  Dosen& dsn );
void Dosen_unenrollKelas(  Dosen& dsn );
void Kelas_addMhs( Kelas& kls );
void Kelas_removeMhs( Kelas& kls );
void Kelas_addDosen( Kelas& kls );
void Kelas_removeDosen( Kelas& kls );
void Matkul_addKelas( Matkul& matkul );
void Matkul_removeKelas( Matkul& matkul );
void addMhsHandler ( );
void addDosenHandler ( );
void addMatkulHandler ( );
void addKelasHandler ( );
void dosen_beriNilai ( Dosen& dosen );
void mhsPage ( Mahasiswa& mhs );
void kelasPage ( Kelas& kelas );
void matkulPage ( Matkul& matkul );
void dosenPage ( Dosen& dosen );
int selectMhsHandler ( std::set<Mahasiswa*, std::less<>>* pMhs = NULL );
int selectDosenHandler ( std::set<Dosen*, std::less<>>* pDosen = NULL );
int selectMatkulHandler ( std::set<Matkul*, std::less<>>* pMatkul = NULL );
int selectKelasHandler ( std::set<Kelas*, std::less<>>* pKelas = NULL );
int selectKelasHandler ( std::map<Kelas*, float>* pKelas = NULL );
void removeMhsHandler ( );
void removeDosenHandler ( );
void removeKelasHandler ( );
void removeMatkulHandler ( );



void Mhs_enrollKelas ( Mahasiswa& mhs ) {
    std::string id;
    if (!fillSingle({"Kode Kelas : ", &id, ".{1,}"})) 
        return;

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
}

void Mhs_unenrollKelas ( Mahasiswa& mhs ) {
    std::string id;
    if (!fillSingle({"Kode Kelas : ", &id, ".{1,}"})) 
        return;

    std::set<Kelas>::iterator it = rKelas.find(id);
    if (it == rKelas.end()) { // Kelas tidak ditemukan
        std::cout   << "[ERROR] Kelas dengan ID: " << id 
                    << " tidak ditemukan" << std::endl;
    } else if (mhs.unenroll((Kelas&)*it) == true) {
        std::cout   << "Mahasiswa dengan ID: " << mhs.getId() 
                    << " berhasil terhapus dari kelas " 
                    << id << std::endl;
    } else { 
        std::cout   << "[WARNING] Mahasiswa dengan ID: " 
                    << mhs.getId() << " tidak berada ke kelas " 
                    << id << std::endl;
    }
}

void Dosen_enrollKelas( Dosen& dsn ) {
    std::string id;
    if (!fillSingle({"Kode Kelas : ", &id, ".{1,}"})) 
        return;

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
}

void Dosen_unenrollKelas( Dosen& dsn ) {
    std::string id;
    if (!fillSingle({"Kode Kelas : ", &id, ".{1,}"})) 
        return;

    std::set<Kelas>::iterator it = rKelas.find(id);
    if (it == rKelas.end()) {
        std::cout   << "[ERROR] Kode kelas: " << id 
                    << " tidak ditemukan" << std::endl;
    } else if (dsn.unenroll((Kelas&)*it) == true) {
        std::cout   << "Dosen dengan email: " << dsn.getId() 
                    << " berhasil terhapus dari kelas " << id 
                    << std::endl;
    } else {
        std::cout   << "[WARNING] Dosen dengan email: " 
                    << dsn.getId() << " tidak berada ke kelas " 
                    << id << std::endl;
    }
}

void Kelas_addMhs( Kelas& kls ) {
    std::string id;
    if (!fillSingle({"Email ID   : ", &id, regexEmail})) 
        return;

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
}

void Kelas_removeMhs( Kelas& kls ) {
    std::string id;
    if (!fillSingle({"Email ID   : ", &id, regexEmail})) 
        return;

    std::set<Mahasiswa>::iterator it = rMhs.find(id);
    if (it == rMhs.end()) {
        std::cout   << "[ERROR] Mahasiswa dengan email: " 
                    << id << " tidak ditemukan" << std::endl;
    } else if (kls.removeMhs((Mahasiswa&)*it) == true) {
        std::cout   << "Mahasiswa dengan email : " 
                    << id << " berhasil terhapus di kelas " 
                    << kls.getId() << std::endl;
    } else {
        std::cout   << "[WARNING] Mahasiswa dengan email : " 
                    << id << " tidak berada di kelas " 
                    << kls.getId() << std::endl;
    }
}


void Kelas_addDosen( Kelas& kls ) {
    std::string id;
    if (!fillSingle({"Email ID   : ", &id, regexEmail})) 
        return;

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
}

void Kelas_removeDosen( Kelas& kls ) {
    std::string id;
    if (!fillSingle({"Email ID   : ", &id, regexEmail})) 
        return;

    std::set<Dosen>::iterator it = rDosen.find(id);
    if (it == rDosen.end()) {
        std::cout   << "[ERROR] Dosen dengan email: " 
                    << id << " tidak ditemukan" << std::endl;
    } else if (kls.removeDosen((Dosen&)*it) == true) {
        std::cout   << "Dosen dengan email : " << id 
                    << " berhasil terhapus di kelas " 
                    << kls.getId() << std::endl;
    } else {
        std::cout   << "[ERROR] Dosen dengan email : " 
                    << id << " tidak berada di kelas " 
                    << kls.getId() << std::endl;
    }
}

void Matkul_addKelas(  Matkul& matkul ) {
    std::string id, dept;
    
    std::system("cls");
    std::cout << "Form Isi Data Kelas" << std::endl;
    std::cout << InfoBatal << std::endl;
    if(!fillSingle( {"Kode Kelas : ", &id, ".{1,}"} )) return;

    // Masukkan ke set
    std::pair<std::set<Kelas, std::less<>>::iterator, bool> tmp = 
        rKelas.insert(Kelas(id));

    // Enroll Mahasiswa dan dosen
    Kelas& kls = (Kelas&)*(tmp.first);
    if (!tmp.second)
        std::cout   << "[WARNING] Kelas dengan Kode: " 
                    << kls.getId() << " Telah berada pada sistem ini." 
                    << std::endl;
    if (kls.getMatkul() == NULL){
        if (kls.setMatkul(matkul)) {
            std::cout   << "Kelas dengan Kode: " << kls.getId()
                        << " berhasil terdaftar di mata kuliah "
                        << matkul.getId() << std::endl;
        } 
    } else if (kls.getMatkul() != &matkul) {
        std::cout   << "[WARNING] Kelas dengan Kode: " 
                    << kls.getId() << " Telah terdaftar di mata kuliah " 
                    << kls.getMatkul()->getId() << ". Apakah mau diganti "
                    << "menjadi mata kuliah " << matkul.getId() << "? ";
        std::string choice;
        fillSingle(Form("(y/n): ", &choice, "[YyNn]"));
        if (tolower(choice[0]) == 'y')
            kls.setMatkul(matkul);
    }

    kelasPage(kls);
}

void Matkul_removeKelas( Matkul& matkul ) {
    std::string id, dept;
    
    std::cout << InfoBatal << std::endl;
    if(!fillSingle( {"Kode Kelas : ", &id, ".{1,}"} )) return;

    std::set<Kelas>::iterator tmp = rKelas.find(id);
    if (tmp == rKelas.end()) {
        std::cout   << "[ERROR] Kelas dengan kode " << id 
                    << " tidak ditemukan di sistem ini." << std::endl;
        return;
    } else if (((Kelas&)(*tmp)).getMatkul() != &matkul) {
        std::cout   << "[ERROR] Kelas dengan kode " << id 
                    << " tidak terdaftar pada mata kuliah " << matkul.getId()
                    << std::endl;
        return;
    } else if (((Kelas&)(*tmp)).getMatkul() == &matkul) { // [TODO]
        if (((Kelas&)(*tmp)).removeMatkul()) {
            std::cout   << "Berhasil menghapus kelas dengan kode " << id 
                        << " dari mata kuliah " << matkul.getId() << std::endl;
            rKelas.erase(tmp);
        }
    }
}

void addMhsHandler ( ) {

    // Form Isi Data
    std::string id, name, nrp, tglLahir, dept, thnMsk;
    std::system("cls");
    std::cout << "Form Isi Data Mahasiswa" << std::endl;
    std::cout << InfoBatal << std::endl;
    std::vector<Form> form = { 
        {"Email ID   : ", &id, regexEmail}, {"Name       : ", &name, ".{1,}"}, 
        {"Tgl. Lahir (format: dd-mm-yyyy): ", &tglLahir, regexTglLahir}, 
        {"NRP        : ", &nrp, "\\d{1,}"}, {"Departemen : ", &dept, ".{1,}"}, 
        {"Thn. Masuk : ", &thnMsk, "\\d{1,}"}
    };
    if(!fillForm( form )) 
        return;

    // Masukkan ke set
    std::pair<std::set<Mahasiswa, std::less<void>>::iterator, bool> tmp = 
        rMhs.insert(Mahasiswa(id, name, tglLahir, nrp, dept, std::stoi(thnMsk)) );
    
    // Enroll ke kelas
    Mahasiswa& mhs = (Mahasiswa&)*(tmp.first);
    mhsPage(mhs);
}

void addDosenHandler ( ) {
    // Form isi data
    std::string id, name, npp, tglLahir, dept, pend;
    
    std::system("cls");
    std::cout << "Form Isi Data Dosen" << std::endl;
    std::cout << InfoBatal << std::endl;
    std::vector<Form> form = { 
        {"Email ID   : ", &id, regexEmail}, {"Name       : ", &name, ".{1,}"}, 
        {"Tgl. Lahir (format: dd-mm-yyyy: ", &tglLahir, regexTglLahir}, 
        {"NPP        : ", &npp, "\\d{1,}"}, {"Departemen : ", &dept, ".{1,}"}, 
        {"Pendidikan : ", &pend, ".{1,}"}
    };
    if(!fillForm( form )) return;

    // Masukkan ke set
    std::pair<std::set<Dosen, std::less<void>>::iterator, bool> tmp = 
        rDosen.insert(Dosen(id, name, tglLahir, npp, dept, pend));

    // Enroll ke kelas
    Dosen& dsn = (Dosen&)*(tmp.first);
    if (!tmp.second)
        std::cout << "[WARNING] Dosen dengan ID: " << dsn.getId() << 
                    " Telah berada pada sistem ini." << std::endl;
                    
    dosenPage(dsn);
}

void addMatkulHandler ( )
{
    // Form isi
    std::string id, sks;
    
    std::system("cls");
    std::cout << "Form Isi Data Mata Kuliah" << std::endl;
    std::cout << InfoBatal << std::endl;
    std::vector<Form> form = { 
        {"Kode Matkul: ", &id, ".{1,}"},
        {"SKS        : ", &sks, regexFloat},
    };
    if(!fillForm( form )) return;

    // Masukkan ke set
    std::pair<std::set<Matkul, std::less<>>::iterator, bool> tmp = 
        rMatkul.insert(Matkul(id, std::stof(sks)));

    // Tambah Kelas
    Matkul& matkul = (Matkul&)*(tmp.first);
    if (!tmp.second)
        std::cout   << "[WARNING] Mata Kuliah dengan Kode: " 
                    << matkul.getId() << " Telah berada pada sistem ini." 
                    << std::endl;

    matkulPage(matkul);
}

void mhsPage ( Mahasiswa& mhs ) {
    bool enroll = true;
    while (enroll) {
        std::cout << "1. Enroll ke kelas" << std::endl;
        std::cout << "2. Pilih kelas" << std::endl;
        std::cout << "3. Hapus Kelas" << std::endl;
        std::cout << "4. Daftar Kelas" << std::endl;
        std::cout << "5. Kembali" << std::endl;
        std::string choiceStr;
        if(!fillSingle({"Pilihan > ", &choiceStr, "\\d{1,}"})) return;
        int choice = std::stoi(choiceStr);
        switch (choice) {
            case 1: { Mhs_enrollKelas(mhs); break;}
            case 2: { selectKelasHandler(&mhs.getAllKelas()); break; }
            case 3: { Mhs_unenrollKelas(mhs); break;}
            case 4: { 
                std::map<Kelas *, float>& kelas_nilai = mhs.getAllKelas();
                std::map<Kelas *, float>::iterator it = kelas_nilai.begin();
                for(; it != kelas_nilai.end(); ++it) {
                    std::cout   << "Kelas: " << it->first->getId() << ", IP: "
                                << std::setprecision(3) << it->second << std::endl;
                }
                if(it == kelas_nilai.begin())
                    std::cout   << "[ERROR] Mahasiswa dengan email : " 
                                << mhs.getId() << " Belum memiliki kelas." 
                                << std::endl;
                break;
            }
            case 5: enroll = false;
            default: break;
        }
    }
}

void dosen_beriNilai ( Dosen& dosen ) {
    bool enroll = true;
    while (enroll) {
        std::cout << InfoBatal << std::endl;
        std::string id;
        if (!fillSingle({"ID Kelas   : ", &id, ".{1,}"})) return;
        std::set<Kelas>::iterator itKelas = rKelas.find(id);
        if (itKelas == rKelas.end()) {
            std::cout   << "[ERROR] Kode Kelas " << id << " tidak ditemukan "
                        << "pada sistem" << std::endl;
            continue;
        } else {
            std::set<Kelas *> kelasDosen =  dosen.getAllKelas();
            std::set<Kelas *>::const_iterator itKelasDosen = 
                kelasDosen.find((Kelas*)&(*itKelas));

            if (itKelasDosen == kelasDosen.end()) {
                std::cout   << "[ERROR] dosen " << dosen.getId() << " tidak mengajar "
                            << " kelas " << ((Kelas&)(*itKelas)).getId() << std::endl;
                continue;
            } else {
                for(Mahasiswa* i : (*itKelasDosen)->getRecMhs()) {
                    std::string prompt = "Nilai Mahasiswa " + i->getId() + ": ";
                    std::string floatstr;
                    if(!fillSingle(Form(prompt, &floatstr, regexFloat)))
                        break;
                    std::map<Kelas *, float>& kelas_nilai = i->getAllKelas();
                    kelas_nilai[(Kelas*)&(*itKelas)] = std::stof(floatstr);
                }
            }
        }
    }
}

void kelasPage ( Kelas& kelas ) {
    bool enroll = true;
    while (enroll) {
        std::cout << std::endl;
        std::cout << "1. Tambah Mahasiswa" << std::endl;
        std::cout << "2. Tambah Dosen" << std::endl;
        std::cout << "3. Daftar Mahasiswa" << std::endl;
        std::cout << "4. Daftar Dosen" << std::endl;
        std::cout << "5. Pilih Mahasiswa" << std::endl;
        std::cout << "6. Pilih Dosen" << std::endl;
        std::cout << "7. Hapus Mahasiswa" << std::endl;
        std::cout << "8. Hapus Dosen" << std::endl;
        std::cout << "9. Kembali" << std::endl;
        std::string choiceStr;
        if(!fillSingle({"Pilihan > ", &choiceStr, "\\d{1,}"})) return;
        int choice = std::stoi(choiceStr);
        switch (choice) {
            case 1: { Kelas_addMhs(kelas); break; }
            case 2: { Kelas_addDosen(kelas); break; }
            case 3: { 
                std::cout << "\nDaftar Mahasiswa : " 
                          << print(kelas.getRecMhs().begin(), kelas.getRecMhs().end())
                          << std::endl;
                break; 
            }
            case 4: { 
                std::cout << "\nDaftar Dosen : " 
                          << print(kelas.getRecDosen().begin(), kelas.getRecDosen().end())
                          << std::endl;
                break;  
            }
            case 5: { selectMhsHandler(&kelas.getRecMhs()); break;}
            case 6: { selectDosenHandler(&kelas.getRecDosen()); break;}
            case 7: { Kelas_removeMhs(kelas); break;}
            case 8: { Kelas_removeDosen(kelas); break;}
            case 9: enroll = false;
            default: break;
        }
    }
}

void matkulPage ( Matkul& matkul ) {
    bool enroll = true;
    while (enroll) {
        std::cout << "1. Tambah Kelas" << std::endl;
        std::cout << "2. Pilih Kelas" << std::endl;
        std::cout << "3. Hapus Kelas" << std::endl;
        std::cout << "4. Daftar Kelas" << std::endl;
        std::cout << "5. Kembali" << std::endl;
        std::string choiceStr;
        if(!fillSingle({"Pilihan > ", &choiceStr, "\\d{1,}"})) return;
        int choice = std::stoi(choiceStr);
        switch (choice) {
            case 1: { Matkul_addKelas(matkul); break; }
            case 2: { selectKelasHandler(&matkul.getRecKelas()); break; }
            case 3: { Matkul_removeKelas(matkul); break; }
            case 4: { 
                std::cout << "\nDaftar Kelas : " 
                          << print(matkul.getRecKelas().begin(), matkul.getRecKelas().end())
                          << std::endl;
                break; 
            }
            case 5: enroll = false;
            default: break;
        }
    }
}

void dosenPage ( Dosen& dosen ) {
    bool enroll = true;
    while (enroll) {
        std::cout << "1. Tambah ke kelas" << std::endl;
        std::cout << "2. Daftar Kelas" << std::endl;
        std::cout << "3. Hapus Kelas" << std::endl;
        std::cout << "4. Beri Nilai" << std::endl;
        std::cout << "5. Kembali" << std::endl;
        std::string choiceStr;
        if(!fillSingle({"Pilihan > ", &choiceStr, "\\d{1,}"})) return;
        int choice = std::stoi(choiceStr);
        switch (choice) {
            case 1: { Dosen_enrollKelas(dosen); break;}
            case 2: { 
                std::cout   << "\nDaftar Kelas : "
                            << print(dosen.getAllKelas().begin(), dosen.getAllKelas().end()) 
                            << std::endl; 
                break;
            }
            case 3: { Dosen_unenrollKelas(dosen); break; }
            case 4: { dosen_beriNilai(dosen); break; }
            case 5: enroll = false;
            default: break;
        }
    }
}

int selectMhsHandler ( std::set<Mahasiswa*, std::less<>>* pMhs ) {
    // Form Isi Data
    std::string id;
    if (!fillSingle( {"Email ID   : ", &id, regexEmail} )) 
        return 2;

    std::set<Mahasiswa>::iterator it = rMhs.find(id);
    if(it == rMhs.end()) {
        std::cout   << "[ERROR] Mahasiswa dengan email: "
                    << id << " tidak ditemukan." << std::endl;
        return 0;
    } else if (pMhs != NULL) {
        std::set<Mahasiswa *>::iterator itMhs = pMhs->find((Mahasiswa*)&(*it));
        if (itMhs == pMhs->end()) {
            std::cout   << "[ERROR] Dosen dengan email " << id
                        << " tidak ditemukan." << std::endl;
            return 0;
        }  
    }
    
    Mahasiswa& mhs = (Mahasiswa&)(*it);
    mhsPage(mhs);
    return 1;
}

int selectDosenHandler ( std::set<Dosen*, std::less<>>* pDosen ) {
    // Form isi data
    std::string id;
    if (!fillSingle( {"Email ID   : ", &id, regexEmail} )) 
        return 2;

    std::set<Dosen>::iterator it = rDosen.find(id);
    if(it == rDosen.end()) {
        std::cout   << "[ERROR] Dosen dengan email: "
                    << id << " tidak ditemukan." << std::endl;
        return 0;
    } else if (pDosen != NULL) {
        std::set<Dosen *>::iterator itDosen = pDosen->find((Dosen*)&(*it));
        if (itDosen == pDosen->end()) {
            std::cout   << "[ERROR] Dosen dengan email " << id
                        << " tidak ditemukan." << std::endl;
            return 0;
        }  
    }
    
    Dosen& dosen = (Dosen&)(*it);
    dosenPage(dosen);
    return 1;
}

int selectKelasHandler ( std::map<Kelas*, float>* pKelas ) {
    // Form isi data
    std::string id;
    if (!fillSingle( {"Kode Kelas : ", &id, ".{1,}"} )) 
        return 2;

    std::set<Kelas>::iterator it = rKelas.find(id);
    if(it == rKelas.end()) {
        std::cout   << "[ERROR] Kode kelas: "
                    << id << " tidak ditemukan." << std::endl;
        return 0;
    } else if (pKelas != NULL) {
        std::map<Kelas *, float>::iterator itKelas = pKelas->find((Kelas*)&(*it));
        if (itKelas == pKelas->end()) {
            std::cout   << "[ERROR] Kode kelas: " << id
                        << " tidak ditemukan." << std::endl;
            return 0;
        }  
    }
    
    Kelas& kelas = (Kelas&)(*it);
    kelasPage(kelas);
    return 1;
}

int selectKelasHandler ( std::set<Kelas*, std::less<>>* pKelas ) {
    // Form isi data
    std::string id;
    if (!fillSingle( {"Kode Kelas : ", &id, ".{1,}"} )) 
        return 2;

    std::set<Kelas>::iterator it = rKelas.find(id);
    if(it == rKelas.end()) {
        std::cout   << "[ERROR] Kode kelas: "
                    << id << " tidak ditemukan." << std::endl;
        return 0;
    } else if (pKelas != NULL) {
        std::set<Kelas *>::iterator itKelas = pKelas->find((Kelas*)&(*it));
        if (itKelas == pKelas->end()) {
            std::cout   << "[ERROR] Kode kelas: " << id
                        << " tidak ditemukan." << std::endl;
            return 0;
        }  
    }
    
    Kelas& kelas = (Kelas&)(*it);
    kelasPage(kelas);
    return 1;
}

int selectMatkulHandler ( std::set<Matkul*, std::less<>>* pMatkul ) {
    // Form isi data
    std::string id;
    if (!fillSingle( {"Kode Matkul: ", &id, ".{1,}"} )) 
        return 2;

    std::set<Matkul>::iterator it = rMatkul.find(id);
    if(it == rMatkul.end()) {
        std::cout   << "[ERROR] Kode Matkul: "
                    << id << " tidak ditemukan." << std::endl;
        return 0;
    } else if (pMatkul != NULL) {
        std::set<Matkul *>::iterator itMatkul = pMatkul->find((Matkul*)&(*it));
        if (itMatkul == pMatkul->end()) {
            std::cout   << "[ERROR] Kode Matkul: " << id
                        << " tidak ditemukan." << std::endl;
            return 0;
        }  
    }
    
    Matkul& matkul = (Matkul&)(*it);
    matkulPage(matkul);
    return 1;
}

void addKelasHandler( ) {
    // Form isi
    std::string id, dept;
    
    std::cout << InfoBatal << std::endl;
    if(!fillSingle( {"Kode Kelas : ", &id, ".{1,}"} )) return;

    // Masukkan ke set
    std::pair<std::set<Kelas, std::less<>>::iterator, bool> tmp = 
        rKelas.insert(Kelas(id));

    // Enroll Mahasiswa dan dosen
    Kelas& kls = (Kelas&)*(tmp.first);
    if (!tmp.second)
        std::cout   << "[WARNING] Kelas dengan Kode: " 
                    << kls.getId() << " Telah berada pada sistem ini." 
                    << std::endl;

    kelasPage(kls);
}

void removeMhsHandler( ) {
    std::string id;
    if (!fillSingle( {"Email ID   : ", &id, regexEmail} )) 
        return;

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

void removeDosenHandler( ) {
    std::string id;
    if (!fillSingle( {"Email ID   : ", &id, regexEmail} )) 
        return;
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

void removeKelasHandler( ) {
    std::string id;
    if (!fillSingle( {"Email ID   : ", &id, ".{1,}"} )) 
        return;

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

void removeMatkulHandler( ) {
    std::string id;
    if (!fillSingle( {"ID        : ", &id, ".{1,}"} )) 
        return;
    std::set<Matkul>::iterator it = rMatkul.find(id);
    if (it == rMatkul.end()) {
        std::cout   << "[ERROR] Mata Kuliah: " 
                    << id << " tidak ditemukan" << std::endl;
    } else {
        for(Kelas* i : ((Matkul&)(*it)).getRecKelas()) {
            std::set<Kelas, std::less<void>>::iterator itKelas = 
                rKelas.find(i->getId());
            rKelas.erase(itKelas);
        }
        if (rMatkul.erase(*it) == 1) {
            std::cout   << "Mata Kuliah : " 
                        << id << " berhasil dihapuskan dari sistem " << std::endl;
        } else {
            std::cout   << "[ERROR] Mata Kuliah : " 
                        << id << " gagal dihapus " << std::endl;
        }
    }
}


int main() {

    bool run = true;
    while (run) {
        std::system("cls");
        std::cout << "Jumlah Mahasiswa  : " << rMhs.size() << std::endl;
        std::cout << "Jumlah Dosen      : " << rDosen.size() << std::endl;
        std::cout << "Jumlah Kelas      : " << rKelas.size() << std::endl;
        std::cout << " 1. Add Mahasiswa      2. Add Dosen        3. Add Matkul" << std::endl;
        std::cout << " 4. Select Mahasiswa   5. Select Dosen     6. Select Matkul" << std::endl;
        std::cout << " 7. Remove Mahasiswa   8. Remove Dosen     9. Remove Mata Kuliah" << std::endl;
        std::cout << "10. Print Mahasiswa   11. Print Dosen     12. Print Kelas" << std::endl;
        std::cout << "0. Keluar" << std::endl;
        
        std::string choiceStr;
        if(!fillSingle({"Pilihan > ", &choiceStr, "\\d{1,}"})) continue;
        int choice = std::stoi(choiceStr);

        fflush(stdin);
        switch (choice) {

            case 1: { addMhsHandler(); break; }
            case 2: { addDosenHandler(); break; }
            case 3: { addMatkulHandler(); break;}

            case 4: { selectMhsHandler(); break;}
            case 5: { selectDosenHandler(); break;}
            case 6: { selectMatkulHandler(); break;}

            case 7: { removeMhsHandler(); break;}
            case 8: { removeDosenHandler(); break;}
            case 9: { removeMatkulHandler(); break;}
            
            case 10: {
                for (const Mahasiswa& i : rMhs) {
                    std::cout << (Mahasiswa&)i << std::endl;
                }
                break;
            }
            case 11: {
                for (const Dosen& i : rDosen) {
                    std::cout << (Dosen&)i << std::endl;
                }
                break;
            }
            case 12: {
                for (const Kelas& i : rKelas) {
                    std::cout << (Kelas&)i << std::endl;
                }
                break;
            }
            case 0: run = false;
            default: break;
        }
        fflush(stdin);
        std::cout << "[INFO] Tekan Enter untuk kembali ke menu: " << std::endl;
        std::getc(stdin);
    }
}