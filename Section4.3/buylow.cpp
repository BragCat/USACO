/*
 ID: bragcat1
 LANG: C++11
 TASK: buylow
 */

#include <fstream>

using namespace std;

const int MAX_N = 5000;
const int MAX_B = 32;
const int DECIMAL = 100000000;

class BigNumber {

public:
    int digits[MAX_B] = {0};
    int digitCnt = 0;

    BigNumber() {
        digits[0] = 1;
        digitCnt = 1;
    }

    BigNumber & plus(BigNumber &number) {
        int digitCnt1 = number.digitCnt;
        int up = 0;
        for (int i = 0; i < max(digitCnt1, digitCnt) + 1; ++i) {
            digits[i] = digits[i] + number.digits[i] + up;
            up = digits[i] / DECIMAL;
            digits[i] %= DECIMAL;
        }
        while (digits[digitCnt] > 0) {
            ++digitCnt;
        }
        return *this;
    }

    BigNumber & copy(BigNumber &number) {
        for (int i = 0; i < digitCnt; ++i) {
            digits[i] = 0;
        }
        digitCnt = number.digitCnt;
        for (int i = 0; i < digitCnt; ++i) {
            digits[i] = number.digits[i];
        }
        return *this;
    }
};

int price[MAX_N + 1];
int n;

int f[MAX_N + 1];
BigNumber g[MAX_N + 1];
int nextIndex[MAX_N + 1];

void print(ofstream &fout, BigNumber number) {
    for (int i = number.digitCnt - 1; i >= 0; --i) {
        int k = DECIMAL / 10;
        int digit = number.digits[i];
        if (i != number.digitCnt - 1) {
            while (k > digit) {
                fout << 0;
                k /= 10;
            }
        }
        fout << digit;
    }
}

int main() {
    ifstream fin("buylow.in");
    fin >> n;
    for (int i = 0; i < n; ++i) {
        fin >> price[i];
    }
    fin.close();

    price[n++] = 0;
    for (int i = 0; i < n; ++i) {
        f[i] = 1;
        for (int j = i + 1; j < n; ++j) {
            if (price[i] == price[j]) {
                nextIndex[i] = j;
                break;
            }
        }
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (price[j] > price[i]) {
                if (nextIndex[j] && nextIndex[j] < i) {
                    continue;
                }
                if (f[j] + 1 > f[i]) {
                    f[i] = f[j] + 1;
                    g[i].copy(g[j]);
                }
                else if (f[j] + 1 == f[i]) {
                    g[i].plus(g[j]);
                }
            }
        }
    }

    ofstream fout("buylow.out");
    fout << f[n - 1] - 1 << " ";
    print(fout, g[n - 1]);
    fout << endl;
    fout.close();

    return 0;
}
