/*
 ID: bragcat1
 LANG: C++11
 TASK: clocks
 */

#include <cstring>
#include <fstream>
#include <vector>

using namespace std;

const int N = 3;
const int MOVE_NUM = 9;
const int D[MOVE_NUM][N][N] = {{{3, 3, 0}, {3, 3, 0}, {0, 0, 0}},
                               {{3, 3, 3}, {0, 0, 0}, {0, 0, 0}},
                               {{0, 3, 3}, {0, 3, 3}, {0, 0, 0}},
                               {{3, 0, 0}, {3, 0, 0}, {3, 0, 0}},
                               {{0, 3, 0}, {3, 3, 3}, {0, 3, 0}},
                               {{0, 0, 3}, {0, 0, 3}, {0, 0, 3}},
                               {{0, 0, 0}, {3, 3, 0}, {3, 3, 0}},
                               {{0, 0, 0}, {0, 0, 0}, {3, 3, 3}},
                               {{0, 0, 0}, {0, 3, 3}, {0, 3, 3}}};

int clocks[N][N];
vector<int> seq;

bool checkClock() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (clocks[i][j] != 0) {
                return false;
            }
        }
    }
    return true;
}

bool dfs(int t, int tot) {
    if (tot == 0) {
        return checkClock();
    }
    if (t == MOVE_NUM) {
        return false;
    }
    for (int i = min(3, tot); i >= 0; --i) {
        for (int j = 0; j < i; ++j) {
            seq.push_back(t);
        }
        int temp[N][N];
        memcpy(temp, clocks, sizeof(clocks));
        for (int p = 0; p < N; ++p) {
            for (int q = 0; q < N; ++q) {
                clocks[p][q] = (clocks[p][q] + D[t][p][q] * i) % 12;
            }
        }
        if (dfs(t + 1, tot - i)) {
            return true;
        }
        memcpy(clocks, temp, sizeof(clocks));
        for (int j = 0; j < i; ++j) {
            seq.pop_back();
        }
    }
    return false;
}

int main() {
    ifstream fin("clocks.in");
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            fin >> clocks[i][j];
            clocks[i][j] %= 12;
        }
    }
    fin.close();

    for (int i = 0; i < 4 * MOVE_NUM; ++i) {
        if (dfs(0, i)) {
            break;
        }
    }

    ofstream fout("clocks.out");
    for (int i = 0; i < seq.size(); ++i) {
        if (i > 0) {
            fout << ' ';
        }
        fout << seq[i] + 1;
    }
    fout << endl;
    fout.close();
    return 0;
}
