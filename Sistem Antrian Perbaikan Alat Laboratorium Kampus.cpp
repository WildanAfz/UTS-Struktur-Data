#include <iostream>
#include <string>

using namespace std;

struct Node {
    string namaAlat;
    string tanggalRusak;
    string kodeRuangan;
    Node* next;
    
    Node(string nama, string tanggal, string kode)
        : namaAlat(nama), tanggalRusak(tanggal), kodeRuangan(kode), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    Node* tail;
    
public:
    LinkedList() : head(nullptr), tail(nullptr) {}
    
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    // 1. Menambahkan alat di akhir list
    void tambahAlat(string nama, string tanggal, string kode) {
        Node* newNode = new Node(nama, tanggal, kode);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        cout << "Alat berhasil ditambahkan!\n";
    }

    // 2. Menghapus alat dari awal list
    void hapusAlat() {
        if (head == nullptr) {
            cout << "Antrian kosong!\n";
            return;
        }
        
        Node* temp = head;
        head = head->next;
        if (head == nullptr) tail = nullptr;
        
        cout << "Alat yang dihapus:\n"
             << "Nama: " << temp->namaAlat << "\n"
             << "Tanggal Rusak: " << temp->tanggalRusak << "\n"
             << "Kode Ruangan: " << temp->kodeRuangan << "\n";
        
        delete temp;
    }

    // 3. Mencari alat berdasarkan kode ruangan
    Node* cariBerdasarkanRuangan(string kode) {
        Node* current = head;
        while (current != nullptr) {
            if (current->kodeRuangan == kode) return current;
            current = current->next;
        }
        return nullptr;
    }

    // 4. Menampilkan seluruh antrian
    void tampilkanAntrian() {
        if (head == nullptr) {
            cout << "Antrian kosong!\n";
            return;
        }
        
        Node* current = head;
        int counter = 1;
        while (current != nullptr) {
            cout << counter++ << ". " << current->namaAlat 
                 << " (Rusak: " << current->tanggalRusak 
                 << ", Ruang: " << current->kodeRuangan << ")\n";
            current = current->next;
        }
    }
};

int main() {
    LinkedList antrian;
    int pilihan;
    
    do {
        cout << "\n=== SISTEM ANTRIAN PERBAIKAN ALAT LAB ==="
             << "\n1. Tambah Alat Rusak"
             << "\n2. Perbaiki Alat (Hapus dari Antrian)"
             << "\n3. Cari Alat Berdasarkan Ruangan"
             << "\n4. Tampilkan Semua Antrian"
             << "\n0. Keluar"
             << "\nPilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch(pilihan) {
            case 1: {
                string nama, tanggal, kode;
                cout << "Nama Alat: "; getline(cin, nama);
                cout << "Tanggal Rusak (DD-MM-YYYY): "; getline(cin, tanggal);
                cout << "Kode Ruangan: "; getline(cin, kode);
                antrian.tambahAlat(nama, tanggal, kode);
                break;
            }
            case 2:
                antrian.hapusAlat();
                break;
            case 3: {
                string kode;
                cout << "Masukkan kode ruangan: "; getline(cin, kode);
                Node* hasil = antrian.cariBerdasarkanRuangan(kode);
                if (hasil) {
                    cout << "Ditemukan alat di ruang " << kode << ":\n"
                         << "Nama: " << hasil->namaAlat << "\n"
                         << "Tanggal Rusak: " << hasil->tanggalRusak << "\n";
                } else {
                    cout << "Tidak ditemukan alat di ruang " << kode << "\n";
                }
                break;
            }
            case 4:
                antrian.tampilkanAntrian();
                break;
        }
    } while (pilihan != 0);

    return 0;
}
