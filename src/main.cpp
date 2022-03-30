#include <iostream>
#include <vector>

#include "include/person.hpp"
#include "include/mahasiswa.hpp"
#include "include/dosen.hpp"
#include "include/tendik.hpp"

using namespace std;

void input(vector<string>& prompt, vector<string*>& pStr, vector<int*>& pInt)
{
    int promptCnt = 0;
    for(size_t i = 0; i < pStr.size(); i++)
        { cout << prompt[promptCnt++]; fflush(stdin); getline(cin, *(pStr[i])); }
    for(size_t i = 0; i < pInt.size(); i++)
        { cout << prompt[promptCnt++]; fflush(stdin); cin >> *(pInt[i]); }
}

int main()
{
	vector<mahasiswa> recMhs;
	vector<dosen> recDosen;
	vector<tendik> recTendik;

	int menu_terpilih;

	while(1) {
		cout << "Selamat datang di Universitas X" << endl << endl;
		cout << "Data statistik:" << endl;
		cout << "  1. Jumlah Mahasiswa             : " << recMhs.size() << " mahasiswa" << endl;
		cout << "  2. Jumlah Dosen                 : " << recDosen.size() << " mahasiswa" << endl;
		cout << "  3. Jumlah Tenaga Kependidikan   : " << recTendik.size() << " mahasiswa" << endl;
		cout << endl;
		cout << "Menu: " << endl;
		cout << "  1. Tambah Mahasiswa" << endl;
		cout << "  2. Tambah Dosen" << endl;
		cout << "  3. Tambah Tenaga Kependidikan" << endl;
		cout << "  4. Tampilkan semua Mahasiswa" << endl;
		cout << "  5. Tampilkan semua Dosen" << endl;
		cout << "  6. Tampilkan semua Tenaga Kependidikan" << endl;
		cout << "-> Silahkan memilih salah satu: ";
		fflush(stdin); cin >> menu_terpilih;
        
		switch (menu_terpilih) {
			case 1:
            {
                string nama, id, nrp, dept; 
                int dd, mm, yy, tm;
                vector<string> prompt = {
                    "Input nama                     : ", "Input id                       : ",
                    "Input nrp                      : ", "Input Departement              : ",
                    "Input Tanggal Lahir (angka)    : ", "Input Bulan Lahir (angka)      : ", 
                    "Input Tahun Lahir (angka)      : ", "Input Tahun masuk (angka)      : ", 
                };
                vector<string*> pStr = {&nama, &id, &nrp, &dept};
                vector<int*> pInt = {&dd, &mm, &yy, &tm};
                input(prompt, pStr, pInt);
                // cout << "Input nama                     : "; fflush(stdin); getline(cin,  nama);
                // cout << "Input id                       : "; fflush(stdin); getline(cin,  id);
                // cout << "Input nrp                      : "; fflush(stdin); getline(cin,  nrp);
                // cout << "Input Departement              : "; fflush(stdin); getline(cin,  dept);
                // cout << "Input Tanggal Lahir (angka)    : "; fflush(stdin); cin >> dd;
                // cout << "Input Bulan Lahir (angka)      : "; fflush(stdin); cin >> mm;
                // cout << "Input Tahun Lahir (angka)      : "; fflush(stdin); cin >> yy;
                // cout << "Input Tahun masuk (angka)      : "; fflush(stdin); cin >> tm;
                mahasiswa tmp = mahasiswa(id, nama, dd, mm, yy, nrp, dept, tm);
                recMhs.push_back(tmp);
				break;
            }
			case 2:
            {
                string nama, id, npp, dept; 
                int dd, mm, yy, pd;
                vector<string> prompt = {
                    "Input nama                     : ", "Input id                       : ",
                    "Input npp                      : ", "Input Departement              : ",
                    "Input Tanggal Lahir (angka)    : ", "Input Bulan Lahir (angka)      : ",
                    "Input Tahun Lahir (angka)      : ", "Input Pendidikan (angka)       : ",
                };
                vector<string*> pStr = {&nama, &id, &npp, &dept};
                vector<int*> pInt = {&dd, &mm, &yy, &pd};
                input(prompt, pStr, pInt);
                dosen tmp = dosen(id, nama, dd, mm, yy, npp, dept, pd);
                recDosen.push_back(tmp);
				break;
            }
			case 3:
            {
                string nama, id, npp, unit; 
                int dd, mm, yy;
                vector<string> prompt = {
                    "Input nama                     : ", "Input id                       : ",
                    "Input npp                      : ", "Input Unit                     : ",
                    "Input Tanggal Lahir (angka)    : ", "Input Bulan Lahir (angka)      : ",
                    "Input Tahun Lahir (angka)      : ",
                };
                vector<string*> pStr = {&nama, &id, &npp, &unit};
                vector<int*> pInt = {&dd, &mm, &yy};
                input(prompt, pStr, pInt);
                tendik tmp = tendik(id, nama, dd, mm, yy, npp, unit);
                recTendik.push_back(tmp);
				break;
            }
			case 4:
            {
                int i = 1;
                for(auto a : recMhs)
                {
                    cout << "\n" << i++ << ".\n";
                    cout << "    Nama           : " << a.getNama() << endl;
                    cout << "    NRP            : " << a.getNRP() << endl;
                    cout << "    Departemen     : " << a.getDept() << endl;
                    cout << "    ID             : " << a.getId() << endl;
                    cout << "    Tanggal Lahir  : " << a.getTglLahir() << "/" << a.getBulanLahir() << "/" << a.getTahunLahir() << endl;
                    cout << "    Tahun Masuk    : " << a.getThnMsk() << endl;
                }
				break;
            }
			case 5:
            {
                int i = 1;
                for(auto a : recDosen)
                {
                    cout << "\n" << i++ << ".\n";
                    cout << "    Nama           : " << a.getNama() << endl;
                    cout << "    NPP            : " << a.getNPP() << endl;
                    cout << "    Departemen     : " << a.getDept() << endl;
                    cout << "    ID             : " << a.getId() << endl;
                    cout << "    Tanggal Lahir  : " << a.getTglLahir() << "/" << a.getBulanLahir() << "/" << a.getTahunLahir() << endl;
                    cout << "    Pendidikan     : " << a.getPendidikan() << endl;
                }
				break;
            }
			case 6:
			{
                int i = 1;
                for(auto a : recTendik)
                {
                    cout << "\n" << i++ << ".\n";
                    cout << "    Nama           : " << a.getNama() << endl;
                    cout << "    NPP            : " << a.getNPP() << endl;
                    cout << "    Unit           : " << a.getUnit() << endl;
                    cout << "    ID             : " << a.getId() << endl;
                    cout << "    Tanggal Lahir  : " << a.getTglLahir() << "/" << a.getBulanLahir() << "/" << a.getTahunLahir() << endl;
                }
				break;
            }
		}
	}

	return 0;
}
