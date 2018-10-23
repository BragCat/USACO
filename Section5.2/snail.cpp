/*
 ID: bragcat1
 TASK: snail
 LANG: C++11
 */

#include <fstream>

using namespace std;

const int MAX_N = 120;
const int MAX_B = 200;
const int DIR_NUM = 4;
const int DIR[DIR_NUM][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int squares[MAX_N][MAX_N];
int n, b, answer;

bool valid(int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < n);
}

void traverse(int tot, int x, int y) {
    for (int i = 0; i < DIR_NUM; ++i) {
        int dx = DIR[i][0], dy = DIR[i][1];
        int step = 1, nx = x + dx, ny = y + dy;
        while (valid(nx, ny) && squares[nx][ny] == 0) {
            squares[nx][ny] = 2;
            ++step;
            nx += dx;
            ny += dy;
        }
        if (valid(nx, ny) && squares[nx][ny] == 2) {
            --step;
            nx -= dx, ny -= dy;
            if (tot + step > answer) {
                answer = tot + step;
            }
        } else {
            --step;
            nx -= dx, ny -= dy;
            if (step > 0) {
                traverse(tot + step, nx, ny);
            }
        }
        while (step > 0) {
            squares[nx][ny] = 0;
            --step;
            nx -= dx, ny -= dy;
        }
    }
}

int main() {
    ifstream fin("snail.in");
    fin >> n >> b;
    char ch;
    fin >> ch;
    for (int i = 0; i < b; ++i) {
        int y = ch - 'A';
        fin >> ch;
        int x = 0;
        while (ch >= '0' && ch <= '9') {
            x = x * 10 + ch - '0';
            if (!(fin >> ch)) {
                break;
            }
        }
        --x;
        squares[x][y] = 1;
    }
    fin.close();

    squares[0][0] = 2;
    traverse(1, 0, 0);

    ofstream fout("snail.out");
    fout << answer << endl;
    fout.close();
    return 0;
}
