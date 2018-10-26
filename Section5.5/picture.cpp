/*
 ID: bragcat1
 TASK: picture
 LANG: C++11
 */

#include <algorithm>
#include <cstring>
#include <fstream>

using namespace std;

const int MAX_N = 5000;
const int MAX_X = 10000;

int n;
int rect[MAX_N][4];

int ans;
struct Line{
    int p, q;
    int label, common;
}line[MAX_N * 2];
int segment[MAX_X * 2 + 1];

bool cmp(const Line &a, const Line &b) {
    if (a.common < b.common) {
        return true;
    } else if (a.common > b.common) {
        return false;
    } else {
        return a.label < b.label;
    }
}

void add(int l, int r, int delta) {
    for (int i = l; i < r; ++i) {
        segment[i] += delta;
        if (delta == 1 && segment[i] == 1) {
            ++ans;
        } else if (delta == -1 && segment[i] == 0) {
            ++ans;
        }
    }
}

void cover() {
    sort(begin(line), begin(line) + n * 2, cmp);
    memset(segment, 0, sizeof(segment));
    for (int i = 0; i < n * 2; ++i) {
        if (line[i].label == 0) {
            add(line[i].p, line[i].q, 1);
        } else {
            add(line[i].p, line[i].q, -1);
        }
    }
}

int main() {
    ifstream fin("picture.in");
    fin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 4; ++j) {
            fin >> rect[i][j];
            rect[i][j] += MAX_X;
        }
    }
    fin.close();

    for (int i = 0; i < n; ++i) {
        line[i * 2].p = line[i * 2 + 1].p = rect[i][0];
        line[i * 2].q = line[i * 2 + 1].q = rect[i][2];
        line[i * 2].label = 0;
        line[i * 2 + 1].label = 1;
        line[i * 2].common = rect[i][1];
        line[i * 2 + 1].common = rect[i][3];
    }
    cover();

    for (int i = 0; i < n; ++i) {
        line[i * 2].p = line[i * 2 + 1].p = rect[i][1];
        line[i * 2].q = line[i * 2 + 1].q = rect[i][3];
        line[i * 2].label = 0;
        line[i * 2 + 1].label = 1;
        line[i * 2].common = rect[i][0];
        line[i * 2 + 1].common = rect[i][2];
    }
    cover();

    ofstream fout("picture.out");
    fout << ans << endl;
    fout.close();

    return 0;
}