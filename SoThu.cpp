#include <bits/stdc++.h>
using namespace std;

// ==========================================
// BỘ ĐIỀU KHIỂN MÀU SẮC (STREAM MANIPULATORS)
// ==========================================
namespace Color {
    inline ostream& reset(ostream& os)     { return os << "\033[0m"; }
    inline ostream& bold(ostream& os)      { return os << "\033[1m"; }
    inline ostream& underline(ostream& os) { return os << "\033[4m"; }

    // Màu cơ bản
    inline ostream& red(ostream& os)       { return os << "\033[31m"; }
    inline ostream& green(ostream& os)     { return os << "\033[32m"; }
    inline ostream& yellow(ostream& os)    { return os << "\033[33m"; }
    inline ostream& blue(ostream& os)      { return os << "\033[34m"; }
    inline ostream& magenta(ostream& os)   { return os << "\033[35m"; }
    inline ostream& cyan(ostream& os)      { return os << "\033[36m"; }
    inline ostream& white(ostream& os)     { return os << "\033[37m"; }

    // Màu sáng (Bright / High Intensity)
    inline ostream& b_red(ostream& os)     { return os << "\033[91m"; }
    inline ostream& b_green(ostream& os)   { return os << "\033[92m"; }
    inline ostream& b_yellow(ostream& os)  { return os << "\033[93m"; }
    inline ostream& b_blue(ostream& os)    { return os << "\033[94m"; }
    inline ostream& b_magenta(ostream& os) { return os << "\033[95m"; }
    inline ostream& b_cyan(ostream& os)    { return os << "\033[96m"; }
}

class DongVat {
private:
    string ten;
    int tuoi;
    double canNang;

protected:
    static string chuanHoa(string s) {
        stringstream ss(s);
        string tu, ketQua = "";

        while (ss >> tu) {
            tu[0] = toupper(tu[0]);
            for (size_t i = 1; i < tu.length(); i++) {
                tu[i] = tolower(tu[i]);
            }
            if (ketQua != "") {
                ketQua += " ";
            }
            ketQua += tu;
        }
        return ketQua;
    }

    // Định dạng tiền có dấu phẩy ngăn cách mỗi 3 chữ số
    static string formatTien(double tien) {
        long long soTien = llround(tien);
        string s = to_string(soTien);
        int n = (int)s.length() - 3;
        while (n > 0) {
            s.insert(n, ",");
            n -= 3;
        }
        return s + " VND";
    }

    // Định dạng cân nặng kèm đơn vị để căn trái không bị rời chữ "kg"
    static string formatCanNang(double cn) {
        stringstream ss;
        ss << fixed << setprecision(1) << cn << " kg";
        return ss.str();
    }

public:
    DongVat() {
        ten = "";
        tuoi = 0;
        canNang = 0;
    }
    DongVat(string _ten, int _tuoi, double _canNang) {
        ten = chuanHoa(_ten);
        tuoi = (_tuoi >= 0) ? _tuoi : 0;
        canNang = (_canNang >= 0) ? _canNang : 0;
    }
    DongVat(const DongVat& other) {
        ten = other.ten;
        tuoi = other.tuoi;
        canNang = other.canNang;
    }
    virtual ~DongVat() {}

    // Get - Set
    string getTen() { return ten; }
    int getTuoi() { return tuoi; }
    double getCanNang() { return canNang; }

    void setTen(string _ten) {
        ten = chuanHoa(_ten);
    }
    void setTuoi(int _tuoi) {
        if (_tuoi >= 0) {
            tuoi = _tuoi;
        } else {
            cout << Color::b_red << "Tuoi phai lon hon hoac bang 0!" << Color::reset << endl;
        }
    }
    void setCanNang(double _canNang) {
        if (_canNang >= 0) {
            canNang = _canNang;
        } else {
            cout << Color::b_red << "Can nang phai lon hon hoac bang 0!" << Color::reset << endl;
        }
    }

    // Nhap - Xuat
    virtual void Nhap(istream& is) {
        cout << Color::b_cyan << "Nhap ten dong vat: " << Color::reset;
        getline(is >> ws, ten);
        ten = chuanHoa(ten);

        while (true) {
            cout << Color::b_cyan << "Nhap tuoi: " << Color::reset;
            if (is >> tuoi && tuoi >= 0) break;
            cout << Color::b_red << "Tuoi khong hop le, vui long nhap lai so nguyen >= 0!" << Color::reset << endl;
            is.clear();
            is.ignore(1000, '\n');
        }

        while (true) {
            cout << Color::b_cyan << "Nhap can nang (kg): " << Color::reset;
            if (is >> canNang && canNang >= 0) break;
            cout << Color::b_red << "Can nang khong hop le, vui long nhap lai so thuc >= 0!" << Color::reset << endl;
            is.clear();
            is.ignore(1000, '\n');
        }
    }

