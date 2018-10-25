/*
 ID: bragcat1
 TASK: charrec
 LANG: C++11
 */

#include <fstream>
#include <iostream>

using namespace std;

const int MAX_N = 1200;
const int CHAR_NUM = 27;
const int MAX_INT = ~0u >> 1;

int n;
char charMap[CHAR_NUM][20][20];
char record[MAX_N][20];
int f[MAX_N], p[MAX_N];
char g[MAX_N];
string ans;

int countDiff(char s[], char t[]) {
    int cnt = 0;
    for (int i = 0; i < 20; ++i) {
        cnt += (s[i] != t[i]);
    }
    return cnt;
}

int match(int st, int ed, char &ch) {
    int least = MAX_INT;
    if (ed - st + 1 == 19) {
        for (int i = 0; i < CHAR_NUM; ++i) {
            for (int j = 0; j < 20; ++j) {
                int x = st, y = ((j == 0) ? 1 : 0);
                int cnt = 0;
                while (x <= ed) {
                    cnt += countDiff(record[x], charMap[i][y]);
                    ++x, ++y;
                    if (y == j) {
                        ++y;
                    }
                }
                if (cnt < least) {
                    least = cnt;
                    ch = ((i == 26) ? ' ' : static_cast<char>(i + 'a'));
                }
            }
        }
    } else if (ed - st + 1 == 20) {
        for (int i = 0; i < CHAR_NUM; ++i) {
            int x = st, y = 0;
            int cnt = 0;
            while (x <= ed) {
                cnt += countDiff(record[x], charMap[i][y]);
                ++x, ++y;
            }
            if (cnt < least) {
                least = cnt;
                ch = ((i == 26) ? ' ' : static_cast<char>(i + 'a'));
            }
        }
    } else {
        for (int i = 0; i < CHAR_NUM; ++i) {
            for (int j = 0; j < 20; ++j) {
                int x = st, y = 0;
                int cnt = 0, pre = -1;
                bool flag = false;
                while (x <= ed) {
                    int cur = countDiff(record[x], charMap[i][y]);
                    ++x, ++y;
                    if (y == j) {
                        if (!flag) {
                            --y;
                            flag = true;
                        } else {
                            cnt += min(cur, pre);
                        }
                    } else {
                        cnt += cur;
                    }
                    pre = cur;
                }
                if (cnt < least) {
                    least = cnt;
                    ch = ((i == 26) ? ' ' : static_cast<char>(i + 'a'));
                }
            }
        }
    }
    return least;
}

int main() {
    ifstream ffont("font.in");
    ffont >> n;
    for (int i = 0; i < n / 20; ++i) {
        int index = ((i == 0) ? CHAR_NUM - 1 : (i - 1));
        for (int j = 0; j < 20; ++j) {
            string s;
            ffont >> s;
            for (int k = 0; k < 20; ++k) {
                charMap[index][j][k] = s[k];
            }
        }
    }
    ffont.close();

    ifstream fin("charrec.in");
    fin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 20; ++j) {
            fin >> record[i][j];
        }
        f[i] = MAX_INT;
    }
    fin.close();

    f[0] = 0;
    for (int i = 19; i <= n; ++i) {
        int least = MAX_INT;
        char matchCh;
        int pre = -1;
        for (int j = 19; j < 22; ++j) {
            if (i - j >= 0 && f[i - j] != MAX_INT) {
                char ch;
                int corCnt = f[i - j] + match(i - j + 1, i, ch);
                if (corCnt < least) {
                    least = corCnt;
                    matchCh = ch;
                    pre = i - j;
                }
            }
        }
        f[i] = least, g[i] = matchCh, p[i] = pre;
    }

    int i = n;
    while (i > 0) {
        ans = g[i] + ans;
        i = p[i];
    }

    ofstream fout("charrec.out");
    fout << ans << endl;
    fout.close();
    return 0;
}
