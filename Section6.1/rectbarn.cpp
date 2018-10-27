/*
 ID: bragcat1
 TASK: rectbarn
 LANG: C++11
 */

#include <fstream>
#include <vector>

using namespace std;

const int MAX_R = 3000;
const int MAX_C = 3000;

int r, c, p;
bool field[MAX_R][MAX_C];
int h[MAX_C];

int main() {
    ifstream fin("rectbarn.in");
    fin >> r >> c >> p;
    for (int i = 0; i < p; ++i) {
        int x, y;
        fin >> x >> y;
        --x, --y;
        field[x][y] = true;
    }
    fin.close();

    int ans = 0;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (field[i][j]) {
                h[j] = 0;
            } else if (i == 0) {
                h[j] = 1;
            } else {
                h[j] = h[j] + 1;
            }
        }
        int l[MAX_C], r[MAX_C];
        vector<int> q;
        for (int j = 0; j < c; ++j) {
            while (!q.empty() && h[q.back()] >= h[j]) {
                q.pop_back();
            }
            if (q.empty()) {
                l[j] = 0;
            } else {
                l[j] = q.back() + 1;
            }
            q.push_back(j);
        }
        q.clear();
        for (int j = c - 1; j >= 0; --j) {
            while (!q.empty() && h[q.back()] >= h[j]) {
                q.pop_back();
            }
            if (q.empty()) {
                r[j] = c - 1;
            } else {
                r[j] = q.back() - 1;
            }
            q.push_back(j);
        }
        for (int j = 0; j < c; ++j) {
            ans = max(ans, h[j] * (r[j] - l[j] + 1));
        }
    }

    ofstream fout("rectbarn.out");
    fout << ans << endl;
    fout.close();
    return 0;
}
