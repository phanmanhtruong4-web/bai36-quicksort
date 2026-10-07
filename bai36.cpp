#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// ==========================================
// CÂU 1: Định nghĩa cấu trúc Vé máy bay
// ==========================================
struct VeMayBay {
    int maVe;             // Mã vé (kiểu số nguyên)
    string khoiHanh;      // Khởi hành (chuỗi ký tự)
    string den;           // Đến (chuỗi ký tự)
    double giaVe;         // Giá vé (kiểu số thực)
};

// ==========================================
// CÂU 2: Hàm nhập mảng n vé máy bay
// ==========================================
void nhapDS(vector<VeMayBay> &ds, int n) {
    for (int i = 0; i < n; i++) {
        VeMayBay ve;
        cout << "\n--- Nhap thong tin ve may bay thu " << i + 1 << " ---\n";
        
        cout << "Ma ve (So nguyen): ";
        cin >> ve.maVe;
        
        cin.ignore(); // Xóa bộ nhớ đệm trước khi nhập chuỗi
        cout << "Noi khoi hanh: ";
        getline(cin, ve.khoiHanh);
        
        cout << "Noi den: ";
        getline(cin, ve.den);
        
        cout << "Gia ve: ";
        cin >> ve.giaVe;
        
        ds.push_back(ve);
    }
}

// ==========================================
// CÂU 3: Hàm xuất mảng n vé máy bay
// ==========================================
void xuatVeMayBay(const VeMayBay &ve) {
    cout << left << setw(10) << ve.maVe 
         << setw(20) << ve.khoiHanh 
         << setw(20) << ve.den 
         << right << setw(15) << fixed << setprecision(2) << ve.giaVe << endl;
}

void xuatDS(const vector<VeMayBay> &ds) {
    cout << "\n" << string(65, '=') << endl;
    cout << left << setw(10) << "Ma Ve" 
         << setw(20) << "Khoi Hanh" 
         << setw(20) << "Den" 
         << right << setw(15) << "Gia Ve" << endl;
    cout << string(65, '-') << endl;
    
    for (const auto &ve : ds) {
        xuatVeMayBay(ve);
    }
    cout << string(65, '=') << endl;
}

// ==========================================
// CÂU 4: Sắp xếp nhanh (Quick Sort)
// Sắp xếp tăng dần theo giá vé
// ==========================================
int partition(vector<VeMayBay> &ds, int low, int high) {
    double pivot = ds[high].giaVe;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (ds[j].giaVe <= pivot) {
            i++;
            swap(ds[i], ds[j]);
        }
    }
    swap(ds[i + 1], ds[high]);
    return i + 1;
}

void quickSort(vector<VeMayBay> &ds, int low, int high) {
    if (low < high) {
        int pi = partition(ds, low, high);
        quickSort(ds, low, pi - 1);
        quickSort(ds, pi + 1, high);
    }
}

// ==========================================
// CÂU 5: Tìm kiếm nhị phân (Chia để trị)
// Tìm các vé máy bay có giá vé bằng X
// ==========================================
int binarySearchFirst(const vector<VeMayBay> &ds, double X) {
    int left = 0, right = ds.size() - 1;
    int res = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (ds[mid].giaVe == X) {
            res = mid;
            right = mid - 1; // Tiếp tục tìm vị trí xuất hiện đầu tiên bên trái
        } else if (ds[mid].giaVe < X) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return res;
}

void timKiemTheoGia(const vector<VeMayBay> &ds, double X) {
    int firstIdx = binarySearchFirst(ds, X);
    
    if (firstIdx == -1) {
        cout << "\n[!] Khong tim thay ve may bay nao co gia ve bang " << X << endl;
        return;
    }
    
    cout << "\n=== DANH SACH VE MAY BAY CO GIA VE BANG " << X << " ===";
    cout << "\n" << string(65, '=') << endl;
    cout << left << setw(10) << "Ma Ve" 
         << setw(20) << "Khoi Hanh" 
         << setw(20) << "Den" 
         << right << setw(15) << "Gia Ve" << endl;
    cout << string(65, '-') << endl;
    
    // In toàn bộ các vé máy bay liên tiếp có cùng giá X
    for (int i = firstIdx; i < (int)ds.size() && ds[i].giaVe == X; i++) {
        xuatVeMayBay(ds[i]);
    }
    cout << string(65, '=') << endl;
}

// ==========================================
// CÂU 6: Hàm chính (main)
// ==========================================
int main() {
    int n;
    vector<VeMayBay> ds;

    // 1. Nhập số lượng vé máy bay
    cout << "Nhap so luong ve may bay n: ";
    cin >> n;
    while (n <= 0) {
        cout << "So luong phai > 0. Nhap lai n: ";
        cin >> n;
    }

    nhapDS(ds, n);

    // Hiển thị danh sách vừa nhập
    cout << "\n=== DANH SACH VE MAY BAY VUA NHAP ===";
    xuatDS(ds);

    // 2. Sắp xếp danh sách tăng dần theo giá vé bằng Quick Sort
    quickSort(ds, 0, ds.size() - 1);
    cout << "\n=== DANH SACH VE MAY BAY SAU KHI SAP XEP TANG DAN THEO GIA VE ===";
    xuatDS(ds);

    // 3. Tìm kiếm nhị phân theo giá X
    double X;
    cout << "\nNhap gia ve X can tim: ";
    cin >> X;
    timKiemTheoGia(ds, X);

    return 0;
}
