#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

//untuk djikstra
#define ii pair<int, int>
vector<vector<ii>> graph;

struct produk {
    int id;
    string nama_produk;
    string kategori;
    int harga;
};

struct keranjang {
    produk item;
    int jumlah;
};

class toko_online {
private:
    vector<produk> products;
    vector<keranjang> cart;
    vector<int> riwayat;
    map<int, vector<keranjang>> detail_transaksi; // Hash map untuk menyimpan detail transaksi

public:
    // Penyusunan data produk
    toko_online() {
        products = {
            {1, "Smartphone Samsung Galaxy S23", "Elektronik", 12000000},
            {2, "Laptop ASUS ROG Zephyrus G14", "Elektronik", 25000000},
            {3, "TV LED LG 43 Inch", "Elektronik", 6500000},
            {4, "Earbuds Apple AirPods Pro", "Elektronik", 3500000},
            {5, "Kamera DSLR Canon EOS 90D", "Elektronik", 17000000},
            {6, "Sepeda MTB Polygon", "Fitness", 5000000},
            {7, "Dumbbell 5kg", "Fitness", 200000},
            {8, "Matras Yoga", "Fitness", 250000},
            {9, "Mesin Elliptical", "Fitness", 7500000},
            {10, "Resistance Band", "Fitness", 100000},
            {11, "Serum Wajah Vitamin C", "Kecantikan", 150000},
            {12, "Masker Wajah Aloe Vera", "Kecantikan", 75000},
            {13, "Lipstik Matte L'Oréal", "Kecantikan", 120000},
            {14, "Parfum Chanel", "Kecantikan", 2500000},
            {15, "Sabun Cuci Muka Himalaya", "Kecantikan", 35000},
            {16, "Roti Tawar Serba Roti", "Konsumsi", 15000},
            {17, "Kopi Arabica 100g", "Konsumsi", 50000},
            {18, "Mie Instan", "Konsumsi", 5000},
            {19, "Susu UHT Indomilk 1 Liter", "Konsumsi", 18000},
            {20, "Teh Kotak Sosro 500ml", "Konsumsi", 7500}
        };
    }

    // Menampilkan daftar produk
    void tampilkan_produk() {
        cout << "\n==================================================================\n";
        cout << "||Daftar Produk:                                                ||\n";
        cout << "==================================================================\n";
        cout << left << setw(5) << "ID"
             << setw(30) << "Nama Produk"
             << setw(15) << "Kategori"
             << setw(10) << "Harga ||" << endl;

        for (const auto &produk : products) {
            cout << left << setw(5) << produk.id
                 << setw(30) << produk.nama_produk
                 << setw(15) << produk.kategori
                 << setw(10) << produk.harga << endl;
        }
        cout << "==================================================================\n";
    }

    // No 1: Sortir produk berdasarkan kategori dan harga
    void urutkan(int kategori_produk, int urutan_harga) {
        string jenis_kategori;

        switch (kategori_produk) {
            case 1: jenis_kategori = "Elektronik"; break;
            case 2: jenis_kategori = "Fitness"; break;
            case 3: jenis_kategori = "Kecantikan"; break;
            case 4: jenis_kategori = "Konsumsi"; break;
            default:
                cout << "[ERROR] Kategori tidak valid.\n";
                system("pause");
                return;
        }

        vector<produk> produk_filter;
        for (auto Produk : products) {
            if (Produk.kategori == jenis_kategori) { 
                produk_filter.push_back(Produk);
            }
        }

        if (produk_filter.empty()) {
            cout << "[ERROR] Tidak ada produk dalam kategori " << jenis_kategori << ".\n";
            system("pause");
            return;
        }

        if (urutan_harga == 5) { 
            sort(produk_filter.begin(), produk_filter.end(), [](produk a, produk b) { 
                return a.harga < b.harga;
            });
        } else if (urutan_harga == 6) { 
            sort(produk_filter.begin(), produk_filter.end(), [](produk a, produk b) {
                return a.harga > b.harga;
            });
        } else {
            cout << "[ERROR] Urutan harga tidak valid.\n";
            system("pause");
            return;
        }

        cout << "\n==================================================================\n";
        cout << "||Produk dalam kategori \"" << jenis_kategori << "\" diurutkan berdasarkan harga: ||\n";
        cout << "==================================================================\n";

        cout << left << setw(5) << "ID" 
             << setw(30) << "Nama Produk" 
             << setw(10) << "Harga" << endl; 

        for (auto Produk : produk_filter) {
            cout << left << setw(5) << Produk.id 
                 << setw(30) << Produk.nama_produk 
                 << setw(10) << Produk.harga << endl;
        }
        cout << "==================================================================\n\n";
        system("pause");
        cout << "\n------------------------------------------------------------------\n\n";
    }

