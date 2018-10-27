/*
 ID: bragcat1
 LANG: C++11
 TASK: vans
 */

#include <cstring>
#include <fstream>

using namespace std;

const int MAX_N = 1000;

struct BigNumber {
    int digits[MAX_N] = {0};
    int len = 0;
    BigNumber() {}
    BigNumber(int x) {
        if (x == 0) {
            len = 1;
        }
        while (x > 0) {
            digits[len++] = x % 10;
            x /= 10;
        }
    }
    BigNumber(const BigNumber &a) {
        len = a.len;
        memcpy(digits, a.digits, sizeof(digits));
    }
    BigNumber &add(BigNumber &a) {
        len = max(a.len, len);
        int up = 0;
        for (int i = 0; i < len; ++i) {
            digits[i] += a.digits[i] + up;
            up = digits[i] / 10;
            digits[i] %= 10;
        }
        if (up > 0) {
            digits[len] = up;
            ++len;
        }
        return *this;
    }
    BigNumber &subtract(BigNumber &a) {
        for (int i = 0; i < len; ++i) {
            if (digits[i] < a.digits[i]) {
                digits[i] += 10;
                --digits[i + 1];
            }
            digits[i] -= a.digits[i];
        }
        while (len > 0 && digits[len - 1] == 0) {
            --len;
        }
        return *this;
    }
    BigNumber &multiply(int x) {
        int up = 0;
        for (int i = 0; i < len; ++i) {
            digits[i] = digits[i] * x + up;
            up = digits[i] / 10;
            digits[i] %= 10;
        }
        digits[len] += up;
        while (digits[len] > 0) {
            digits[len + 1] = digits[len] / 10;
            digits[len++] %= 10;
        }
        return *this;
    }
    friend ofstream & operator <<(ofstream &out, BigNumber &a) {
        for (int i = a.len - 1; i >= 0; --i) {
            out << a.digits[i];
        }
        return out;
    }
};

int n;
BigNumber f[MAX_N + 1];

int main() {
    ifstream fin("vans.in");
    fin >> n;
    fin.close();

    f[1] = 0, f[2] = 2, f[3] = 4, f[4] = 12;
    for (int i = 5; i <= n; ++i) {
        BigNumber f1 = f[i - 1], f2 = f[i - 2], f3 = f[i - 3], f4 = f[i - 4];
        f[i].add(f1.multiply(2)).add(f2.multiply(2)).add(f4).subtract(f3.multiply(2));
    }

    ofstream fout("vans.out");
    fout.setf(ios::fixed);
    fout.precision(0);
    fout << f[n] << endl;
    fout.close();

    return 0;
}

