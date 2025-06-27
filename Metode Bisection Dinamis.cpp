#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

// Fungsi 1: Polinomial default dari soal
double fungsi1(double T) {
    return (-0.50598e-10) * T * T * T + (0.38292e-7) * T * T + (0.74363e-4) * T + (0.88318e-2);
}

// Fungsi 2: Contoh fungsi lain (bisa kamu ganti)
double fungsi2(double x) {
    return sin(x) - x / 2;
}

// Fungsi Bisection umum untuk dua fungsi
void bisection(double (*f)(double), double a, double b, double toleransi, int max_iter) {
    ofstream file("hasil_iterasi.csv");
    file << "Iterasi,a,b,c,f(c)\n";

    double c;
    int i = 0;

    cout << "\nIterasi\ta\t\tb\t\tc\t\tf(c)\n";

    if (f(a) * f(b) >= 0) {
        cout << "Fungsi tidak memenuhi syarat f(a)*f(b) < 0. Tidak ada akar pada interval tersebut.\n";
        return;
    }

    do {
        c = (a + b) / 2;
        i++;

        cout << i << "\t" << a << "\t" << b << "\t" << c << "\t" << f(c) << endl;
        file << i << "," << a << "," << b << "," << c << "," << f(c) << "\n";

        if (f(a) * f(c) < 0)
            b = c;
        else
            a = c;

        if (i >= max_iter) {
            cout << "\nMaksimum iterasi (" << max_iter << ") tercapai. Akar hampiran terakhir: " << c << endl;
            break;
        }

    } while (fabs(f(c)) > toleransi);

    if (fabs(f(c)) <= toleransi)
        cout << "\nAkar hampiran = " << c << " dengan f(c) = " << f(c) << "\n";

    file.close();

    // Simpan grafik fungsi ke file
    ofstream grafik("grafik_fungsi.csv");
    for (double x = a - 5; x <= b + 5; x += 0.1) {
        grafik << x << "," << f(x) << "\n";
    }
    grafik.close();
    cout << "Data grafik disimpan di 'grafik_fungsi.csv'\n";
}

int main() {
    double a, b, toleransi;
    int max_iter, pilihan;

    cout << "====== PROGRAM METODE NUMERIK (BISECTION) ======\n";
    cout << "Pilih fungsi:\n";
    cout << "1. Fungsi default soal (polinomial)\n";
    cout << "2. Fungsi f(x) = sin(x) - x/2\n";
    cout << "Masukkan pilihan (1 atau 2): ";
    cin >> pilihan;

    cout << "\nMasukkan batas bawah (a): ";
    cin >> a;
    cout << "Masukkan batas atas (b): ";
    cin >> b;

    if (a >= b) {
        cout << "Batas bawah harus lebih kecil dari batas atas!\n";
        return 1;
    }

    cout << "Masukkan toleransi error (misal 0.0001): ";
    cin >> toleransi;

    cout << "Masukkan jumlah iterasi maksimum: ";
    cin >> max_iter;

    // Tentukan fungsi yang digunakan
    if (pilihan == 1) {
        bisection(fungsi1, a, b, toleransi, max_iter);
    } else if (pilihan == 2) {
        bisection(fungsi2, a, b, toleransi, max_iter);
    } else {
        cout << "Pilihan tidak valid.\n";
    }

    cout << "\nHasil iterasi disimpan dalam file 'hasil_iterasi.csv'\n";
    return 0;
}

// Nama : Hafizh Hilman Asyhari
// Github : hafizhhasyhari
// Tahun : 2025
