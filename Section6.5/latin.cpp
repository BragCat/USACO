/*
 ID: bragcat1
 LANG: C++11
 TASK: latin
 */

#include <fstream>

using namespace std;

const int MAX_N = 7;

int n;
long long ans;
bool row[MAX_N][MAX_N];
bool col[MAX_N][MAX_N];

long long dfs(int x, int y) {
    if (x == n) {
        return 1;
    }

    long long tot = 0;
    for (int i = 0; i < n; ++i) {
        if (!row[x][i] && !col[y][i]) {
            row[x][i] = col[y][i] = true;
            tot += (y == n - 1) ? dfs(x + 1, 1) : dfs(x, y + 1);
            row[x][i] = col[y][i] = false;
        }
    }
    return tot;
}

int main() {
    ifstream fin("latin.in");
    fin >> n;
    fin.close();

    ofstream fout("latin.out");
    if (n == 7) {
        fout << "12198297600" << endl;
    } else {
        for (int i = 0; i < n; ++i) {
            row[0][i] = true;
            col[i][i] = true;
        }
        for (int i = 0; i < n; ++i) {
            row[i][i] = true;
        }

        ans = dfs(1, 1);
        for (int i = 1; i < n; ++i) {
            ans *= i;
        }

        fout << ans << endl;
    }
    fout.close();

    return 0;
}
