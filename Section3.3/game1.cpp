/*
 ID: bragcat1
 LANG: C++11
 TASK: game1
 */

#include <fstream>

using namespace std;

const int MAXN = 100;

int n;
int number[MAXN + 1], sum[MAXN + 1];
int f[MAXN + 1][MAXN + 1];

int main() {
    ifstream fin("game1.in");
    fin >> n;
    for (int i = 1; i <= n; ++i) {
        fin >> number[i];
        sum[i] = sum[i - 1] + number[i];
    }
    fin.close();

    for (int len = 0; len < n; ++len) {
        for (int st = 1; st <= n - len; ++st) {
            f[st][st + len] = sum[st + len] - sum[st - 1] - min(f[st][st + len - 1], f[st + 1][st + len]);
        }
    }

    ofstream fout("game1.out");
    fout << f[1][n] << " " << sum[n] - f[1][n] << endl;
    fout.close();
    return 0;
}
