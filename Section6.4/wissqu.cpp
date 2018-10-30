/*
 ID: bragcat1
 TASK: wissqu
 LANG: C++11
 */

#include <fstream>
#include <vector>

using namespace std;

const int MAX_N = 4;
const int TYPE_NUM = 5;
const int DIR_NUM = 8;
const int d[DIR_NUM][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}};

int ans;
int num[TYPE_NUM];
int square[MAX_N][MAX_N];
bool isNew[MAX_N][MAX_N];
vector<int> cowList;
vector<pair<int, int>> placeList;
ofstream fout("wissqu.out");
bool isFirst = true;

bool valid(int x, int y, int t) {
    if (isNew[x][y] || square[x][y] == t) {
        return false;
    }
    for (int i = 0; i < DIR_NUM; ++i) {
        int nx = x + d[i][0], ny = y + d[i][1];
        if (nx >= 0 && nx < MAX_N && ny >= 0 && ny < MAX_N) {
            if (square[nx][ny] == t) {
                return false;
            }
        }
    }
    return true;
}

void dfs(int cnt) {
    if (cnt == MAX_N * MAX_N) {
        if (isFirst) {
            for (int i = 0; i < cnt; ++i) {
                fout << static_cast<char>(cowList[i] + 'A') << ' '
                    << placeList[i].first + 1 << ' ' << placeList[i].second + 1 << endl;
            }
            isFirst = false;
        }
        ++ans;
        return;
    }

    int stType = 0, edType = TYPE_NUM - 1;
    if (cnt == 0) {
        stType = edType = 'D' - 'A';
    }
    for (int t = stType; t <= edType; ++t) {
        if (num[t] > 0) {
            for (int i = 0; i < MAX_N; ++i) {
                for (int j = 0; j < MAX_N; ++j) {
                    if (valid(i, j, t)) {
                        int oldT = square[i][j];
                        square[i][j] = t;
                        isNew[i][j] = true;
                        --num[t];
                        if (isFirst) {
                            cowList.push_back(t);
                            placeList.emplace_back(i, j);
                        }
                        dfs(cnt + 1);
                        if (isFirst) {
                            cowList.pop_back();
                            placeList.pop_back();
                        }
                        ++num[t];
                        isNew[i][j] = false;
                        square[i][j] = oldT;
                    }
                }
            }
        }
    }
}

int main() {
    ifstream fin("wissqu.in");
    char ch;
    for (int i = 0; i < MAX_N; ++i) {
        for (int j = 0; j < MAX_N; ++j) {
            fin >> ch;
            square[i][j] = ch - 'A';
            ++num[square[i][j]];
        }
    }
    fin.close();

    --num['C' - 'A'], ++num['D' - 'A'];

    dfs(0);

    fout << ans << endl;
    fout.close();

    return 0;
}