    // Xuất các cột chung: Thông tin căn trái, Tiền ăn căn phải
    virtual void Xuat(ostream& os) {
        os << " " << Color::bold << Color::b_yellow << left << setw(8) << getLoai() << Color::reset
           << " | " << Color::b_cyan << left << setw(20) << ten << Color::reset
           << " | " << Color::white << left << setw(6) << tuoi << Color::reset
           << " | " << Color::white << left << setw(12) << formatCanNang(canNang) << Color::reset
           << " | " << Color::b_green << right << setw(18) << formatTien(tinhTienThucAn()) << Color::reset;
    }

    friend istream& operator>>(istream& is, DongVat& dv) {
        dv.Nhap(is);
        return is;
    }

    friend ostream& operator<<(ostream& os, DongVat& dv) {
        dv.Xuat(os);
        return os;
    }

    // Method
    virtual string keu() = 0;
    virtual double tinhTienThucAn() = 0;
    virtual string getLoai() = 0;
};

// Lớp kế thừa: Cho
class Cho : public DongVat {
private:
    string giongLoai;
public:
    Cho() : DongVat() {
        giongLoai = "";
    }
    Cho(string _ten, int _tuoi, double _canNang, string _giongLoai) : DongVat(_ten, _tuoi, _canNang) {
        giongLoai = chuanHoa(_giongLoai);
    }
    Cho(const Cho& other) : DongVat(other) {
        giongLoai = other.giongLoai;
    }
    ~Cho() override {}

    string getGiongLoai() { return giongLoai; }
    void setGiongLoai(string _giongLoai) {
        giongLoai = chuanHoa(_giongLoai);
    }

    void Nhap(istream& is) override {
        DongVat::Nhap(is);
        cout << Color::b_cyan << "Nhap giong cho (Poodle, Becgie, Corgi...): " << Color::reset;
        getline(is >> ws, giongLoai);
        giongLoai = chuanHoa(giongLoai);
    }

    void Xuat(ostream& os) override {
        DongVat::Xuat(os);
        os << " | " << Color::magenta << left << setw(18) << giongLoai << Color::reset << " |";
    }

    string keu() override {
        return "\033[96m" + getTen() + " (" + giongLoai + ")\033[0m sua: \033[1;93mGau gau!\033[0m";
    }

    double tinhTienThucAn() override {
        // Gia thuc an hat cho cho: ~70,000 VND/kg, ~3,500 kcal/kg => 20 VND/kcal
        double giaMoiKcal = 20.0;

        // RER = 70 * BW^0.75
        double rer = 70.0 * pow(getCanNang(), 0.75);

        // He so theo tuoi (giai doan song)
        double heSoTuoi;
        if (getTuoi() < 1) {
            heSoTuoi = 2.0;        // cho con
        } else if (getTuoi() >= 7) {
            heSoTuoi = 1.2;        // cho gia
        } else {
            heSoTuoi = 1.6;        // cho truong thanh
        }

        // He so theo giong
        double heSoGiong;
        if (giongLoai == "Becgie") {
            heSoGiong = 1.2;       // giong lon, hoat dong nhieu
        } else if (giongLoai == "Corgi") {
            heSoGiong = 1.1;
        } else if (giongLoai == "Poodle") {
            heSoGiong = 0.95;
        } else {
            heSoGiong = 1.0;
        }

        double kcalNgay = rer * heSoTuoi * heSoGiong;
        return kcalNgay * 30.0 * giaMoiKcal;
    }

    string getLoai() override {
        return "Cho";
    }
};

// Lớp kế thừa: Meo
class Meo : public DongVat {
private:
    string giongLoai;

public:
    Meo() : DongVat() {
        giongLoai = "";
    }
    Meo(string _ten, int _tuoi, double _canNang, string _giongLoai)
        : DongVat(_ten, _tuoi, _canNang) {
        giongLoai = chuanHoa(_giongLoai);
    }
    Meo(const Meo& other) : DongVat(other) {
        giongLoai = other.giongLoai;
    }
    ~Meo() override {}

    string getGiongLoai() { return giongLoai; }
    void setGiongLoai(string _giongLoai) {
        giongLoai = chuanHoa(_giongLoai);
    }

    void Nhap(istream& is) override {
        DongVat::Nhap(is);
        cout << Color::b_cyan << "Nhap giong meo (Ba Tu, Muop, Anh Long Ngan...): " << Color::reset;
        getline(is >> ws, giongLoai);
        giongLoai = chuanHoa(giongLoai);
    }

