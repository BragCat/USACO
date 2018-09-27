/*
 ID: bragcat1
 LANG: C++11
 TASK: frameup
 */

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_H = 30;
const int MAX_W = 30;
const int MAX_CHAR = 26;
const int MAX_INT = ~0u >> 1;

int h, w;
bool covered[MAX_CHAR];
int axis[MAX_CHAR][4];
char map[MAX_H][MAX_W];
bool exist[MAX_CHAR];
int cnt;
string answer;
vector<string> answerList;
ifstream fin;
ofstream fout;

bool check(int c) {
    char ch = static_cast<char>(c + 'A');
    int minH = axis[c][0], maxH = axis[c][1], minW = axis[c][2], maxW = axis[c][3];
    int x = minH, y = minW;
    while (x <= maxH) {
        if (map[x][y] == ch || covered[map[x][y] - 'A']) {
            ++x;
        }
        else {
            return false;
        }
    }
    x = maxH;
    while (y <= maxW) {
        if (map[x][y] == ch || covered[map[x][y] - 'A']) {
            ++y;
        }
        else {
            return false;
        }
    }
    y = maxW;
    while (x >= minH) {
        if (map[x][y] == ch || covered[map[x][y] - 'A']) {
            --x;
        }
        else {
            return false;
        }
    }
    x = minH;
    while (y >= minW) {
        if (map[x][y] == ch || covered[map[x][y] - 'A']) {
            --y;
        }
        else {
            return false;
        }
    }
    return true;
}

void dfs(int coveredCnt) {
    if (coveredCnt == cnt) {
        string tempAnswer = answer;
        reverse(tempAnswer.begin(), tempAnswer.end());
        answerList.push_back(tempAnswer);
        return;
    }
    for (int i = 0; i < MAX_CHAR; ++i) {
        if (exist[i] && !covered[i] && check(i)) {
            covered[i] = true;
            answer.push_back(static_cast<char>('A' + i));
            dfs(coveredCnt + 1);
            answer.pop_back();
            covered[i] = false;
        }
    }
}

int main() {
    for (auto a : axis) {
        for (int i = 0; i < 4; ++i) {
            a[i] = MAX_INT;
        }
    }
    fin.open("frameup.in");
    fin >> h >> w;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            fin >> map[i][j];
            if (map[i][j] >= 'A' && map[i][j] <= 'Z') {
                int x = map[i][j] - 'A';
                exist[x] = true;
                if (axis[x][0] == MAX_INT || axis[x][0] > i) {
                    axis[x][0] = i;
                }
                if (axis[x][1] == MAX_INT || axis[x][1] < i) {
                    axis[x][1] = i;
                }
                if (axis[x][2] == MAX_INT || axis[x][2] > j) {
                    axis[x][2] = j;
                }
                if (axis[x][3] == MAX_INT || axis[x][3] < j) {
                    axis[x][3] = j;
                }
            }
        }
    }
    fin.close();

    for (auto a : axis) {
        cnt += (a[0] != MAX_INT);
    }

    dfs(0);
    sort(answerList.begin(), answerList.end());

    fout.open("frameup.out");
    for (auto answer : answerList) {
        fout << answer << endl;
    }
    fout.close();
    return 0;
}
