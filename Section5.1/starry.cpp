/*
 ID: bragcat1
 TASK: starry
 LANG: C++11
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXM = 105;
const int d[2][8] = {{0, -1, -1, -1, 0, 1, 1, 1},
                     {-1, -1, 0, 1, 1, 1, 0, -1}};

struct Cluster {
    char s[MAXM][MAXM];
    int numst, high, wide;

    bool operator == (const Cluster &b) {
        if (numst != b.numst) return false;

        if (high == b.high && wide == b.wide) {
            bool flag = false;

            for (int i = 0; i < high; ++i) {
                flag = true;
                for (int j = 0; j < wide; ++j)
                    if (s[i][j] != b.s[i][j]) {
                        flag = false;
                        break;
                    }
                if (!flag) break;
            }
            if (flag) return true;

            for (int i = 0; i < high; ++i) {
                flag = true;
                for (int j = 0; j < wide; ++j)
                    if (s[i][j] != b.s[high - i - 1][j]) {
                        flag = false;
                        break;
                    }
                if (!flag) break;
            }
            if (flag) return true;

            for (int i = 0; i < high; ++i) {
                flag = true;
                for (int j = 0; j < wide; ++j)
                    if (s[i][j] != b.s[i][wide - j - 1]) {
                        flag = false;
                        break;
                    }
                if (!flag) break;
            }
            if (flag) return true;

            for (int i = 0; i < high; ++i) {
                flag = true;
                for (int j = 0; j < wide; ++j)
                    if (s[i][j] != b.s[high - i - 1][wide - j - 1]) {
                        flag = false;
                        break;
                    }
                if (!flag) break;
            }
            if (flag) return true;
        }

        if (high == b.wide && wide == b.high) {
            bool flag = false;

            for (int i = 0; i < high; ++i) {
                flag = true;
                for (int j = 0; j < wide; ++j)
                    if (s[i][j] != b.s[wide - j - 1][i]) {
                        flag = false;
                        break;
                    }
                if (!flag) break;
            }
            if (flag) return true;

            for (int i = 0; i < high; ++i) {
                flag = true;
                for (int j = 0; j < wide; ++j)
                    if (s[i][j] != b.s[j][i]) {
                        flag = false;
                        break;
                    }
                if (!flag) break;
            }
            if (flag) return true;

            for (int i = 0; i < high; ++i) {
                flag = true;
                for (int j = 0; j < wide; ++j)
                    if (s[i][j] != b.s[j][high - i - 1]) {
                        flag = false;
                        break;
                    }
                if (!flag) break;
            }
            if (flag) return true;

            for (int i = 0; i < high; ++i) {
                flag = true;
                for (int j = 0; j < wide; ++j)
                    if (s[i][j] != b.s[wide - j - 1][high - i - 1]) {
                        flag = false;
                        break;
                    }
                if (!flag) break;
            }
            if (flag) return true;
        }
        return false;
    }
} clusters[30];

char g[MAXM][MAXM];
int h, w, mark[MAXM * MAXM], num[MAXM][MAXM], cnt1, cnt2, left, right, up, down;
bool vis[MAXM][MAXM];

Cluster create() {
    Cluster tmp;
    memset(tmp.s, 0, sizeof(tmp.s));
    tmp.numst = 0;
    tmp.high = down - up + 1;
    tmp.wide = right - left + 1;
    for (int i = 0; i < tmp.high; ++i)
        for (int j = 0; j < tmp.wide; ++j) {
            if (num[i + up][j + left] == cnt1) tmp.s[i][j] = '1', tmp.numst++;
            else tmp.s[i][j] = '0';
        }
    return tmp;
}

bool test(int x, int y) {
    return 0 <= x && x < h && 0 <= y && y < w;
}

void floodfill(int x0, int y0) {
    vis[x0][y0] = false;
    num[x0][y0] = cnt1;
    up = min(up, x0);
    down = max(down, x0);
    left = min(left, y0);
    right = max(right, y0);
    for (int i = 0; i < 8; ++i) {
        int x = x0 + d[0][i], y = y0 + d[1][i];
        if (test(x, y) && g[x][y] == '1' && vis[x][y]) floodfill(x, y);
    }
}

int main() {
    FILE *fin = fopen("starry.in", "r");
    fscanf(fin, "%d%d", &w, &h);
    for (int i = 0; i < h; ++i)
        fscanf(fin, "%s", g[i]);
    fclose(fin);

    memset(vis, true, sizeof(vis));
    memset(num, 0, sizeof(num));
    cnt1 = cnt2 = 0;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (vis[i][j] && g[i][j] == '1') {
                ++cnt1;
                up = down = i;
                left = right = j;
                floodfill(i, j);
                Cluster cl = create();
                bool flag = true;
                for (int k = 0; k < cnt2; ++k)
                    if (cl == clusters[k]) {
                        mark[cnt1] = k;
                        flag = false;
                        break;
                    }
                if (flag) clusters[mark[cnt1] = cnt2++] = cl;
            }
        }
    }

    FILE *fout = fopen("starry.out", "w");
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (g[i][j] != '0')
                fprintf(fout, "%c", mark[num[i][j]] + 'a');
            else
                fprintf(fout, "0");
        }
        fprintf(fout, "\n");
    }
    fclose(fout);
    return 0;
}