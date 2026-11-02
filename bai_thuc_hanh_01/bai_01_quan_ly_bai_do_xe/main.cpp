#include <iostream>
#include <string>
#include <iomanip>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Lop mo ta thong tin mot phuong tien
class Xe {
private:
    int maXe;
    string loaiXe; // Car, Motorcycle, Bicycle
    int gioVao;
    int soGioDo;
    double phiDoXe;
    bool dangChiemCho;

    string chuanHoaLoai(const string& loai) const {
        string s = loai;
        if (s.empty()) return s;
        for (char &c : s) c = tolower(c);
        s[0] = toupper(s[0]);
        return s;
    }

public:
    Xe() : maXe(0), loaiXe(""), gioVao(0), soGioDo(0), phiDoXe(0.0), dangChiemCho(false) {}

    Xe(int ma, const string& loai, int gio, int thoiLuong)
        : maXe(ma), loaiXe(chuanHoaLoai(loai)), gioVao(gio),
          soGioDo(thoiLuong), phiDoXe(0.0), dangChiemCho(true) {
        tinhPhi();
    }

    int layMaXe() const { return maXe; }
    string layLoaiXe() const { return loaiXe; }
    int layGioVao() const { return gioVao; }
    int laySoGioDo() const { return soGioDo; }
    double layPhiDoXe() const { return phiDoXe; }
    bool layDangChiemCho() const { return dangChiemCho; }

    void ganMaXe(int ma) { maXe = ma; }
    void ganLoaiXe(const string& loai) { loaiXe = chuanHoaLoai(loai); }
    void ganGioVao(int gio) { gioVao = gio; }
    void ganSoGioDo(int tg) { soGioDo = tg; }
    void ganDangChiemCho(bool trangThai) { dangChiemCho = trangThai; }

    void tinhPhi() {
        if (!dangChiemCho || soGioDo <= 0) {
            phiDoXe = 0.0;
            return;
        }

        // Don gia theo gio
        double donGia = 2000.0;
        if (loaiXe == "Car")             donGia = 6000.0;
        else if (loaiXe == "Motorcycle") donGia = 4000.0;
        else if (loaiXe == "Bicycle")    donGia = 2000.0;

        // Gio cao diem: 6h-9h sang, 15h-18h chieu
        bool caoDiem = (gioVao >= 6 && gioVao < 10) || (gioVao >= 15 && gioVao < 19);

        double giaDau = caoDiem ? donGia * 1.30 : donGia * 0.95;
        double giaSau = donGia * 0.90;

        if (soGioDo <= 2)
            phiDoXe = soGioDo * giaDau;
        else
            phiDoXe = 2 * giaDau + (soGioDo - 2) * giaSau;
    }

    void hienThi() const {
        if (!dangChiemCho) return;
        cout << "  - Mã xe: " << maXe
             << " | Loại: " << left << setw(11) << loaiXe
             << " | Giờ vào: " << right << setw(2) << gioVao << "h"
             << " | Đỗ: " << setw(2) << soGioDo << "h"
             << " | Phí: " << fixed << setprecision(0) << phiDoXe << " VNĐ\n";
    }
};

// Lop quan ly mot bai do xe
class BaiDoXe {
private:
    int maBai;
    char kichThuoc; // S, M, L

    Xe xe1, xe2, xe3;
    bool coXe1, coXe2, coXe3;

public:
    BaiDoXe() : maBai(0), kichThuoc('S'), xe1(), xe2(), xe3(),
                coXe1(false), coXe2(false), coXe3(false) {}

    BaiDoXe(int ma, char kt)
        : maBai(ma), kichThuoc(toupper(kt)), xe1(), xe2(), xe3(),
          coXe1(false), coXe2(false), coXe3(false) {}

    int layMaBai() const { return maBai; }
    char layKichThuoc() const { return kichThuoc; }

    int laySucChua() const {
        if (kichThuoc == 'S') return 1;
        if (kichThuoc == 'M') return 2;
        if (kichThuoc == 'L') return 3;
        return 0;
    }

    int laySoXeHienCo() const {
        int dem = 0;
        if (coXe1) dem++;
        if (coXe2) dem++;
        if (coXe3) dem++;
        return dem;
    }

    bool conCho() const {
        int sc = laySucChua();
        if (sc >= 1 && !coXe1) return true;
        if (sc >= 2 && !coXe2) return true;
        if (sc >= 3 && !coXe3) return true;
        return false;
    }

