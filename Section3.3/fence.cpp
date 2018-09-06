/*
 ID: bragcat1
 LANG: C++11
 TASK: fence
 */

#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define N 500

#define min(a,b) ((a)<(b))?(a):(b)

vector<int> answer;

void ride(int degrees[], int paths[][N], int node) {
    for (int i = 0; i < N; ++i) {
        if (paths[node][i] > 0) {
            --degrees[node];
            --degrees[i];
            --paths[node][i];
            --paths[i][node];
            ride(degrees, paths, i);
        }
    }
    answer.push_back(node);
}

int main(void) {
    int minNode = N + 1;
    int degrees[N];
    int paths[N][N];
    memset(degrees, 0, sizeof(degrees));
    memset(paths, 0, sizeof(paths));
    int fenceNumber;

    FILE *fin = fopen("fence.in", "r");
    if (fin == NULL) {
        printf("open file failed.\n");
        return 0;
    }
    fscanf(fin, "%d", &fenceNumber);
    for (int i = 0; i < fenceNumber; ++i) {
        int x, y;
        fscanf(fin, "%d%d", &x, &y);
        ++degrees[x - 1];
        ++degrees[y - 1];
        ++paths[x - 1][y - 1];
        ++paths[y - 1][x - 1];
        minNode = min(minNode, min(x - 1, y - 1));
    }
    fclose(fin);

    int stNode = -1;
    for (int i = 0; i < N; ++i) {
        if (degrees[i] % 2 != 0) {
            stNode = i;
            break;
        }
    }
    if (stNode == -1) {
        stNode = minNode;
    }

    ride(degrees, paths, stNode);
    FILE *fout = fopen("fence.out", "w");
    while (!answer.empty()) {
        fprintf(fout, "%d\n", answer.back() + 1);
        answer.pop_back();
    }
    fclose(fout);

    return 0;
}
