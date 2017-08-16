/*
ID: lizhita1
LANG: C
TASK: wormhole
*/

#include <stdio.h>
#include <string.h>

#define MAX_N 12
#define MAX_INT 0x7fffffff

int ans = 0;

int canTrap(int n, int pair[], int x[], int y[]) {
    int i, j;
    int in[MAX_N];
    int currentX, currentY;
    for (i=0; i<n; ++i) {
        memset(in, 0, sizeof(int)*MAX_N);
        in[i] = 1;
        currentX = x[pair[i]];
        currentY = y[pair[i]];
        while (1) {
            int minX = MAX_INT, id = -1;
            for (j=0; j<n; ++j)
                if (y[j]==currentY && x[j]>currentX && x[j]<minX) {
                    minX = x[j];
                    id = j;
                }
            if (id==-1)
                break;
            if (in[id])
                return 1;
            in[id] = 1;
            currentX = x[pair[id]];
            currentY = y[pair[id]];
        }
    }
    return 0;
}

void make_pair(int n, int pairedNum, int pair[], int x[], int y[]) {
    int i, holeA;
    if (pairedNum==n/2) {
        if (canTrap(n, pair, x, y))
            ++ans;
        return;
    }
    for (i=0; i<n; ++i)
        if (pair[i]==-1) {
            holeA = i;
            break;
        }
    for (i=0; i<n; ++i)
        if (pair[i]==-1 && i!=holeA) {
            pair[holeA] = i;
            pair[i] = holeA;
            make_pair(n, pairedNum+1, pair, x, y);
            pair[holeA] = pair[i] = -1;
        }
}

int main() {
    int n, i;
    int x[MAX_N], y[MAX_N];
    int pair[MAX_N];

    FILE *fin = fopen("wormhole.in", "r");
    fscanf(fin, "%d", &n);
    for (i=0; i<n; ++i)
        fscanf(fin, "%d%d", &x[i], &y[i]);
    fclose(fin);

    memset(pair, -1, sizeof(int)*MAX_N); 
    make_pair(n, 0, pair, x, y);

    FILE *fout = fopen("wormhole.out", "w");
    fprintf(fout, "%d\n", ans);
    fclose(fout);
    return 0;
}
