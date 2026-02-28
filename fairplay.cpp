#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;
char matrix[5][5];
void createMatrix(string keyword) {
    bool used[26] = {false};
    used['J' - 'A'] = true; 
    string chars = "";
    for (char c : keyword) {
        c = toupper(c);
        if (c == 'J') c = 'I';
        if (c >= 'A' && c <= 'Z' && !used[c - 'A']) {
            chars += c;
            used[c - 'A'] = true;
        }
    }
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (!used[c - 'A']) {
            chars += c;
        }
    }
    int k = 0;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            matrix[i][j] = chars[k++];
        }
    }
}
string preparePlaintext(string text) {
    string cleaned = "";
    for (char c : text) {
        if (c != ' ') {
            c = toupper(c);
            if (c == 'J') c = 'I';
            if (c >= 'A' && c <= 'Z') {
                cleaned += c;
            }
        }
    }
    string pairs = "";
    for (size_t i = 0; i < cleaned.length(); ) {
        char c1 = cleaned[i];
        if (i + 1 < cleaned.length()) {
            char c2 = cleaned[i+1];
            if (c1 == c2) {
                pairs += c1;
                pairs += 'X';
                i += 1;
            } else {
                pairs += c1;
                pairs += c2;
                i += 2;
            }
        } else {
            pairs += c1;
            pairs += 'X';
            i += 1;
        }
    }
    return pairs;
}
void findPosition(char c, int& row, int& col) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (matrix[i][j] == c) {
                row = i;
                col = j;
                return;
            }
        }
    }
}
string encrypt(string plaintext) {
    string pairs = preparePlaintext(plaintext);
    string ciphertext = "";

    for (size_t i = 0; i < pairs.length(); i += 2) {
        int r1, c1, r2, c2;
        findPosition(pairs[i], r1, c1);
        findPosition(pairs[i+1], r2, c2);

        if (r1 == r2) {
            ciphertext += matrix[r1][(c1 + 1) % 5];
            ciphertext += matrix[r2][(c2 + 1) % 5];
        } else if (c1 == c2) {
            ciphertext += matrix[(r1 + 1) % 5][c1];
            ciphertext += matrix[(r2 + 1) % 5][c2];
        } else {
            ciphertext += matrix[r1][c2];
            ciphertext += matrix[r2][c1];
        }
        ciphertext += " "; 
    }
    
    if (!ciphertext.empty()) {
        ciphertext.pop_back();
    }

    return ciphertext;
}

int main() {
    string keyword;
    string plaintext;
    cout << "Nhap tu khoa (Keyword): ";
    getline(cin, keyword);
    cout << "Nhap ban ro (Plaintext): ";
    getline(cin, plaintext);
    createMatrix(keyword);
    string ciphertext = encrypt(plaintext);
    cout << "\n--- Playfair Cipher Result ---" << endl;
    cout << "Keyword:    " << keyword << endl;
    cout << "Plaintext:  " << plaintext << endl;
    cout << "Ciphertext: " << ciphertext << endl;

    return 0;
}