    // No 2: Menambah produk ke keranjang
    void tambah_ke_keranjang(int id_produk, int jumlah_produk) {
        auto it = find_if(products.begin(), products.end(), [id_produk](const produk& p) {
            return p.id == id_produk;
        });

        if (it != products.end()) {
            auto it_cart = find_if(cart.begin(), cart.end(), [id_produk](const keranjang& k) {
                return k.item.id == id_produk;
            });

            if (it_cart != cart.end()) {
                it_cart->jumlah += jumlah_produk; 
                cout << "[INFO] Jumlah produk \"" << it->nama_produk << "\" di keranjang telah diperbarui.\n";
            } else {
                cart.push_back({*it, jumlah_produk}); 
                cout << "[INFO] Produk \"" << it->nama_produk << "\" berhasil ditambahkan ke keranjang belanja.\n";
            }
        } else {
            cout << "[ERROR] Produk dengan ID " << id_produk << " tidak ditemukan.\n";
        }

        system("pause");
        cout << "\n------------------------------------------------------------------\n\n";
    }

    // No 3: Mencari produk berdasarkan id
    void cari_produk_by_id(int id_produk) {
        auto it = find_if(products.begin(), products.end(), [id_produk](const produk& p) {
            return p.id == id_produk;
        });

        if (it != products.end()) {
            cout << "\n[INFO] Produk ditemukan:\n";
            cout << "==================================================================\n";
            cout << left << setw(5) << "ID"
                << setw(30) << "Nama Produk"
                << setw(15) << "Kategori"
                << setw(10) << "Harga" << endl;
            cout << left << setw(5) << it->id
                << setw(30) << it->nama_produk
                << setw(15) << it->kategori
                << setw(10) << it->harga << endl;
            cout << "==================================================================\n";
        } else {
            cout << "[ERROR] Produk dengan ID " << id_produk << " tidak ditemukan.\n";
        }

        system("pause");
        cout << "\n------------------------------------------------------------------\n\n";        
    }

    // No 4: Melihat daftar produk di keranjang
    void tampilkan_keranjang() {
        if (cart.empty()) {
            cout << "\n[INFO] Keranjang belanja kosong.\n";
            system("pause");
            return;
        }

        cout << "\n==================================================================\n";
        cout << "||Keranjang Belanja:                                            ||\n";
        cout << "==================================================================\n";
        cout << left << setw(5) << "ID"
             << setw(30) << "Nama Produk"
             << setw(10) << "Jumlah"
             << setw(15) << "Harga Total" << endl;

        for (const auto &item : cart) {
            cout << left << setw(5) << item.item.id
                 << setw(30) << item.item.nama_produk
                 << setw(10) << item.jumlah
                 << setw(15) << (item.item.harga * item.jumlah) << endl;
        }
        cout << "==================================================================\n";
    }

    // No 5: Menghapus produk dari keranjang
    void hapus_dari_keranjang(int id_produk) {
        auto it = find_if(cart.begin(), cart.end(), [id_produk](const keranjang& k) {
            return k.item.id == id_produk;
        });

        if (it != cart.end()) {
            cout << "Produk \"" << it->item.nama_produk << "\" telah dihapus dari keranjang.\n";
            cart.erase(it); // Hapus produk dari keranjang
        } else {
            cout << "Produk dengan ID " << id_produk << " tidak ditemukan di keranjang.\n";
        }

        system("pause");
        cout << "\n------------------------------------------------------------------\n\n";
    }

    // No 6: Menghitung biaya berdasarkan jarak (shortest path)
    int dijkstra(int start, int end, int N) {
        vector<int> dist(N, INT_MAX);
        dist[start] = 0;

        priority_queue<ii, vector<ii>, greater<ii>> pq;
        pq.push({0, start}); 

        while (!pq.empty()) {
            int curr_time = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            if (curr_time > dist[node])
                continue;

            for (auto neighbor : graph[node]) {
                int next_node = neighbor.first;
                int time = neighbor.second;

                if (curr_time + time < dist[next_node]) {
                    dist[next_node] = curr_time + time;
                    pq.push({dist[next_node], next_node});
                }
            }
        }

        return dist[end];
    }

