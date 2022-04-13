#include <iostream>
#include <vector>

#include "include/person.hpp"
#include "include/mahasiswa.hpp"
#include "include/dosen.hpp"
#include "include/tendik.hpp"

using namespace std;

/**
 * @brief Fungsi untuk mengambil data
 * 
 * Fungsi ini dibuat untuk mengambil data-data yang berulang pada case 1 s/d 3
 * seperti nama, npp/nrp, id, tanggal lahir, departemen, dan lainnya, agar tidak terjadi 
 * kode berulang yang dapat mengurangi keterbacaan kode.
 * 
 * @param prompt referensi dari vektor yang mengandung string untuk memberi konteks input
 * 
 * seperti "Input nama : ", "Input id : ", dsb.
 * 
 * @param pStr referensi dari vektor yang mengandung pointer data input yang berupa string
 * 
 * seperti nama, id, nrp, departement, dsb.
 * 
 * @param pInt referensi dari vektor yang mengandung pointer data input integer
 * 
 * seperti tanggal, bulan, dan tahun lahir, tahun masuk, sks Lulus, semester, dsb.
 * 
 */
void getInput(vector<string>& prompt, vector<string*>& pStr, vector<int*>& pInt)
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
    bool loopContinue = 1;
	while(loopContinue) {
        // display menu
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
        cout << "  7. Keluar" << endl;
		cout << "-> Silahkan memilih salah satu: ";

        // mengambil pilihan menu user
		fflush(stdin); cin >> menu_terpilih;
        
        // switch case sesuai pada pilihan user
		switch (menu_terpilih) {
            
			case 1: // input mahasiswa baru
            {
                // deklarasi variabel string dan int
                string nama, id, nrp, dept; 
                int dd, mm, yy, tm, sksLulus, semester;

                // definisi vektor string untuk ditampilkan ke terminal
                // untuk menjadi konteks input data mahasiswa
                vector<string> prompt = {
                    "Input nama                     : ", "Input id                       : ",
                    "Input nrp                      : ", "Input Departement              : ",
                    "Input Tanggal Lahir (int)      : ", "Input Bulan Lahir (int)        : ", 
                    "Input Tahun Lahir (int)        : ", "Input Tahun masuk (int)        : ", 
                    "Input SKS Lulus (int)          : ", "Input Semester ke (int)        : "
                };

                // menggabungkan pointer dari masing-masing variabel input kedalam sebuah vektor 
                vector<string*> pStr = {&nama, &id, &nrp, &dept};
                vector<int*> pInt = {&dd, &mm, &yy, &tm, &sksLulus, &semester};

                // mengambil input
                getInput(prompt, pStr, pInt);

                // deklarasi objek mahasiswa baru
                mahasiswa tmp = mahasiswa(id, nama, dd, mm, yy, nrp, dept, tm);

                // set nilai semester dan sks lulus menggunakan fungsi setter dari kelas
                tmp.setSKSLulus(sksLulus); tmp.setSemester(semester = semester < 1? 1 : semester > 14? 14 : semester);

                // input nilai sks untuk masing-masing semester
                for(int i = 0; i < semester; i++)
                {
                    float ipsTmp;
                    std::cout << "IPS Semester ke " << i + 1 << " (int)      : "; fflush(stdin); cin >> ipsTmp;
                    tmp.setIPS(i+1, ipsTmp);
                }

                // masukkan objek mahasiswa yang telah dibuat kedalam vektor mahasiswa
                recMhs.push_back(tmp);
				break;
            }
            
			case 2: // input dosen baru
            {
                // deklarasi variabel string dan int
                string nama, id, npp, dept; 
                int dd, mm, yy, pd;

                // definisi vektor string untuk ditampilkan ke terminal 
                // untuk menjadi konteks input data dosen
                vector<string> prompt = {
                    "Input nama                     : ", "Input id                       : ",
                    "Input npp                      : ", "Input Departement              : ",
                    "Input Tanggal Lahir (angka)    : ", "Input Bulan Lahir (angka)      : ",
                    "Input Tahun Lahir (angka)      : ", "Input Pendidikan (angka)       : ",
                };

                // menggabungkan pointer dari masing-masing variabel input kedalam sebuah vektor 
                vector<string*> pStr = {&nama, &id, &npp, &dept};
                vector<int*> pInt = {&dd, &mm, &yy, &pd};

                // mengambil input
                getInput(prompt, pStr, pInt);

                // deklarasi objek dosen baru
                dosen tmp = dosen(id, nama, dd, mm, yy, npp, dept, pd);
                
                // masukkan objek dosen yang telah dibuat kedalam vektor dosen
                recDosen.push_back(tmp);
				break;
            }
            
			case 3: // input tendik baru
            {
                // deklarasi variabel string dan int
                string nama, id, npp, unit; 
                int dd, mm, yy;

                // definisi vektor string untuk ditampilkan ke terminal 
                // untuk menjadi konteks input data tendik
                vector<string> prompt = {
                    "Input nama                     : ", "Input id                       : ",
                    "Input npp                      : ", "Input Unit                     : ",
                    "Input Tanggal Lahir (angka)    : ", "Input Bulan Lahir (angka)      : ",
                    "Input Tahun Lahir (angka)      : ",
                };

                // menggabungkan pointer dari masing-masing variabel input kedalam sebuah vektor 
                vector<string*> pStr = {&nama, &id, &npp, &unit};
                vector<int*> pInt = {&dd, &mm, &yy};

                // mengambil input
                getInput(prompt, pStr, pInt);

                // deklarasi objek tendik baru
                tendik tmp = tendik(id, nama, dd, mm, yy, npp, unit);

                // masukkan objek tendik yang telah dibuat kedalam vektor tendik
                recTendik.push_back(tmp);
				break;
            }
			case 4: // tampilkan data mahasiswa
            {
                // definisi counter i menjadi 1
                int i = 1;

                // tampilkan jumlah mahasiswa di dalam sistem
                cout << "Terdapat " << recMhs.size() << " Mahasiswa di dalam sistem ini." << endl;

                // iterasikan variabel a dari setiap objek di recMhs
                for(auto a : recMhs)
                {
                    // tampilkan data tiap mahasiswa
                    cout << "\n" << i++ << ".\n";
                    cout << "    Nama           : " << a.getNama() << endl;
                    cout << "    NRP            : " << a.getNRP() << endl;
                    cout << "    Departemen     : " << a.getDept() << endl;
                    cout << "    ID             : " << a.getId() << endl;
                    cout << "    Tanggal Lahir  : " << a.getTglLahir() << "/" << a.getBulanLahir() << "/" << a.getTahunLahir() << endl;
                    cout << "    Tahun Masuk    : " << a.getThnMsk() << endl;
                    cout << "    Semester Ke    : " << a.getSemester() << endl;
                    cout << "    SKS Lulus      : " << a.getSKSLulus() << endl;
                    cout << "    Tahun Masuk    : " << a.getThnMsk() << endl;
                    cout << "    IPK            : " << a.getIPK() << endl;
                    cout << "    IPS            : { " ;

                    // for loop untuk menampilkan nilai sks dalam bentuk array C
                    for(int j=0, comma=0; j < a.getSemester(); j++, comma=1)
                        cout << ((comma)? ", " : "") << a.getIPS(j+1);
                    cout << " }" << endl;

                }
                
				break;
            }
			case 5: // tampilkan data dosen
            {
                // definisi counter i menjadi 1
                int i = 1;

                // tampilkan jumlah dosen di dalam sistem
                cout << "Terdapat " << recDosen.size() << " Dosen di dalam sistem ini." << endl;

                // iterasikan variabel a pada setiap objek di recDosen
                for(auto a : recDosen)
                {
                    // tampilkan data dosen
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
			case 6: // tampilkan data tendik
			{
                // definisi counter i menjadi 1
                int i = 1;
                
                // tampilkan jumlah dosen di dalam sistem
                cout << "Terdapat " << recTendik.size() << " Tendik di dalam sistem ini." << endl;

                // iterasikan variabel a pada setiap objek di recDosen
                for(auto a : recTendik)
                {
                    // tampilkan data dosen
                    cout << "\n" << i++ << ".\n";
                    cout << "    Nama           : " << a.getNama() << endl;
                    cout << "    NPP            : " << a.getNPP() << endl;
                    cout << "    Unit           : " << a.getUnit() << endl;
                    cout << "    ID             : " << a.getId() << endl;
                    cout << "    Tanggal Lahir  : " << a.getTglLahir() << "/" << a.getBulanLahir() << "/" << a.getTahunLahir() << endl;
                }
				break;
            }
            case 7: // keluar dari program
                cout << "Berhasil Keluar dari Program";
                loopContinue = 0;
                break;
		}
	}

	return 0;
}
