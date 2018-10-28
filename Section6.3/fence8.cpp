/*
 ID: bragcat1
 TASK: fence8
 LANG: C++11
 */

#include <algorithm>
#include <cstring>
#include <fstream>

using namespace std;

const int MAX_N = 50;
const int MAX_R = 1023;

int n, r, tot, waste, curTot;
int boards[MAX_N], rest[MAX_N];
int fences[MAX_R], sum[MAX_R];

bool judge(int cnt, int st) {
    if (cnt == 0) {
        return true;
    }
    if (curTot - waste < sum[cnt - 1]) {
        return false;
    }
    for (int i = st; i < n; ++i) {
        if (rest[i] >= fences[cnt - 1]) {
            curTot -= fences[cnt - 1];
            rest[i] -= fences[cnt - 1];
            if (rest[i] < fences[0]) {
                waste += rest[i];
            }
            if (cnt > 1 && fences[cnt - 2] == fences[cnt - 1]) {
                if (judge(cnt - 1, i)) {
                    return true;
                }
            } else {
                if (judge(cnt - 1, 0)) {
                    return true;
                }
            }
            if (rest[i] < fences[0]) {
                waste -= rest[i];
            }
            rest[i] += fences[cnt - 1];
            curTot += fences[cnt - 1];
        }
    }
    return false;
}

int main() {
    ifstream fin("fence8.in");
    fin >> n;
    for (int i = 0; i < n; ++i) {
        fin >> boards[i];
        tot += boards[i];
    }
    fin >> r;
    for (int i = 0; i < r; ++i) {
        fin >> fences[i];
    }
    fin.close();

    sort(begin(boards), begin(boards) + n);
    sort(begin(fences), begin(fences) + r);
    sum[0] = fences[0];
    for (int i = 1; i < r; ++i) {
        sum[i] = sum[i - 1] + fences[i];
    }

    int ans = 0, left = 0, right = r;
    while (left <= right) {
        int mid = (left + right) / 2;
        waste = 0;
        curTot = tot;
        memcpy(rest, boards, sizeof(boards));
        if (judge(mid, 0)) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    ofstream fout("fence8.out");
    fout << ans << endl;
    fout.close();
    return 0;
}
