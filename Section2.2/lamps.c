/*
ID: lizhita1
LANG: C
TASK: lamps
*/

#include <stdio.h>
#include <string.h>

#define MAX_N 100

int on[MAX_N], off[MAX_N];
int n, c, ansCount = 0;
int ans[16][MAX_N];

void searchAllState(int c) {
    int state[MAX_N];

    for (int i=0; i<16; ++i) {
        int sw[4];
        int count = 0, t = i;
        for (int j=0; j<4; ++j) {
            sw[j] = t%2;
            t /= 2;
            count += sw[j];
        }
        if (count!=c)
            continue;

        memset(state, 0, sizeof(state));
        if (sw[0])
            for (int j=0; j<n; ++j)
                state[j] = 1-state[j];
        if (sw[1])
            for (int j=0; j<n; j += 2)
                state[j] = 1-state[j];
        if (sw[2])
            for (int j=1; j<n; j += 2)
                state[j] = 1-state[j];
        if (sw[3])
            for (int j=0; j<n; j += 3)
                state[j] = 1-state[j];
        int valid = 1;
        for (int j=0; j<n; ++j)
            if ((on[j]==1 && state[j]==1) || (off[j]==1 && state[j]==0)) {
                valid = 0;
                break;
            }
        if (valid) {
            for (int j=0; j<n; ++j) 
                ans[ansCount][j] = 1-state[j];
            ++ansCount;
        }
    }
}

int less(int p, int q) {
    for (int i=0; i<n; ++i)
        if (ans[p][i]<ans[q][i])
            return 1;
        else if (ans[p][i]>ans[q][i])
            return 0;
    return 0;        
}

void swap(int p, int q) {
    for (int i=0; i<n; ++i)
        if (ans[p][i]!=ans[q][i]) {
            int t = ans[p][i];
            ans[p][i] = ans[q][i];
            ans[q][i] = t; 
        }
}

int main() {
    memset(on, 0, sizeof(on));
    memset(off, 0, sizeof(off));
 
    int lampInd;
    FILE *fin = fopen("lamps.in", "r"); 
    fscanf(fin, "%d%d", &n, &c);
    fscanf(fin, "%d", &lampInd);
    while (lampInd!=-1) {
        on[lampInd-1] = 1;
        fscanf(fin, "%d", &lampInd);
    }
    fscanf(fin, "%d", &lampInd);
    while (lampInd!=-1) {
        off[lampInd-1] = 1;
        fscanf(fin, "%d", &lampInd);
    }
    fclose(fin);

    if (c>4)
        if (c%2==0)
            c = 4;
        else 
            c = 3;

    switch (c) {
        case 0: searchAllState(0); break;
        case 1: searchAllState(1); break;
        case 2: searchAllState(0); searchAllState(2); break;
        case 3: searchAllState(1); searchAllState(3); break;
        case 4: searchAllState(0); searchAllState(2); searchAllState(4); break;
    }

    for (int i=0; i<ansCount; ++i)
        for (int j=i+1; j<ansCount; ++j)
            if (less(j, i))
                swap(i, j);

    FILE *fout = fopen("lamps.out", "w");
    if (!ansCount)
        fprintf(fout, "IMPOSSIBLE\n");
    else
        for (int i=0; i<ansCount; ++i) {
            for (int j=0; j<n; ++j) 
                fprintf(fout, "%d", ans[i][j]);
            fprintf(fout, "\n");
        } 
    fclose(fout);

    return 0;
}