    // Function untuk membuat template graph dan inputan sumber serta tujuan lokasi
    void shortest_path() {
        graph.resize(10);

        graph[0].push_back({3, 4});
        graph[0].push_back({6, 4});
        graph[0].push_back({8, 5});
        graph[0].push_back({2, 7});
        graph[2].push_back({1, 5});
        graph[6].push_back({1, 4});
        graph[6].push_back({5, 11});
        graph[8].push_back({5, 10});
        graph[6].push_back({4, 2});
        graph[4].push_back({7, 7});
        graph[5].push_back({4, 9});
        graph[5].push_back({7, 8});
        graph[5].push_back({9, 3});
        graph[9].push_back({7, 4});

        int akhir;
        cout << "Masukkan lokasi tujuan: ";
        cin >> akhir;

        int result = dijkstra(0, akhir, 10);

        if (result == INT_MAX) {
            cout << "\n[ERROR] Jarak dari toko ke lokasi " << akhir << " tidak terjangkau" << endl;
        } else {
            printf("\n[INFO] Jarak dari toko ke lokasi tujuan %d adalah %d km, maka total biaya pengiriman adalah Rp%d,- \n", akhir, result, result * 3000);
        }

        system("pause");
        cout << "\n------------------------------------------------------------------\n\n";
    }

    // No 7: Pembayaran dan penyimpanan riwayat pembayaran
    void pembayaran() {
        int total = 0;

        if (cart.empty()) {
            return;
        }

        for (const auto &item : cart) {
            total += item.item.harga * item.jumlah;
        }

        cout << "\nTotal biaya yang harus dibayar: Rp" << total << ",-\n";
        cout << "Apakah Anda ingin melanjutkan pembayaran? (y/n): ";
        char konfirmasi;
        cin >> konfirmasi;

        if (konfirmasi == 'y' || konfirmasi == 'Y') {
            cout << "[INFO] Pembayaran berhasil dilakukan. Terima kasih atas pembelian Anda!\n";
            riwayat.push_back(total);
            int id_transaksi = riwayat.size(); // ID transaksi 
            detail_transaksi[id_transaksi] = cart; // Simpan detail transaksi
            cart.clear();
        } else {
            cout << "[INFO] Pembayaran dibatalkan.\n";
        }

        system("pause");
        cout << "\n------------------------------------------------------------------\n\n";
    }

    // No 8: Melihat riwayat pembayaran
    void lihat_riwayat_pembayaran() {
        if (riwayat.empty()) {
            cout << "\n[INFO] Belum ada riwayat pembayaran.\n";
            system("pause");
            return;
        }

        cout << "\n==================================================================\n";
        cout << "||Riwayat Pembayaran:                                            ||\n";
        cout << "==================================================================\n";

        for (size_t i = 0; i < riwayat.size(); ++i) {
            cout << "Transaksi ke-" << i + 1 << ": Rp"<< riwayat[i] << ",-\n";
        }

        cout << "==================================================================\n";
        system("pause");
        cout << "\n------------------------------------------------------------------\n\n";
    }

    // No 9: Melihat detail transaksi dari setiap riwayat pembayaran
    void lihat_detail_transaksi() {
        if (detail_transaksi.empty()) {
            cout << "\n[INFO] Belum ada detail transaksi.\n";
                system("pause");
            return;
        }

        int akhir;
        cout << "Masukkan lokasi tujuan: ";
        cin >> akhir;

        
        cout << "\n==================================================================\n";
        cout << "||Detail Riwayat Transaksi:                                     ||\n";
        cout << "==================================================================\n";

        for (const auto& [id_transaksi, items] : detail_transaksi) {
            cout << "Transaksi ke-" << id_transaksi << ":\n";
            cout << left << setw(5) << "ID"
                 << setw(30) << "Nama Produk"
                 << setw(10) << "Jumlah"
                 << setw(15) << "Harga Total" << endl;

            for (const auto& item : items) {
                cout << left << setw(5) << item.item.id
                     << setw(30) << item.item.nama_produk
                     << setw(10) << item.jumlah
                     << setw(15) << (item.item.harga * item.jumlah) << endl;
            }
            cout << "------------------------------------------------------------------\n";
        }

        graph.resize(10);
        graph[0].push_back({3, 4});
        graph[0].push_back({6, 4});
        graph[0].push_back({8, 5});
        graph[0].push_back({2, 7});
        graph[2].push_back({1, 5});
        graph[6].push_back({1, 4});
        graph[6].push_back({5, 11});
        graph[8].push_back({5, 10});
        graph[6].push_back({4, 2});
        graph[4].push_back({7, 7});
        graph[5].push_back({4, 9});
        graph[5].push_back({7, 8});
        graph[5].push_back({9, 3});
        graph[9].push_back({7, 4});

        int result = dijkstra(0, akhir, 10);

        cout << "Biaya ongkos kirim = " << result*3000 << endl;

        cout << "==================================================================\n";
            system("pause");
        cout << "------------------------------------------------------------------\n";

    }
};

