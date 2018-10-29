/*
 ID: bragcat1
 LANG: C++11
 TASK: prime3
 */
#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

struct Trie {
    Trie *next[10];
    Trie() {
        for (int i = 0; i < 10; ++i) {
            next[i] = nullptr;
        }
    }
};

void insert(Trie *trie, string str) {
    for (int i = 0; i < str.size(); ++i) {
        if (!trie->next[str[i] - '0']) {
            trie->next[str[i] - '0'] = new Trie();
        }
        trie = trie->next[str[i] - '0'];
    }
}

bool search(Trie *trie, string str) {
    for (int i = 0; i < str.size(); ++i) {
        if (!trie->next[str[i] - '0']) {
            return false;
        }
        trie = trie->next[str[i] - '0'];
    }
    return true;
}

bool isPrime(string str) {
    if ((str[4] - '0') % 2 == 0) {
        return false;
    }

    int num = 0;
    for (int i = 0; i < str.size(); ++i) {
        num = num * 10 + str[i] - '0';
    }

    int upbound = sqrt(num);
    for (int i = 3; i <= upbound; ++i) {
        if (num % i == 0) {
            return false;
        }
    }

    return true;
}

void alltuples_recur(int index, string partial, int partialsum,
        vector<string> &tuples, const int sum, const int leftcorner) {
    if (partialsum > sum) {
        return;
    }

    if (index == 5) {
        if (partialsum != sum) {
            return;
        }

        if (!isPrime(partial)) {
            return;
        }

        tuples.push_back(partial);

        return;
    }

    char start = '0';
    if (index == 0) {
        start = '1';
    }

    for (char c = start; c <= '9'; ++c) {
        string tmp = partial;
        tmp.push_back(c);
        alltuples_recur(index + 1, tmp, partialsum + c - '0', tuples, sum,
                        leftcorner);
    }
}

bool check(std::vector<string> square, Trie *trie, const int sum) {
    vector<string> strs(6, "");
    int diagonalsum = 0;
    for (int i = 0; i < square.size(); ++i) {
        for (int j = 0; j < square[i].size(); ++j) {
            strs[j].push_back(square[i][j]);

            if (i == j) {
                strs[5].push_back(square[i][j]);
            }

            if (i + j == 4) {
                diagonalsum += square[i][j] - '0';
                if (diagonalsum > sum) {
                    return false;
                }
            }
        }
    }

    for (int i = 0; i < strs.size(); ++i) {
        if (!search(trie, strs[i])) {
            return false;
        }
    }

    if (square.size() == 5) {
        string diagonal = "";
        for (int i = square.size() - 1; i >= 0; --i) {
            for (int j = 0; j < square[i].size(); ++j) {
                if (i + j == 4) {
                    diagonal.push_back(square[i][j]);
                }
            }
        }
        return search(trie, diagonal);
    }

    return true;
}