    bool themXe(const Xe& x) {
        int sc = laySucChua();
        if (sc >= 1 && !coXe1) { xe1 = x; coXe1 = true; return true; }
        if (sc >= 2 && !coXe2) { xe2 = x; coXe2 = true; return true; }
        if (sc >= 3 && !coXe3) { xe3 = x; coXe3 = true; return true; }
        return false;
    }

    bool coXeNay(int ma) const {
        if (coXe1 && xe1.layMaXe() == ma) return true;
        if (coXe2 && xe2.layMaXe() == ma) return true;
        if (coXe3 && xe3.layMaXe() == ma) return true;
        return false;
    }

    bool layThongTinXe(int ma, Xe& ketQua) const {
        if (coXe1 && xe1.layMaXe() == ma) { ketQua = xe1; return true; }
        if (coXe2 && xe2.layMaXe() == ma) { ketQua = xe2; return true; }
        if (coXe3 && xe3.layMaXe() == ma) { ketQua = xe3; return true; }
        return false;
    }

    bool xoaXe(int ma) {
        if (coXe1 && xe1.layMaXe() == ma) { coXe1 = false; xe1.ganDangChiemCho(false); return true; }
        if (coXe2 && xe2.layMaXe() == ma) { coXe2 = false; xe2.ganDangChiemCho(false); return true; }
        if (coXe3 && xe3.layMaXe() == ma) { coXe3 = false; xe3.ganDangChiemCho(false); return true; }
        return false;
    }

    void hienThiXeTheoLoai(const string& loai) const {
        if (coXe1 && xe1.layLoaiXe() == loai) { cout << "  [Bãi " << maBai << "] "; xe1.hienThi(); }
        if (coXe2 && xe2.layLoaiXe() == loai) { cout << "  [Bãi " << maBai << "] "; xe2.hienThi(); }
        if (coXe3 && xe3.layLoaiXe() == loai) { cout << "  [Bãi " << maBai << "] "; xe3.hienThi(); }
    }

    double layTongPhi() const {
        double tong = 0.0;
        if (coXe1) tong += xe1.layPhiDoXe();
        if (coXe2) tong += xe2.layPhiDoXe();
        if (coXe3) tong += xe3.layPhiDoXe();
        return tong;
    }

    void congDonThongKeTheoLoai(const string& loai, double& tongPhi, int& soXe) const {
        if (coXe1 && xe1.layLoaiXe() == loai) { tongPhi += xe1.layPhiDoXe(); soXe++; }
        if (coXe2 && xe2.layLoaiXe() == loai) { tongPhi += xe2.layPhiDoXe(); soXe++; }
        if (coXe3 && xe3.layLoaiXe() == loai) { tongPhi += xe3.layPhiDoXe(); soXe++; }
    }

    void hienThiThongTinBai() const {
        cout << "----------------------------------------------------\n";
        cout << "BÃI ĐỖ XE [ID: " << maBai << "] - Cỡ: " << kichThuoc
             << "  (Hiện có: " << laySoXeHienCo() << "/" << laySucChua() << " xe)\n";
        cout << "----------------------------------------------------\n";
        if (laySoXeHienCo() == 0) {
            cout << "  (Bãi đang trống)\n";
        } else {
            if (coXe1) xe1.hienThi();
            if (coXe2) xe2.hienThi();
            if (coXe3) xe3.hienThi();
        }
        cout << "----------------------------------------------------\n";
    }
};

// Lop giao dien dieu khien menu
class GiaoDien {
private:
    BaiDoXe bai1, bai2, bai3;
    bool coBai1, coBai2, coBai3;

    void xoaInput() const {
        cin.clear();
        cin.ignore(10000, '\n');
    }

    bool trungMaBai(int ma) const {
        if (coBai1 && bai1.layMaBai() == ma) return true;
        if (coBai2 && bai2.layMaBai() == ma) return true;
        if (coBai3 && bai3.layMaBai() == ma) return true;
        return false;
    }

    bool trungMaXe(int ma) const {
        if (coBai1 && bai1.coXeNay(ma)) return true;
        if (coBai2 && bai2.coXeNay(ma)) return true;
        if (coBai3 && bai3.coXeNay(ma)) return true;
        return false;
    }

public:
    GiaoDien() : bai1(), bai2(), bai3(), coBai1(false), coBai2(false), coBai3(false) {}

