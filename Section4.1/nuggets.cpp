/*
 ID: bragcat1
 LANG: C++11
 TASK: nuggets
 */

#include <fstream>

using namespace std;

const int MAXN = 10;
const int MAX_NUGGET = 256;
const int MAX_BOUND = 2000000000;

int n;
int nuggets[MAXN];
bool f[MAX_NUGGET];

int calcGcd(int a, int b) {
    if (a < b) {
        a = a ^ b;
        b = a ^ b;
        a = a ^ b;
    }
    return (b == 0) ? a : calcGcd(b, a % b);
}

int main() {
    ifstream fin("nuggets.in");
    fin >> n;
    for (int i = 0; i < n; ++i) {
        fin >> nuggets[i];
    }
    fin.close();

    int gcd = nuggets[0];
    for (auto nugget : nuggets) {
        gcd = calcGcd(nugget, gcd);
    }
    ofstream fout("nuggets.out");
    if (gcd > 1) {
        fout << 0 << endl;
    }
    else {
        int number = 0;
        f[0] = true;
        int index = number, last = 0;
        while (number < MAX_BOUND) {
            if (number - last > MAX_NUGGET) {
                break;
            }

            if (!f[index]) {
                last = number;
            }
            else {
                f[index] = false;
                for (int i = 0; i < n; ++i) {
                    f[(index + nuggets[i]) % MAX_NUGGET] = true;
                }
            }
            index = (++number) % MAX_NUGGET;
        }
        fout << last << endl;
    }
    fout.close();
    return 0;
}
