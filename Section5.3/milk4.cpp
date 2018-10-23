/*
 ID: bragcat1
 TASK: milk4
 LANG: C++11
 */

#include <fstream>
#include <algorithm>

using namespace std;

const int MAX_Q = 20000;
const int MAX_N = 100;

int q, n;
int cap[MAX_N];
int ansCnt;
int ansNum[MAX_N];

bool dp(int cnt) {
    bool f[MAX_Q + 1] = {false};
    f[0] = true;
    for (int i = 0; i < cnt; ++i) {
        for (int j = ansNum[i]; j <= q; ++j) {
            f[j] |= f[j - ansNum[i]];
        }
    }
    return f[q];
}

bool dfs(int lim, int cur, int st) {
    if (cur == lim) {
        return dp(lim);
    }
    for (int i = st; i < n; ++i) {
        ansNum[cur] = cap[i];
        if (dfs(lim, cur + 1, i + 1)) {
            return true;
        }
    }
    return false;
}

void dfsMaster() {
    for (int i = 1; i <= n; ++i) {
        if (dfs(i, 0, 0)) {
            ansCnt = i;
            break;
        }
    }
}

int main() {
    ifstream fin("milk4.in");
    fin >> q >> n;
    for (int i = 0; i < n; ++i) {
        fin >> cap[i];
    }
    fin.close();

    sort(begin(cap), begin(cap) + n);
    dfsMaster();

    ofstream fout("milk4.out");
    fout << ansCnt;
    for (int i = 0; i < ansCnt; ++i) {
        fout << " " << ansNum[i];
    }
    fout << endl;
    fout.close();

    return 0;
}
