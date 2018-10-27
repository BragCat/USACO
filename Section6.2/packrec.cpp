/*
 ID: bragcat1
 LANG: C++11
 TASK: packrec
 */

#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

const int NUM = 4;

int rect[NUM][2], r[NUM][2];
bool used[NUM];
int perm[NUM];
vector<pair<int, int>> ans;

bool cmp(const pair<int, int> &a, const pair<int, int> &b) {
    return a.first < b.first || (a. first == b.first && a.second < b.second);
}

void updateAns(int x, int y) {
    if (x > y) {
        int t = x;
        x = y;
        y = t;
    }
    if (ans.empty() || ans[0].first * ans[0].second == x * y) {
        ans.emplace_back(x, y);
    } else if (ans[0].first * ans[0].second > x * y) {
        ans.clear();
        ans.emplace_back(x, y);
    }
}

void calcArea() {
    // 1
    int x = 0, y = 0;
    for (int i = 0; i < NUM; ++i) {
        x += r[i][0];
        y = max(y, r[i][1]);
    }
    updateAns(x, y);

    // 2
    x = max(r[0][0], r[1][0] + r[2][0] + r[3][0]);
    y = r[0][1] + max(r[1][1], max(r[2][1], r[3][1]));
    updateAns(x, y);

    // 3
    x = max(r[0][0], r[1][0] + r[2][0]) + r[3][0];
    y = max(r[0][1] + max(r[1][1], r[2][1]), r[3][1]);
    updateAns(x, y);

    // 4
    x = max(r[0][0], r[1][0]) + r[2][0] + r[3][0];
    y = max(r[0][1] + r[1][1], max(r[2][1], r[3][1]));
    updateAns(x, y);

    // 5
    if (r[0][1] >= r[2][1] + r[3][1]) {
        x = max(r[0][0] + max(r[2][0], r[3][0]), r[1][0]);
        y = r[0][1] + r[1][1];
        updateAns(x, y);
    } else if (r[3][1] >= r[0][1] + r[1][1]) {
        x = max(max(r[0][0], r[1][0]) + r[3][0], r[2][0]);
        y = r[3][1] + r[2][1];
        updateAns(x, y);
    } else {
        x = max(r[0][0], r[1][0]) + max(r[2][0], r[3][0]);
        y = max(r[0][1] + r[1][1], r[2][1] + r[3][1]);
        updateAns(x, y);

        if (r[0][1] < r[3][1] && r[1][0] < r[0][0] && r[2][0] > r[3][0]) {
            x = max(r[0][0] + r[3][0], r[1][0] + r[2][0]);
            updateAns(x, y);
        }
    }
}

void calcRect() {
    for (int i = 0; i < 16; ++i) {
        int state = i;
        for (int j = 0; j < 4; ++j) {
            if (state & 1) {
                r[j][0] = rect[perm[j]][0], r[j][1] = rect[perm[j]][1];
            } else {
                r[j][0] = rect[perm[j]][1], r[j][1] = rect[perm[j]][0];
            }
            state = state >> 1;
        }
        calcArea();
    }
}

void dfs(int ind) {
    if (ind == NUM) {
        calcRect();
        return;
    }
    for (int i = 0; i < NUM; ++i) {
        if (!used[i]) {
            used[i] = true;
            perm[ind] = i;
            dfs(ind + 1);
            used[i] = false;
        }
    }
}

int main() {
    ifstream fin("packrec.in");
    for (auto &i : rect) {
        fin >> i[0] >> i[1];
    }
    fin.close();

    dfs(0);
    sort(ans.begin(), ans.end(), cmp);
    auto it = unique(ans.begin(), ans.end());
    ans.resize(it - ans.begin());

    ofstream fout("packrec.out");
    fout << ans[0].first * ans[0].second << endl;
    for (const auto &p : ans) {
        fout << p.first << ' ' << p.second << endl;
    }
    fout.close();

    return 0;
}