    // 1. Tao bai moi
    void taoBaiDoXe() {
        if (coBai1 && coBai2 && coBai3) {
            cout << "[LỖI] Hệ thống đã đủ 3 bãi đỗ, không tạo thêm được!\n";
            return;
        }

        int ma;
        char kt;
        cout << "Nhập mã bãi đỗ: ";
        if (!(cin >> ma) || ma <= 0) {
            cout << "[LỖI] Mã bãi không hợp lệ!\n";
            xoaInput();
            return;
        }
        if (trungMaBai(ma)) {
            cout << "[LỖI] Mã bãi " << ma << " đã tồn tại!\n";
            return;
        }

        cout << "Nhập kích thước (S: 1 xe, M: 2 xe, L: 3 xe): ";
        cin >> kt;
        kt = toupper(kt);
        if (kt != 'S' && kt != 'M' && kt != 'L') {
            cout << "[LỖI] Kích thước chỉ được nhập S, M hoặc L!\n";
            return;
        }

        BaiDoXe baiMoi(ma, kt);
        if (!coBai1)      { bai1 = baiMoi; coBai1 = true; }
        else if (!coBai2) { bai2 = baiMoi; coBai2 = true; }
        else              { bai3 = baiMoi; coBai3 = true; }

        cout << "-> Tạo bãi đỗ " << ma << " thành công!\n";
    }

    // 2. Them xe vao bai
    void themXeVaoBai() {
        if (!coBai1 && !coBai2 && !coBai3) {
            cout << "[LỖI] Chưa có bãi đỗ nào, hãy tạo bãi trước!\n";
            return;
        }

        int ma, gio, soGio;
        string loai;

        cout << "Nhập mã xe: ";
        if (!(cin >> ma) || ma <= 0) {
            cout << "[LỖI] Mã xe không hợp lệ!\n";
            xoaInput();
            return;
        }
        if (trungMaXe(ma)) {
            cout << "[LỖI] Mã xe " << ma << " đã tồn tại!\n";
            return;
        }

        cout << "Nhập loại xe (Car / Motorcycle / Bicycle): ";
        cin >> loai;
        string loaiKT = loai;
        for (char &c : loaiKT) c = tolower(c);
        if (loaiKT != "car" && loaiKT != "motorcycle" && loaiKT != "bicycle") {
            cout << "[LỖI] Loại xe không hợp lệ!\n";
            return;
        }

        cout << "Nhập giờ vào (0 - 23): ";
        if (!(cin >> gio) || gio < 0 || gio > 23) {
            cout << "[LỖI] Giờ vào từ 0 đến 23!\n";
            xoaInput();
            return;
        }

        cout << "Nhập số giờ đỗ (1 - 23): ";
        if (!(cin >> soGio) || soGio < 1 || soGio > 23) {
            cout << "[LỖI] Số giờ đỗ từ 1 đến 23!\n";
            xoaInput();
            return;
        }

        Xe xeMoi(ma, loai, gio, soGio);
        bool daXep = false;
        int maBaiXep = 0;

        if      (coBai1 && bai1.conCho()) { bai1.themXe(xeMoi); daXep = true; maBaiXep = bai1.layMaBai(); }
        else if (coBai2 && bai2.conCho()) { bai2.themXe(xeMoi); daXep = true; maBaiXep = bai2.layMaBai(); }
        else if (coBai3 && bai3.conCho()) { bai3.themXe(xeMoi); daXep = true; maBaiXep = bai3.layMaBai(); }

        if (daXep) {
            cout << "-> Đã thêm xe " << ma << " vào bãi " << maBaiXep << "\n";
            cout << "   Phí đỗ tạm tính: " << fixed << setprecision(0) << xeMoi.layPhiDoXe() << " VNĐ\n";
        } else {
            cout << "[LỖI] Tất cả các bãi đều đã hết chỗ!\n";
        }
    }

    // 3. Xoa bai do
    void xoaBaiDoXe() {
        int ma;
        cout << "Nhập mã bãi cần xoá: ";
        if (!(cin >> ma)) { xoaInput(); return; }

        if (coBai1 && bai1.layMaBai() == ma) { coBai1 = false; cout << "-> Đã xoá bãi " << ma << "\n"; return; }
        if (coBai2 && bai2.layMaBai() == ma) { coBai2 = false; cout << "-> Đã xoá bãi " << ma << "\n"; return; }
        if (coBai3 && bai3.layMaBai() == ma) { coBai3 = false; cout << "-> Đã xoá bãi " << ma << "\n"; return; }

        cout << "[LỖI] Không tìm thấy bãi " << ma << "!\n";
    }

