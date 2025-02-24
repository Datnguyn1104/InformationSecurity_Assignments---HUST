#include <iostream>
using namespace std;

class MaHoaPlayfair {
private:
    char bangMa[5][5];
    
    // Hàm chuẩn hóa chuỗi_ chuyển thành chữ hoa và thay thế J bằng I
    void chuanHoaVanBan(string &vanBan) {
        for (int i = 0; i < vanBan.length(); i++) {
            vanBan[i] = toupper(vanBan[i]);
            if (vanBan[i] == 'J')
                vanBan[i] = 'I';
        }
    }
    
    // Hàm khởi tạo bảng mã Playfair từ khóa
    void khoiTaoBangMa(string khoa) {
        // Kiểm tra khóa rỗng
        if (khoa.empty()) {
            khoa = "KHONGCOKEY"; // mặc định
        }
        
        // Chuẩn hóa khóa
        chuanHoaVanBan(khoa);
        
        // Loại bỏ ký tự trùng lặp trong khóa
        string khoaDuyNhat = "";
        bool kyTuDaSuDung[26] = {false};
        
        for (char c : khoa) {
            if (isalpha(c)) {
                if (c == 'J') c = 'I';
                if (!kyTuDaSuDung[c - 'A']) {
                    khoaDuyNhat += c;
                    kyTuDaSuDung[c - 'A'] = true;
                }
            }
        }
        
        // Thêm các chữ cái còn lại vào khóa
        for (char c = 'A'; c <= 'Z'; c++) {
            if (c == 'J') continue;
            if (!kyTuDaSuDung[c - 'A']) {
                khoaDuyNhat += c;
                kyTuDaSuDung[c - 'A'] = true;
            }
        }
        
        // Điền bảng mã
        int k = 0;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                bangMa[i][j] = khoaDuyNhat[k++];
            }
        }
    }
    
    // Hàm tìm vị trí của ký tự trong bảng mã
    void timViTri(char kyTu, int &hang, int &cot) {
        if (kyTu == 'J') kyTu = 'I';
        
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (bangMa[i][j] == kyTu) {
                    hang = i;
                    cot = j;
                    return;
                }
            }
        }
    }
    
    // Hàm chuẩn bị văn bản để mã hóa
    string chuanBiVanBan(string vanBan) {
        if (vanBan.empty()) {
            return "";
        }
        
        chuanHoaVanBan(vanBan);
        
        string ketQua = "";
        // Chỉ giữ lại các chữ cái
        for (int i = 0; i < vanBan.length(); i++) {
            if (isalpha(vanBan[i])) {
                ketQua += vanBan[i];
            }
        }
        
        if (ketQua.empty()) {
            return "";
        }
        
        // Chèn X giữa hai ký tự giống nhau
        for (int i = 0; i < ketQua.length() - 1; i += 2) {
            if (ketQua[i] == ketQua[i + 1]) {
                ketQua.insert(i + 1, "X");
            }
        }
        
        // Thêm X vào cuối nếu độ dài lẻ
        if (ketQua.length() % 2 != 0) {
            ketQua += 'X';
        }
        
        return ketQua;
    }
    
public:
    // Hàm khởi tạo với khóa
    MaHoaPlayfair(string khoa) {
        khoiTaoBangMa(khoa);
    }
    
    // Hàm hiển thị bảng mã
    void hienThiBangMa() {
        cout << "Bang ma Playfair:" << endl;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                cout << bangMa[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    // Hàm mã hóa
    string maHoa(string banRo) {
        string banDaChuanBi = chuanBiVanBan(banRo);
        
        // Kiểm tra chuỗi rỗng
        if (banDaChuanBi.empty()) {
            return "ERROR!";
        }
        
        string banMa = "";
        
        for (int i = 0; i < banDaChuanBi.length(); i += 2) {
            int hang1, cot1, hang2, cot2;
            
            timViTri(banDaChuanBi[i], hang1, cot1);
            timViTri(banDaChuanBi[i + 1], hang2, cot2);
            
            if (hang1 == hang2) {
                banMa += bangMa[hang1][(cot1 + 1) % 5];
                banMa += bangMa[hang2][(cot2 + 1) % 5];
            }
            else if (cot1 == cot2) {
                banMa += bangMa[(hang1 + 1) % 5][cot1];
                banMa += bangMa[(hang2 + 1) % 5][cot2];
            }

            else {
                banMa += bangMa[hang1][cot2];
                banMa += bangMa[hang2][cot1];
            }
        }
        
        return banMa;
    }
};

int main() {
    string khoa, banRo;
    
    cout << "Nhap khoa: ";
    getline(cin, khoa);
    
    cout << "Nhap ban ro: ";
    getline(cin, banRo);
    
    MaHoaPlayfair maHoa(khoa);
    
    maHoa.hienThiBangMa();
    
    string banMa = maHoa.maHoa(banRo);
    cout << "Ban ma: " << banMa << endl;
    
    return 0;
}
