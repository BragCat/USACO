/*
 ID: bragcat1
 TASK: rect1
 LANG: C++11
 */

#include <fstream>

using namespace std;

const int MAX_N = 1000;
const int MAX_COLOR = 2500;

int n;
int rect[MAX_N + 1][5];
int cnt[MAX_COLOR + 1];

int split(int llx, int lly, int urx, int ury, int ind) {
    if (ind == n) {
        return (urx - llx) * (ury - lly);
    }
    int llxi = rect[ind][0], llyi = rect[ind][1], urxi = rect[ind][2], uryi = rect[ind][3];
    if (llx >= urxi || lly >= uryi || urx <= llxi || ury <= llyi) {
        return split(llx, lly, urx, ury, ind + 1);
    }
    if (llx >= llxi && lly >= llyi && urx <= urxi && ury <= uryi) {
        return 0;
    }
    int ans = 0;
    if (uryi >= lly && uryi < ury) {
        ans += split(llx, uryi, urx, ury, ind + 1);
    }
    if (llyi > lly && llyi <= ury) {
        ans += split(llx, lly, urx, llyi, ind + 1);
    }
    int ly = max(lly, llyi), ry = min(ury, uryi);
    if (llxi > llx && llxi <= urx) {
        ans += split(llx, ly, llxi, ry, ind + 1);
    }
    if (urxi >= llx && urxi < urx) {
        ans += split(urxi, ly, urx, ry, ind + 1);
    }
    return ans;
}

int main() {
    ifstream fin("rect1.in");
    rect[0][0] = rect[0][1] = 0, rect[0][4] = 1;
    fin >> rect[0][2] >> rect[0][3] >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 5; ++j) {
            fin >> rect[i + 1][j];
        }
    }
    fin.close();

    ++n;
    for (int i = 0; i < n; ++i) {
        cnt[rect[i][4]] += split(rect[i][0], rect[i][1], rect[i][2], rect[i][3], i + 1);
    }

    ofstream fout("rect1.out");
    for (int i = 1; i < MAX_COLOR; ++i) {
        if (cnt[i] > 0) {
            fout << i << ' ' << cnt[i] << endl;
        }
    }
    fout.close();

    return 0;
}