    // 4. Lay xe ra
    void layXeRa() {
        int ma;
        cout << "Nhập mã xe cần lấy ra: ";
        if (!(cin >> ma)) { xoaInput(); return; }

        Xe xeTim;
        bool timThay = false;
        int maBaiChua = 0;

        if      (coBai1 && bai1.layThongTinXe(ma, xeTim)) { bai1.xoaXe(ma); timThay = true; maBaiChua = bai1.layMaBai(); }
        else if (coBai2 && bai2.layThongTinXe(ma, xeTim)) { bai2.xoaXe(ma); timThay = true; maBaiChua = bai2.layMaBai(); }
        else if (coBai3 && bai3.layThongTinXe(ma, xeTim)) { bai3.xoaXe(ma); timThay = true; maBaiChua = bai3.layMaBai(); }

        if (timThay) {
            cout << "-> Xe " << ma << " đã lấy ra khỏi bãi " << maBaiChua << "\n";
            cout << "   Tiền phải thanh toán: " << fixed << setprecision(0) << xeTim.layPhiDoXe() << " VNĐ\n";
        } else {
            cout << "[LỖI] Không tìm thấy xe " << ma << "!\n";
        }
    }

    // 5. Xem tat ca bai
    void hienThiTatCaBai() const {
        if (!coBai1 && !coBai2 && !coBai3) {
            cout << "Chưa có bãi đỗ nào trong hệ thống.\n";
            return;
        }
        cout << "\n--- DANH SÁCH BÃI ĐỖ XE ---\n";
        cout << left << setw(10) << "MÃ BÃI" << setw(12) << "KÍCH THƯỚC"
             << setw(12) << "SỨC CHỨA" << setw(10) << "SỐ XE\n";
        cout << "------------------------------------------\n";
        if (coBai1) cout << left << setw(10) << bai1.layMaBai() << setw(12) << bai1.layKichThuoc()
                         << setw(12) << bai1.laySucChua() << setw(10) << bai1.laySoXeHienCo() << "\n";
        if (coBai2) cout << left << setw(10) << bai2.layMaBai() << setw(12) << bai2.layKichThuoc()
                         << setw(12) << bai2.laySucChua() << setw(10) << bai2.laySoXeHienCo() << "\n";
        if (coBai3) cout << left << setw(10) << bai3.layMaBai() << setw(12) << bai3.layKichThuoc()
                         << setw(12) << bai3.laySucChua() << setw(10) << bai3.laySoXeHienCo() << "\n";
        cout << "------------------------------------------\n";
    }

    // 6. Xem chi tiet xe theo bai
    void hienThiXeTheoBai() const {
        int ma;
        cout << "Nhập mã bãi cần xem: ";
        if (!(cin >> ma)) { return; }

        if (coBai1 && bai1.layMaBai() == ma) { bai1.hienThiThongTinBai(); return; }
        if (coBai2 && bai2.layMaBai() == ma) { bai2.hienThiThongTinBai(); return; }
        if (coBai3 && bai3.layMaBai() == ma) { bai3.hienThiThongTinBai(); return; }

        cout << "[LỖI] Không tìm thấy bãi " << ma << "!\n";
    }

    // 7. Liet ke xe theo loai
    void lietKeXeTheoLoai() const {
        string loai;
        cout << "Nhập loại xe cần lọc (Car / Motorcycle / Bicycle): ";
        cin >> loai;
        string tmp = loai;
        for (char &c : tmp) c = tolower(c);
        tmp[0] = toupper(tmp[0]);

        cout << "\n--- DANH SÁCH XE: " << tmp << " ---\n";
        if (coBai1) bai1.hienThiXeTheoLoai(tmp);
        if (coBai2) bai2.hienThiXeTheoLoai(tmp);
        if (coBai3) bai3.hienThiXeTheoLoai(tmp);
        cout << "--------------------------------\n";
    }

