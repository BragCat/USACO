/*
 ID: bragcat1
 LANG: C++11
 TASK: range
 */

#include <fstream>

using namespace std;

const int MAXN = 250;
const char ONE = '1', ZERO = '0';

typedef int range[MAXN][MAXN];

char field[MAXN][MAXN];
range toLeft, toUp, maxRange;
int cnt[MAXN + 1];
int n;


int main() {
    ifstream fin("range.in");
    fin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> field[i][j];
        }
    }
    fin.close();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (field[i][j] == ONE) {
                toLeft[i][j] = j >= 1 ? toLeft[i][j - 1] + 1 : 1;
                toUp[i][j] = i >= 1 ? toUp[i - 1][j] + 1 : 1;
                maxRange[i][j] = min(toLeft[i][j], toUp[i][j]);
                if (i >= 1 && j >= 1) {
                    maxRange[i][j] = min(maxRange[i - 1][j - 1] + 1, maxRange[i][j]);
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 2; k <= maxRange[i][j]; ++k) {
                ++cnt[k];
            }
        }
    }

    ofstream fout("range.out");
    for (int i = 2; i <= n; ++i) {
        if (cnt[i] > 0) {
            fout << i << " " << cnt[i] << endl;
        }
    }
    fout.close();
    return 0;
}
