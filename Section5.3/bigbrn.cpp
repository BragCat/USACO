/*
 ID: bragcat1
 TASK: bigbrn
 LANG: C++
 */

#include <fstream>

using namespace std;

const int MAX_N = 1000;

int n, m;
short u[MAX_N][MAX_N], l[MAX_N][MAX_N], f[MAX_N][MAX_N];
char grid[MAX_N][MAX_N];

int main() {
    ifstream fin("bigbrn.in");
    fin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            grid[i][j] = '0';
        }
    }
    for (int i = 0; i < m; ++i) {
        int x, y;
        fin >> x >> y;
        grid[x - 1][y - 1] = '1';
    }
    fin.close();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '0') {
                if (i == 0) {
                    u[i][j] = 1;
                } else {
                    u[i][j] = u[i - 1][j] + 1;
                }
                if (j == 0) {
                    l[i][j] = 1;
                } else {
                    l[i][j] = l[i][j - 1] + 1;
                }
            }
        }
    }

    short answer = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '0') {
                if (i == 0 || j == 0) {
                    f[i][j] = 1;
                } else {
                    f[i][j] = min(short(f[i - 1][j - 1] + 1), min(u[i][j], l[i][j]));
                }
                answer = max(answer, f[i][j]);
            }
        }
    }

    ofstream fout("bigbrn.out");
    fout << answer << endl;
    fout.close();

    return 0;
}