void fill_square(vector<vector<string> > &squares, const vector<string> &tuples,
        Trie *trie, const int sum, const int leftcorner) {
    vector<string> square(5, string(5, '0'));
    string tmp(5, '0');
    int N = tuples.size();
    for (int i1 = 0; i1 < N; ++i1) {
        if (tuples[i1][0] - '0' != leftcorner) {
            continue;
        }

        for (int r = 0, i = 0; r < 5; ++r, ++i) {
            square[r][r] = tuples[i1][i];
        }

        for (int i2 = 0; i2 < N; ++i2) {
            if (tuples[i2][2] != square[2][2] || tuples[i2][0] % 2 == 0) {
                continue;
            }
            for (int r = 4, i = 0; r >= 0; --r, ++i) {
                square[r][4 - r] = tuples[i2][i];
            }

            for (int i3 = 0; i3 < N; ++i3) {
                if (!(tuples[i3][1] == square[1][1] &&
                      tuples[i3][3] == square[3][1])) {
                    continue;
                }
                for (int r = 0, i = 0; r < 5; ++r, ++i) {
                    square[r][1] = tuples[i3][i];
                }

                for (int i4 = 0; i4 < N; ++i4) {
                    if (!(tuples[i4][1] == square[1][3] &&
                          tuples[i4][3] == square[3][3])) {
                        continue;
                    }
                    for (int r = 0, i = 0; r < 5; ++r, ++i) {
                        square[r][3] = tuples[i4][i];
                    }

                    square[0][2] = sum + '0' - (square[0][0] - '0') -
                                   (square[0][1] - '0') - (square[0][3] - '0') -
                                   (square[0][4] - '0');

                    if (!(square[0][2] >= '0' && square[0][2] <= '9')) {
                        continue;
                    }

                    if (!search(trie, square[0])) {
                        continue;
                    }

                    square[4][2] = sum + '0' - (square[4][0] - '0') -
                                   (square[4][1] - '0') - (square[4][3] - '0') -
                                   (square[4][4] - '0');

                    if (!(square[4][2] >= '0' && square[4][2] <= '9')) {
                        continue;
                    }

                    if (!search(trie, square[4])) {
                        continue;
                    }

                    for (char c31 = '1'; c31 <= '9'; ++c31) {
                        for (char c35 = '1'; c35 <= '9'; c35 += 2) {
                            square[2][0] = c31;
                            square[2][4] = c35;

                            if (!search(trie, square[2])) {
                                continue;
                            }

                            for (char c21 = '0'; c21 <= '9'; ++c21) {
                                for (char c41 = '0'; c41 <= '9'; ++c41) {
                                    square[1][0] = c21;
                                    square[3][0] = c41;

                                    for (int r = 0; r < 5; ++r) {
                                        tmp[r] = square[r][0];
                                    }

                                    if (!search(trie, tmp)) {
                                        continue;
                                    }

                                    for (char c25 = '0'; c25 <= '9'; ++c25) {
                                        for (char c45 = '0'; c45 <= '9';
                                             ++c45) {
                                            square[1][4] = c25;
                                            square[3][4] = c45;

                                            for (int r = 0; r < 5; ++r) {
                                                tmp[r] = square[r][4];
                                            }

                                            if (!search(trie, tmp)) {
                                                continue;
                                            }

                                            square[1][2] =
                                                    sum + '0' -
                                                    (square[1][0] - '0') -
                                                    (square[1][1] - '0') -
                                                    (square[1][3] - '0') -
                                                    (square[1][4] - '0');

                                            if (!(square[1][2] >= '0' &&
                                                  square[1][2] <= '9')) {
                                                continue;
                                            }

                                            if (!search(trie, square[1])) {
                                                continue;
                                            }

                                            square[3][2] =
                                                    sum + '0' -
                                                    (square[3][0] - '0') -
                                                    (square[3][1] - '0') -
                                                    (square[3][3] - '0') -
                                                    (square[3][4] - '0');

                                            if (!(square[3][2] >= '0' &&
                                                  square[3][2] <= '9')) {
                                                continue;
                                            }

                                            if (!search(trie, square[3])) {
                                                continue;
                                            }

                                            for (int i = 0, r = 0; r < 5;
                                                 ++r, ++i) {
                                                tmp[i] = square[r][2];
                                            }

                                            if (!search(trie, tmp)) {
                                                continue;
                                            }

                                            squares.push_back(square);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void square_recur(vector<vector<string> > &squares, vector<string> square,
        const set<string> &tuples, const set<string> &firstlines, Trie *trie, const int sum) {
    if (square.size() > 1 && square.size() < 4 && !check(square, trie, sum)) {
        return;
    } else if (square.size() == 4) {
        string tmp(5, sum + '0');
        for (int r = 0; r < 4; ++r) {
            for (int c = 0; c < 5; ++c) {
                tmp[c] -= square[r][c] - '0';
            }
        }

        for (int i = 0; i < 5; ++i) {
            if (!(tmp[i] >= '0' && tmp[i] <= '9')) {
                return;
            }
        }

        if (!search(trie, tmp)) {
            return;
        }

        square.push_back(tmp);
        if (check(square, trie, sum)) {
            squares.push_back(square);
        }
        return;
    }

    if (square.empty()) {
        for (auto iter = firstlines.begin();
             iter != firstlines.end(); ++iter) {
            square.push_back(*iter);
            square_recur(squares, square, tuples, firstlines, trie, sum);
            square.pop_back();
        }
    } else {
        for (auto iter = tuples.begin(); iter != tuples.end();
             ++iter) {
            square.push_back(*iter);
            square_recur(squares, square, tuples, firstlines, trie, sum);
            square.pop_back();
        }
    }
}

bool cmp(const vector<string> &square1, const vector<string> &square2) {
    for (int r = 0; r < 5; ++r) {
        if (square1[r] < square2[r]) {
            return true;
        } else if (square1[r] > square2[r]) {
            return false;
        }
    }

    return false;
}

int main() {
    FILE *fin = fopen("prime3.in", "r");
    FILE *fout = fopen("prime3.out", "w");

    int sum, leftcorner;
    fscanf(fin, "%d", &sum);
    fscanf(fin, "%d", &leftcorner);

    std::vector<string> tuples;
    alltuples_recur(0, "", 0, tuples, sum, leftcorner);

    Trie *trie = new Trie();
    for (int i = 0; i < tuples.size(); ++i) {
        insert(trie, tuples[i]);
    }

    vector<vector<string> > squares;
    fill_square(squares, tuples, trie, sum, leftcorner);

    sort(squares.begin(), squares.end(), cmp);

    for (int i = 0; i < squares.size(); ++i) {
        for (int r = 0; r < squares[i].size(); ++r) {
            for (int c = 0; c < squares[i][r].size(); ++c) {
                fprintf(fout, "%c", squares[i][r][c]);
            }
            fprintf(fout, "\n");
        }
        if (i != squares.size() - 1) {
            fprintf(fout, "\n");
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}