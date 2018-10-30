/*
 ID: bragcat1
 LANG: C++11
 TASK: betsy
 */

#include <fstream>

using namespace std;

const int MAX_N = 7;
const int DIR_NUM = 4;
const int D[DIR_NUM][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int n, ans;
bool visited[MAX_N][MAX_N];

int getAdjCnt(int x, int y) {
    int cnt = 0;
    for (int i = 0; i < DIR_NUM; ++i) {
        int nx = x + D[i][0], ny = y + D[i][1];
        cnt += (nx >= 0 && nx < n && ny >= 0 && ny < n && !visited[nx][ny]);
    }
    return cnt;
}

void dfs(int x, int y, int cnt) {
    if (x == n - 1 && y == 0) {
        if (cnt == n * n) {
            ++ans;
        }
        return;
    }

    if ((x > 0 && !visited[x - 1][y]) && (y == 0 || visited[x][y - 1])
        && (x < n - 1 && !visited[x + 1][y]) && (y == n - 1 || visited[x][y + 1])) {
        return;
    }
    if ((x == 0 || visited[x - 1][y]) && (y > 0 && !visited[x][y - 1])
        && (x == n - 1 || visited[x + 1][y]) && (y < n - 1 && !visited[x][y + 1])) {
        return;
    }

    int tot = 0, xx, yy;
    for (int i = 0; i < DIR_NUM; ++i) {
        int nx = x + D[i][0], ny = y + D[i][1];
        if (nx > 0 && nx < n - 1 && ny > 0 && ny < n - 1 && !visited[nx][ny]) {
            int adjCnt = getAdjCnt(nx, ny);
            if (adjCnt < 2) {
                ++tot;
                xx = nx, yy = ny;
            }
        }
    }

    if (tot > 1) {
        return;
    } else if (tot == 1) {
        visited[xx][yy] = true;
        dfs(xx, yy, cnt + 1);
        visited[xx][yy] = false;
    } else {
        for (int i = 0; i < DIR_NUM; ++i) {
            int nx = x + D[i][0], ny = y + D[i][1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visited[nx][ny]) {
                visited[nx][ny] = true;
                dfs(nx, ny, cnt + 1);
                visited[nx][ny] = false;
            }
        }
    }
}

int main() {
    ifstream fin("betsy.in");
    fin >> n;
    fin.close();

    visited[0][0] = true;
    dfs(0, 0, 1);

    ofstream fout("betsy.out");
    fout << ans << endl;
    fout.close();
    return 0;
}
