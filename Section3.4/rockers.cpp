/*
 ID: bragcat1
 LANG: C++11
 TASK: rockers
 */

#include <fstream>

using namespace std;

const int MAXN = 20, MAXM = 20, MAXTIME = 20;

int n, t, m;
int f[MAXN + 1][MAXM + 1][MAXTIME + 1];
int songTimes[MAXN];

int main() {
    ifstream fin("rockers.in");
    fin >> n >> t >> m;
    for (int i = 0; i < n; ++i) {
        fin >> songTimes[i];
    }
    fin.close();

    for (int i = 1; i <= n; ++i) {
        int songTime = songTimes[i - 1];
        for (int j = 1; j <= m; ++j) {
            for (int k = 0; k <= t; ++k) {
                f[i][j][k] = f[i - 1][j][k];
                if (k == 0) {
                    f[i][j][k] = max(f[i][j][k], f[i][j - 1][t]);
                }
                else {
                    f[i][j][k] = max(f[i][j][k], f[i][j][k - 1]);
                }
                if (k >= songTime) {
                    f[i][j][k] = max(f[i][j][k], f[i - 1][j][k - songTime] + 1);
                }
            }
        }
    }

    ofstream fout("rockers.out");
    fout << f[n][m][t] << endl;
    fout.close();
    return 0;
}