int main() {
    system("CLS");

    int pilihan;
    toko_online store;

    do {
        cout << "==================================================================\n";
        cout << "                  SELAMAT DATANG DI TOKO ONLINE                   \n";
        cout << "==================================================================\n";
        cout << "|| Fitur yang dapat digunakan:                                  ||\n";
        cout << "||1. Sortir produk berdasarkan kategori dan harga               ||\n";
        cout << "||2. Menambahkan produk ke keranjang belanja                    ||\n";
        cout << "||3. Mencari produk berdasarkan ID                              ||\n";
        cout << "||4. Melihat daftar barang di keranjang                         ||\n";
        cout << "||5. Menghapus barang dari keranjang                            ||\n";
        cout << "||6. Menghitung biaya pengiriman berdasarkan jarak              ||\n";
        cout << "||7. Melakukan pembayaran dan menyimpan riwayat pembayaran      ||\n";
        cout << "||8. Melihat riwayat pembayaran                                 ||\n";
        cout << "||9. Melihat detail setiap transaksi pada riwayat pembayaran    ||\n";
        cout << "||10. Keluar                                                    ||\n";
        cout << "==================================================================\n";
        cout << "Masukan fitur yang ingin digunakan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                int kategori_produk, urutan_harga;

            do {
                    cout << "\n------------------------------------------------------------------\n\n";
                    cout << "==================================================================\n";
                    cout << "||Sortir produk berdasarkan kategori dan harga apa?             ||\n";
                    cout << "==================================================================\n";
                    cout << "||1. Elektronik                                                 ||\n";
                    cout << "||2. Fitness                                                    ||\n";
                    cout << "||3. Kecantikan                                                 ||\n";
                    cout << "||4. Konsumsi                                                   ||\n";
                    cout << "||5. Termurah                                                   ||\n";
                    cout << "||6. Termahal                                                   ||\n";
                    cout << "==================================================================\n";
                    cout << "  Masukan kategori dan harga produk yang ingin dilihat: ";

                    cin >> kategori_produk >> urutan_harga;

                    if ((kategori_produk >= 1 && kategori_produk <= 4) && (urutan_harga == 5 || urutan_harga == 6)) {
                        store.urutkan(kategori_produk, urutan_harga);
                        break;
                    } else {
                        cout << "[ERROR] Masukan tidak valid! Ulangi input.\n\n";
                        system("pause");
                    }
                } while (true);
                break;
            }

            case 2: {
                int id_product, jumlah_produk;

                store.tampilkan_produk();
                cout << "Masukan ID produk dan jumlah yang ingin dimasukkan ke keranjang: ";
                cin >> id_product >> jumlah_produk;
                store.tambah_ke_keranjang(id_product, jumlah_produk);
                break;
            }

            case 3: {
                int id_produk;
                cout << "Masukkan ID produk yang ingin dicari: ";
                cin >> id_produk;
                store.cari_produk_by_id(id_produk);
                break;
            }

            case 4: {
                store.tampilkan_keranjang();
                    system("pause");
                cout << "\n\n------------------------------------------------------------------\n\n";
                break;
            }

            case 5: {
                int id_produk;
                cout << "Masukkan ID produk yang ingin dihapus dari keranjang: ";
                cin >> id_produk;
                store.hapus_dari_keranjang(id_produk);
                break;
            }

            case 6: {
                store.shortest_path();
                break;
            }

            case 7: {
                store.tampilkan_keranjang();
                store.pembayaran();
                break;
            }

            case 8: {
                store.lihat_riwayat_pembayaran();
                break;
            }

            case 9: {
                store.lihat_detail_transaksi();
                break;
            }

            case 10: {
                cout << "Terima kasih sudah menggunakan program ini!!!\n";
                break;
            }
            default: {
                cout << "[ERROR] Nomor tidak valid, silahkan masukan nomor yang valid!\n";
                system("pause");
                continue;
            }
        }
    } while (pilihan != 10);
    return 0;
}