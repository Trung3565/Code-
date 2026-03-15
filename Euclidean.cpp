#include <iostream>
#include <iomanip>
#include <stdint.h>

using namespace std;
int degree(uint32_t a) {
    int d = -1;
    while (a) {
        d++; 
        a >>= 1;
    }
    return d;
}
void poly_div(uint32_t a, uint32_t b, uint32_t &q, uint32_t &r) {
    q = 0;
    r = a;
    int deg_b = degree(b);
    while (degree(r) >= deg_b) {
        int shift = degree(r) - deg_b;
        q ^= (1 << shift);
        r ^= (b << shift);
    }
}
uint32_t poly_mul(uint32_t a, uint32_t b) {
    uint32_t res = 0;
    while (b > 0) {
        if (b & 1) res ^= a;
        a <<= 1;
        b >>= 1;
    }
    return res;
}
uint32_t extended_euclidean(uint32_t m, uint32_t a) {
    uint32_t r1 = m, r2 = a;
    uint32_t t1 = 0, t2 = 1;

    cout << left << setw(8) << "r1"
         << setw(8) << "r2"
         << setw(8) << "q"
         << setw(8) << "r"
         << setw(8) << "t1"
         << setw(8) << "t2"
         << setw(8) << "t" << "\n";
    cout << "---------------------------------------------------------\n";

    while (r2 > 0) {
        uint32_t q, r;
        poly_div(r1, r2, q, r);
        uint32_t t = t1 ^ poly_mul(q, t2);

        cout << left << setw(8) << r1
             << setw(8) << r2
             << setw(8) << q
             << setw(8) << r
             << setw(8) << t1
             << setw(8) << t2
             << setw(8) << t << "\n";

        r1 = r2;
        r2 = r;
        t1 = t2;
        t2 = t;
    }
    cout << "---------------------------------------------------------\n";
    cout << "=> Nghich dao nhan la: " << t1 << "\n\n";
    return t1;
}
int main() {
    uint32_t m = 1033;
    uint32_t a = 523;
    uint32_t b = 1015;

    cout << "Tim nghich dao cua a = " << a << " trong GF(2^10):\n";
    extended_euclidean(m, a);

    cout << "Tim nghich dao cua b = " << b << " trong GF(2^10):\n";
    extended_euclidean(m, b);

    return 0;
}