    void Xuat(ostream& os) override {
        DongVat::Xuat(os);
        os << " | " << Color::magenta << left << setw(18) << giongLoai << Color::reset << " |";
    }

    string keu() override {
        return "\033[95m" + getTen() + " (" + giongLoai + ")\033[0m keu: \033[1;92mMeo meo~\033[0m";
    }

    double tinhTienThucAn() override {
        // Gia thuc an hat cho meo: ~100,000 VND/kg, ~4,000 kcal/kg => 25 VND/kcal
        double giaMoiKcal = 25.0;

        // Bermingham et al. (2010): MER = 77.7 * BW^0.711
        double kcalCoBan = 77.7 * pow(getCanNang(), 0.711);

        // He so theo giong
        double heSoGiong;
        if (giongLoai == "Ba Tu") {
            heSoGiong = 0.9;       // it van dong, nuoi trong nha
        } else if (giongLoai == "Muop") {
            heSoGiong = 1.1;       // nhanh nhen, hoat dong nhieu
        } else {
            heSoGiong = 1.0;
        }

        double kcalNgay = kcalCoBan * heSoGiong;
        return kcalNgay * 30.0 * giaMoiKcal;
    }

    string getLoai() override {
        return "Meo";
    }
};

// Lớp kế thừa: Chim
class Chim : public DongVat {
private:
    string loaiChim;

public:
    Chim() : DongVat() {
        loaiChim = "";
    }
    Chim(string _ten, int _tuoi, double _canNang, string _loaiChim)
        : DongVat(_ten, _tuoi, _canNang) {
        loaiChim = chuanHoa(_loaiChim);
    }
    Chim(const Chim& other) : DongVat(other) {
        loaiChim = other.loaiChim;
    }
    ~Chim() override {}

    string getLoaiChim() { return loaiChim; }
    void setLoaiChim(string _loaiChim) {
        loaiChim = chuanHoa(_loaiChim);
    }

    void Nhap(istream& is) override {
        DongVat::Nhap(is);
        while (true) {
            cout << Color::b_yellow << "Chon tap tinh an uong (1. An hat | 2. An sau | 3. An thit): " << Color::reset;
            int choice;
            if (is >> choice) {
                if (choice == 1) { loaiChim = "An Hat"; break; }
                if (choice == 2) { loaiChim = "An Sau"; break; }
                if (choice == 3) { loaiChim = "An Thit"; break; }
            }
            cout << Color::b_red << "Lua chon khong hop le, vui long chon 1, 2 hoac 3!\n" << Color::reset;
            is.clear();
            is.ignore(1000, '\n');
        }
    }

    void Xuat(ostream& os) override {
        DongVat::Xuat(os);
        os << " | " << Color::magenta << left << setw(18) << loaiChim << Color::reset << " |";
    }

    string keu() override {
        return "\033[93m" + getTen() + " (" + loaiChim + ")\033[0m hot: \033[1;96mLiu lo liu lo!\033[0m";
    }

    double tinhTienThucAn() override {
        double gram = getCanNang() * 1000.0;
        double kcalCoBan;
        double heSoLoai;
        double giaMoiKcal;

        if (loaiChim == "An Thit") {
            // Chim khong phai chim se (Kendeigh 1970)
            kcalCoBan = 0.534 * pow(gram, 0.723);
            heSoLoai = 1.0;
            giaMoiKcal = 30.0;     // thit/chuot, ~60,000 VND/kg, ~2,000 kcal/kg
        } else if (loaiChim == "An Sau") {
            // Chim se (Kendeigh 1970)
            kcalCoBan = 0.867 * pow(gram, 0.724);
            heSoLoai = 1.1;        // chim an sau hoat dong nhieu hon
            giaMoiKcal = 60.0;     // sau kho, ~300,000 VND/kg, ~5,000 kcal/kg
        } else {
            // An hat: chim se (Kendeigh 1970)
            kcalCoBan = 0.867 * pow(gram, 0.724);
            heSoLoai = 1.0;
            giaMoiKcal = 17.0;     // hat, ~60,000 VND/kg, ~3,500 kcal/kg
        }

        double kcalNgay = kcalCoBan * heSoLoai;
        return kcalNgay * 30.0 * giaMoiKcal;
    }

    string getLoai() override {
        return "Chim";
    }
};

// 3. LỚP QUẢN LÝ: SoThu
// ==========================================
class SoThu {
private:
    vector<DongVat*> danhSach;

    void inDuongKeNgang() {
        cout << Color::b_cyan
             << "+------+----------+----------------------+--------+--------------+--------------------+--------------------+\n"
             << Color::reset;
    }

public:
    SoThu() {}

    ~SoThu() {
        for (DongVat* dv : danhSach) {
            delete dv;
        }
        danhSach.clear();
    }

