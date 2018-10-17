/*
 ID: bragcat1
 TASK: theme
 LANG: C++11
 */

#include <fstream>
#include <iostream>

using namespace std;

const int MAX_N = 5000;

int n, ans;
int f[2][MAX_N];
int a[MAX_N];

void dp() {
    for (int i = n - 1; i > 0; --i) {
        a[i] -= a[i - 1];
    }
    int c = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (a[i] == a[j]) {
                f[c ^ 1][j] = f[c][j - 1] + 1;
                ans = max(ans, min(f[c ^ 1][j], j - i - 1));
            }
            else {
                f[c ^ 1][j] = 0;
            }
        }
        c ^= 1;
    }
}

int main() {
    ifstream fin("theme.in");
    fin >> n;
    for (int i = 0; i < n; ++i) {
        fin >> a[i];
    }
    fin.close();

    dp();

    ofstream fout("theme.out");
    fout << ((ans < 4) ? 0 : (ans + 1)) << endl;
    fout.close();
    return 0;
}
