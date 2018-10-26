/*
 ID: bragcat1
 TASK: twofive
 LANG: C++11
 */

#include <cstring>
#include <fstream>

using namespace std;

const int MAX_N = 5;
const int MAX_CHAR = 25;
constexpr int MAX_STATE = (MAX_N + 1) * (MAX_N + 1) * (MAX_N + 1) * (MAX_N + 1) * (MAX_N + 1);


int x[MAX_CHAR], y[MAX_CHAR];
int f[MAX_STATE];
int rowCnt[MAX_N];

int dfs(int ch) {
    int state = 0;
    for (int i = 0; i < MAX_N; ++i) {
        state = state * (MAX_N + 1) + rowCnt[i];
    }
    if (f[state] == -1) {
        f[state] = 0;
        if (x[ch] == -1) {
            for (int i = 0; i < MAX_N; ++i) {
                if ((i == 0 && rowCnt[i] < MAX_N) || rowCnt[i] < rowCnt[i - 1]) {
                    x[ch] = i, y[ch] = rowCnt[i];
                    ++rowCnt[i];
                    f[state] += dfs(ch + 1);
                    --rowCnt[i];
                    x[ch] = y[ch] = -1;
                }
            }
        } else {
            if (((x[ch] == 0 && rowCnt[x[ch]] < MAX_N) || rowCnt[x[ch]] < rowCnt[x[ch] - 1]) && rowCnt[x[ch]] == y[ch]) {
                ++rowCnt[x[ch]];
                f[state] += dfs(ch + 1);
                --rowCnt[x[ch]];
            }
        }
    }
    return f[state];
}

int dp() {
    memset(rowCnt, 0, sizeof(rowCnt));
    memset(f, -1, sizeof(f));
    f[MAX_STATE - 1] = 1;
    return dfs(0);
}

string numToStr(int n) {
    memset(x, -1, sizeof(x));
    memset(y, -1, sizeof(y));
    for (int i = 0; i < MAX_N; ++i) {
        for (int j = 0; j < MAX_N; ++j) {
            for (int k = 0; k < MAX_CHAR; ++k) {
                if (x[k] == -1) {
                    x[k] = i, y[k] = j;
                    int cnt = dp();
                    if (cnt >= n) {
                        break;
                    }
                    n -= cnt;
                    x[k] = y[k] = -1;
                }
            }
        }
    }
    string str(MAX_CHAR, ' ');
    for (int i = 0; i < MAX_CHAR; ++i) {
        str[x[i] * MAX_N + y[i]] = static_cast<char>(i + 'A');
    }
    return str;
}

int strToNum(string str) {
    memset(x, -1, sizeof(x));
    memset(y, -1, sizeof(y));
    int num = 0;
    for (int i = 0; i < MAX_N; ++i) {
        for (int j = 0; j < MAX_N; ++j) {
            int p = i * MAX_N + j;
            int c = str[p] - 'A';
            for (int k = 0; k < c; ++k) {
                if (x[k] == -1) {
                    x[k] = i, y[k] = j;
                    num += dp();
                    x[k] = y[k] = -1;
                }
            }
            x[c] = i, y[c] = j;
        }
    }
    return num + 1;
}


int main() {
    ifstream fin("twofive.in");
    ofstream fout("twofive.out");
    char ch;
    fin >> ch;
    if (ch == 'N') {
        int n;
        fin >> n;
        fout << numToStr(n) << endl;
    } else {
        string str;
        fin >> str;
        fout << strToNum(str) << endl;
    }
    fin.close();
    fout.close();
    return 0;
}