    // 8. Bao cao phi trung binh
    void baoCaoPhiTrungBinh() const {
        cout << "\n--- BÁO CÁO PHÍ ĐỖ XE TRUNG BÌNH ---\n";

        double phiOto = 0, phiXeMay = 0, phiXeDap = 0;
        int soOto = 0, soXeMay = 0, soXeDap = 0;

        if (coBai1) {
            bai1.congDonThongKeTheoLoai("Car",        phiOto,   soOto);
            bai1.congDonThongKeTheoLoai("Motorcycle", phiXeMay, soXeMay);
            bai1.congDonThongKeTheoLoai("Bicycle",    phiXeDap, soXeDap);
        }
        if (coBai2) {
            bai2.congDonThongKeTheoLoai("Car",        phiOto,   soOto);
            bai2.congDonThongKeTheoLoai("Motorcycle", phiXeMay, soXeMay);
            bai2.congDonThongKeTheoLoai("Bicycle",    phiXeDap, soXeDap);
        }
        if (coBai3) {
            bai3.congDonThongKeTheoLoai("Car",        phiOto,   soOto);
            bai3.congDonThongKeTheoLoai("Motorcycle", phiXeMay, soXeMay);
            bai3.congDonThongKeTheoLoai("Bicycle",    phiXeDap, soXeDap);
        }

        cout << "1. Phí trung bình theo loại xe:\n";
        cout << fixed << setprecision(0);
        cout << "  - Ô tô (Car):          " << (soOto   > 0 ? phiOto/soOto     : 0) << " VNĐ (" << soOto   << " xe)\n";
        cout << "  - Xe máy (Motorcycle): " << (soXeMay > 0 ? phiXeMay/soXeMay : 0) << " VNĐ (" << soXeMay << " xe)\n";
        cout << "  - Xe đạp (Bicycle):    " << (soXeDap > 0 ? phiXeDap/soXeDap : 0) << " VNĐ (" << soXeDap << " xe)\n";

        cout << "\n2. Chi tiết từng bãi:\n";
        if (!coBai1 && !coBai2 && !coBai3) {
            cout << "  (Chưa có bãi nào)\n";
        } else {
            auto inThongKeBai = [](const BaiDoXe& b) {
                int soXe    = b.laySoXeHienCo();
                double tong = b.layTongPhi();
                cout << "  * Bãi " << b.layMaBai() << " (cỡ " << b.layKichThuoc() << "): "
                     << soXe << "/" << b.laySucChua() << " xe"
                     << " | Tổng: " << fixed << setprecision(0) << tong << " VNĐ"
                     << " | TB: " << (soXe > 0 ? tong/soXe : 0) << " VNĐ\n";
            };
            if (coBai1) inThongKeBai(bai1);
            if (coBai2) inThongKeBai(bai2);
            if (coBai3) inThongKeBai(bai3);
        }
        cout << "------------------------------------\n";
    }

    void chayMenu() {
        int luaChon = 0;
        do {
            cout << "\n====================================\n";
            cout << "   QUẢN LÝ BÃI ĐỖ XE (OOP C++)\n";
            cout << "====================================\n";
            cout << "1. Tạo bãi đỗ xe mới\n";
            cout << "2. Thêm xe vào bãi đỗ\n";
            cout << "3. Xoá một bãi đỗ xe\n";
            cout << "4. Lấy xe ra khỏi bãi đỗ\n";
            cout << "5. Xem tất cả các bãi đỗ\n";
            cout << "6. Xem chi tiết xe trong bãi\n";
            cout << "7. Lọc xe theo loại\n";
            cout << "8. Thống kê phí trung bình\n";
            cout << "9. Thoát\n";
            cout << "------------------------------------\n";
            cout << "Nhập lựa chọn (1-9): ";

            if (!(cin >> luaChon)) {
                cout << "Nhập sai, vui lòng nhập số!\n";
                xoaInput();
                continue;
            }

            switch (luaChon) {
                case 1: taoBaiDoXe();         break;
                case 2: themXeVaoBai();       break;
                case 3: xoaBaiDoXe();         break;
                case 4: layXeRa();            break;
                case 5: hienThiTatCaBai();    break;
                case 6: hienThiXeTheoBai();   break;
                case 7: lietKeXeTheoLoai();   break;
                case 8: baoCaoPhiTrungBinh(); break;
                case 9: cout << "Tạm biệt!\n"; break;
                default: cout << "Lựa chọn không đúng, chọn lại!\n"; break;
            }
        } while (luaChon != 9);
    }
};

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif
    GiaoDien app;
    app.chayMenu();
    return 0;
}
