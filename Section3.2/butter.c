/*
 ID: bragcat1
 LANG: C
 TASK: butter
 */

#include <stdio.h>
#include <memory.h>
#include <stdbool.h>

#define MAXN 500
#define MAXP 800
#define MAXC 1450
#define MAX_INT 0x7fffffff

#define min(a,b) ((a)<(b))?(a):(b)

int N, P, C;

void calcShortestPath(int dist[][MAXP], int paths[][3], int srcNode) {
    for (int i = 0; i < P; ++i) {
        dist[srcNode][i] = MAX_INT;
    }
    dist[srcNode][srcNode] = 0;
    bool relaxed = true;
    while (relaxed) {
        relaxed = false;
        for (int i = 0; i < C; ++i) {
            int x = paths[i][0], y = paths[i][1], d = paths[i][2];
            if (dist[srcNode][x] != MAX_INT && dist[srcNode][x] + d < dist[srcNode][y]) {
                dist[srcNode][y] = dist[srcNode][x] + d;
                relaxed = true;
            }
            if (dist[srcNode][y] != MAX_INT && dist[srcNode][y] + d < dist[srcNode][x]) {
                dist[srcNode][x] = dist[srcNode][y] + d;
                relaxed = true;
            }
        }
    }
}

int main() {
    int cowNumbers[MAXP];
    memset(cowNumbers, 0, sizeof(cowNumbers));
    int dist[MAXP][MAXP];
    int paths[MAXC][3];
    FILE *fin = fopen("butter.in", "r");
    fscanf(fin, "%d%d%d", &N, &P, &C);
    for (int i = 0; i < N; ++i) {
        int x;
        fscanf(fin, "%d", &x);
        ++cowNumbers[x - 1];
    }
    for (int i = 0; i < C; ++i) {
        fscanf(fin, "%d%d%d", &paths[i][0], &paths[i][1], &paths[i][2]);
        --paths[i][0];
        --paths[i][1];
    }
    fclose(fin);

    for (int i = 0; i < P; ++i) {
        // use bellman-ford algorithm to calculate shortest path for node i
        calcShortestPath(dist, paths, i);
    }

    int answer = MAX_INT;
    for (int i = 0; i < P; ++i) {
        int curDist = 0;
        for (int j = 0; j < P; ++j) {
            curDist += dist[i][j] * cowNumbers[j];
        }
        answer = min(answer, curDist);
    }

    FILE *fout = fopen("butter.out", "w");
    fprintf(fout, "%d\n", answer);
    fclose(fout);

    return 0;
}
