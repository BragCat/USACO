/*
 ID: bragcat1
 LANG: C++11
 TASK: checker
 */

#include <cmath>
#include <fstream>

using namespace std;

int full, sum;
int a[14],n;
ifstream fin("checker.in");
ofstream fout("checker.out");

void dfs(int row, int ld, int rd, int deep) {
    int pos, p;
    if (row != full) {
        pos = full & ~(row | ld | rd);
        while (pos != 0) {
            p = pos & -pos;
            pos = pos - p;
            if (sum < 3) {
                a[deep] = p;
            }
            dfs(row + p, (ld + p) << 1, (rd + p) >> 1, deep + 1);
        }
    } else {
        ++sum;
        if (sum <= 3) {
            for (int i = 1;i <= n - 1; ++i) {
                fout << static_cast<int>(log(a[i]) / log(2) + 1) << ' ';
            }
            fout << static_cast<int>(log(a[n]) / log(2) + 1) << endl;
        }
    }

}

int main() {
    fin >> n;
    fin.close();

    full = (1 << n) - 1;
    dfs(0, 0, 0, 1);

    fout << sum << endl;
    fout.close();

    return 0;
}
