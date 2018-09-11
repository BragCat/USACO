/*
 ID: bragcat1
 LANG: C++11
 TASK: camelot
 */

#include <fstream>
#include <cmath>

using namespace std;

const int MAXR = 30;
const int MAXC = 26;
const int MAX_DIST = MAXR + MAXC;
const int DIRECTION_NUM = 8;
const int DIRECTION_DELTA[DIRECTION_NUM][2] = {{-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}};

int r, c;
int kingRow, kingCol;

// how many steps should a knight take to arrive one cell
// the third dimension 0 represent the knight doesn't take the king, 1 represent the knight takes the king
int dist[MAXR][MAXC][2];

// total steps of all knight to arrive one cell
int totalDist[MAXR][MAXC];

// minimal extra steps of taking king to the cell
int extraDist[MAXR][MAXC];

// steps the king should take to get to the cell
int kingDist[MAXR][MAXC];

int walkAround(int x, int y, int kflag) {
    int oldD = dist[x][y][kflag];
    int newD = oldD;
    for (auto delta : DIRECTION_DELTA) {
        int newX = x + delta[0], newY = y + delta[1];
        if (newX >= 0 && newX < r && newY >= 0 && newY < c && dist[newX][newY][kflag] > oldD + 1) {
            newD = dist[newX][newY][kflag] = oldD + 1;
        }
    }
    if (kflag == 0 && dist[x][y][1] > dist[x][y][0] + kingDist[x][y]) {
        dist[x][y][1] = dist[x][y][0] + kingDist[x][y];
        newD = max(newD, dist[x][y][1]);
    }
    return newD;
}

void calcDist(int startRow, int startCol) {
    int maxDist;

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            dist[i][j][0] = dist[i][j][1] = MAX_DIST;
        }
    }
    dist[startRow][startCol][0] = 0;
    maxDist = dist[startRow][startCol][1] = kingDist[startRow][startCol];

    for (int d = 0; d <= maxDist; ++d) {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                for (int kflag = 0; kflag < 2; ++kflag) {
                    if (dist[i][j][kflag] == d) {
                        int newD = walkAround(i, j, kflag);
                        maxDist = max(maxDist, newD);
                    }
                }
            }
        }
    }
}

int main() {
    ifstream fin("camelot.in");
    fin >> r >> c;
    char ch;
    int x;
    fin >> ch >> x;
    kingCol = ch - 'A';
    kingRow = x - 1;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            int x = abs(i - kingRow);
            int y = abs(j - kingCol);
            extraDist[i][j] = kingDist[i][j] = max(x, y);
        }
    }
    while (fin >> ch >> x) {
        int knightRow = x - 1, knightCol = ch - 'A';
        calcDist(knightRow, knightCol);

        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                totalDist[i][j] += dist[i][j][0];
                extraDist[i][j] = min(extraDist[i][j], dist[i][j][1] - dist[i][j][0]);
            }
        }
    }
    fin.close();

    int minDist = totalDist[0][0] + extraDist[0][0];
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            minDist = min(minDist, totalDist[i][j] + extraDist[i][j]);
        }
    }

    ofstream fout("camelot.out");
    fout << minDist << endl;
    fout.close();

    return 0;
}
