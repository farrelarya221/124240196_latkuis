#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iomanip>

using namespace std;

struct Pegawai {
    int id;
    char nama[100];
    double gaji;
};

char NAMA_FILE[] = "pegawai.dat";
int MAX_PEGAWAI = 100;

void tambahPegawai();
void lihatDaftarPegawai();
void cariPegawai();
void perbaruiGaji();
int bacaFile(Pegawai daftarPegawai[]);
void tulisFile(Pegawai daftarPegawai[], int jumlahPegawai);
void tampilkanPegawai(Pegawai pegawai);
void urutkanPegawai(Pegawai daftarPegawai[], int jumlahPegawai);

int main() {
    int pilihan;
    int lanjut = 1;

    while (lanjut) {
        cout << "\n==== SISTEM INFORMASI KEPEGAWAIAN ====\n";
        cout << "1. Tambah Data Pegawai\n";
        cout << "2. Lihat Daftar Pegawai\n";
        cout << "3. Cari Pegawai Berdasarkan ID\n";
        cout << "4. Perbarui Gaji Pegawai\n";
        cout << "5. Keluar dari Program\n";
        cout << "Pilih menu (1-5): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahPegawai();
                break;
            case 2:
                lihatDaftarPegawai();
                break;
            case 3:
                cariPegawai();
                break;
            case 4:
                perbaruiGaji();
                break;
            case 5:
                lanjut = 0;
                cout << "Terima kasih telah menggunakan program ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    }

    return 0;
}

void tambahPegawai() {
    Pegawai daftarPegawai[100]; 
    int jumlahPegawai = bacaFile(daftarPegawai);
    Pegawai pegawai;
    char lanjut;
    
    do {
        cout << "\n==== TAMBAH DATA PEGAWAI ====\n";
        cout << "ID Pegawai: ";
        cin >> pegawai.id;
        
        int idSudahAda = 0;
        for (int i = 0; i < jumlahPegawai; i++) {
            if (daftarPegawai[i].id == pegawai.id) {
                idSudahAda = 1;
                break;
            }
        }
        
        if (idSudahAda) {
            cout << "ID " << pegawai.id << " sudah digunakan. Silakan gunakan ID lain.\n";
            continue;
        }
        
        cin.ignore();
        cout << "Nama Pegawai: ";
        cin.getline(pegawai.nama, 100);
        cout << "Gaji Pegawai: ";
        cin >> pegawai.gaji;
        
        if (jumlahPegawai < MAX_PEGAWAI) {
            daftarPegawai[jumlahPegawai] = pegawai;
            jumlahPegawai++;
        } else {
            cout << "Penyimpanan penuh. Tidak dapat menambah pegawai baru.\n";
            break;
        }
        
        cout << "Tambah data pegawai lagi? (y/n): ";
        cin >> lanjut;
    } while (lanjut == 'y' || lanjut == 'Y');
    
    tulisFile(daftarPegawai, jumlahPegawai);
    cout << "Data pegawai berhasil disimpan.\n";
}

void lihatDaftarPegawai() {
    Pegawai daftarPegawai[100];
    int jumlahPegawai = bacaFile(daftarPegawai);
    
    if (jumlahPegawai == 0) {
        cout << "Tidak ada data pegawai yang tersedia.\n";
        return;
    }
    urutkanPegawai(daftarPegawai, jumlahPegawai);
    cout << "\n==== DAFTAR PEGAWAI ====\n";
    cout << setw(5) << "ID" << setw(20) << "Nama" << setw(15) << "Gaji" << endl;
    for (int i = 0; i < 40; i++) cout << "-";
    cout << endl;
    
    for (int i = 0; i < jumlahPegawai; i++) {
        cout << setw(5) << daftarPegawai[i].id 
             << setw(20) << daftarPegawai[i].nama 
             << setw(15) << fixed << setprecision(2) << daftarPegawai[i].gaji << endl;
    }
}

void cariPegawai() {
    Pegawai daftarPegawai[100];
    int jumlahPegawai = bacaFile(daftarPegawai);
    int idCari;
    int ditemukan = 0;
    
    cout << "\n==== CARI PEGAWAI ====\n";
    cout << "Masukkan ID Pegawai: ";
    cin >> idCari;
    
    for (int i = 0; i < jumlahPegawai; i++) {
        if (daftarPegawai[i].id == idCari) {
            cout << "\nData Pegawai Ditemukan:\n";
            tampilkanPegawai(daftarPegawai[i]);
            ditemukan = 1;
            break;
        }
    }
    
    if (ditemukan == 0) {
        cout << "Pegawai dengan ID " << idCari << " tidak ditemukan.\n";
    }
}
void perbaruiGaji() {
    Pegawai daftarPegawai[100];
    int jumlahPegawai = bacaFile(daftarPegawai);
    int idCari;
    int ditemukan = 0;
    
    cout << "\n==== PERBARUI GAJI PEGAWAI ====\n";
    cout << "Masukkan ID Pegawai: ";
    cin >> idCari;
    
    for (int i = 0; i < jumlahPegawai; i++) {
        if (daftarPegawai[i].id == idCari) {
            cout << "Data Pegawai Saat Ini:\n";
            tampilkanPegawai(daftarPegawai[i]);
            
            cout << "Masukkan Gaji Baru: ";
            cin >> daftarPegawai[i].gaji;
            
            tulisFile(daftarPegawai, jumlahPegawai);
            cout << "Gaji pegawai berhasil diperbarui.\n";
            ditemukan = 1;
            break;
        }
    }
    
    if (ditemukan == 0) {
        cout << "Pegawai dengan ID " << idCari << " tidak ditemukan.\n";
    }
}

int bacaFile(Pegawai daftarPegawai[]) {
    FILE *file = fopen(NAMA_FILE, "rb");
    int jumlahPegawai = 0;
    
    if (file != NULL) {
        while (fread(&daftarPegawai[jumlahPegawai], sizeof(Pegawai), 1, file) == 1 && jumlahPegawai < MAX_PEGAWAI) {
            jumlahPegawai++;
        }
        fclose(file);
    }
    return jumlahPegawai;
}

void tulisFile(Pegawai daftarPegawai[], int jumlahPegawai) {
    FILE *file = fopen(NAMA_FILE, "wb");
    
    if (file != NULL) {
        for (int i = 0; i < jumlahPegawai; i++) {
            fwrite(&daftarPegawai[i], sizeof(Pegawai), 1, file);
        }
        fclose(file);
    } else {
        cout << "Error: Tidak dapat membuka file untuk penulisan.\n";
    }
}

void tampilkanPegawai(Pegawai pegawai) {
    cout << "ID: " << pegawai.id << endl;
    cout << "Nama: " << pegawai.nama << endl;
    cout << "Gaji: " << fixed << setprecision(2) << pegawai.gaji << endl;
}

void urutkanPegawai(Pegawai daftarPegawai[], int jumlahPegawai) {
    for (int i = 0; i < jumlahPegawai - 1; i++) {
        for (int j = 0; j < jumlahPegawai - i - 1; j++) {
            if (daftarPegawai[j].id > daftarPegawai[j + 1].id) {
                Pegawai temp = daftarPegawai[j];
                daftarPegawai[j] = daftarPegawai[j + 1];
                daftarPegawai[j + 1] = temp;
            }
        }
    }
}