    void themDongVat(DongVat* dv) {
        if (dv != nullptr) {
            danhSach.push_back(dv);
        }
    }

    void xuatDanhSach() {
        if (danhSach.empty()) {
            cout << Color::b_yellow << "(!) So thu hien chua co dong vat nao!\n" << Color::reset;
            return;
        }

        const int W = 108;  // độ rộng của dòng kẻ +------+...
        string tieuDe = " DANH SACH DONG VAT TRONG SO THU ";
        int trai = (W - (int)tieuDe.length()) / 2;
        int phai = W - (int)tieuDe.length() - trai;

        cout << "\n" << Color::bold << Color::b_cyan
        << string(trai, '=') << tieuDe << string(phai, '=') << "\n"
        << Color::reset;

        inDuongKeNgang();

        // Dòng tiêu đề bảng (Thông tin căn trái, Tiền ăn/tháng căn phải)
        cout << "| " << Color::bold << Color::b_yellow << left << setw(4)  << "STT"           << Color::reset
        << " | " << Color::bold << Color::b_yellow << left << setw(8)  << "Loai"          << Color::reset
        << " | " << Color::bold << Color::b_yellow << left << setw(20) << "Ten"           << Color::reset
        << " | " << Color::bold << Color::b_yellow << left << setw(6)  << "Tuoi"          << Color::reset
        << " | " << Color::bold << Color::b_yellow << left << setw(12) << "Can nang"      << Color::reset
        << " | " << Color::bold << Color::b_yellow << left << setw(18) << "Tien an/thang" << Color::reset   // <-- left
        << " | " << Color::bold << Color::b_yellow << left << setw(18) << "Giong / Loai"  << Color::reset << " |\n";

        inDuongKeNgang();

        // Các dòng dữ liệu
        for (size_t i = 0; i < danhSach.size(); i++) {
            cout << "| " << Color::bold << Color::white << left << setw(4) << (i + 1) << Color::reset << " |"
                << *danhSach[i] << "\n";
        }

        inDuongKeNgang();
    }

    void tatCaKeu() {
        if (danhSach.empty()) {
            cout << Color::b_yellow << "(!) So thu hien chua co dong vat nao!\n" << Color::reset;
            return;
        }
        cout << Color::bold << Color::b_magenta << "\n================= TAT CA DONG VAT CUNG KEU =================\n" << Color::reset;

        for (size_t i = 0; i < danhSach.size(); i++) {
            cout << Color::bold << i + 1 << ". " << Color::reset << danhSach[i]->keu() << "\n";
        }
        cout << Color::b_magenta << "------------------------------------------------------------\n" << Color::reset;
    }
};

int main() {
    SoThu zoo;
    int luaChon;

    do {
        cout << "\n" << Color::bold << Color::b_blue << "============= MENU QUAN LY SO THU =============" << Color::reset << "\n";
        cout << Color::b_green << "1." << Color::reset << " Them Cho\n";
        cout << Color::b_green << "2." << Color::reset << " Them Meo\n";
        cout << Color::b_green << "3." << Color::reset << " Them Chim\n";
        cout << Color::b_green << "4." << Color::reset << " Xuat danh sach dong vat\n";
        cout << Color::b_green << "5." << Color::reset << " Cho tat ca dong vat keu\n";
        cout << Color::b_red   << "0." << Color::reset << " Thoat chuong trinh\n";
        cout << Color::bold << "Nhap lua chon: " << Color::reset;

        if (!(cin >> luaChon)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << Color::b_red << "Lua chon khong hop le!\n" << Color::reset;
            continue;
        }

        if (luaChon == 1) {
            DongVat* cho = new Cho();
            cin >> *cho;
            zoo.themDongVat(cho);
            cout << Color::b_green << "-> Da them Cho thanh cong!\n" << Color::reset;
        } else if (luaChon == 2) {
            DongVat* meo = new Meo();
            cin >> *meo;
            zoo.themDongVat(meo);
            cout << Color::b_green << "-> Da them Meo thanh cong!\n" << Color::reset;
        } else if (luaChon == 3) {
            DongVat* chim = new Chim();
            cin >> *chim;
            zoo.themDongVat(chim);
            cout << Color::b_green << "-> Da them Chim thanh cong!\n" << Color::reset;
        } else if (luaChon == 4) {
            zoo.xuatDanhSach();
        } else if (luaChon == 5) {
            zoo.tatCaKeu();
        } else if (luaChon == 0) {
            cout << Color::yellow << "Dang thoat va giai phong bo nho...\n" << Color::reset;
        } else {
            cout << Color::b_red << "Lua chon khong ton tai. Vui long chon lai!\n" << Color::reset;
        }

    } while (luaChon != 0);

    return 0;
}