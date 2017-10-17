/*
ID: lizhita1
LANG: C
TASK: agrinet
 */

#include <stdio.h>

#define MAXN 100

int dist[MAXN], path[MAXN][MAXN], inTree[MAXN];
int n, ans;

int main() {
    FILE *fin = fopen("agrinet.in", "r");
    fscanf(fin, "%d", &n);
    for (int i=0; i<n; ++i)
        for (int j=0; j<n; ++j)
            fscanf(fin, "%d", &path[i][j]);
    fclose(fin);

    for (int i=1; i<n; ++i) {
        dist[i] = path[0][i];
        inTree[i] = 0;
    }
    dist[0] = 0;
    inTree[0] = 1;
    ans = 0;
    
    for (int i=0; i<n-1; ++i) {
        int closest = -1;
        for (int j=0; j<n; ++j) 
            if (!inTree[j] && (closest==-1 || dist[j]<dist[closest])) 
                closest = j;
        ans += dist[closest];
        inTree[closest] = 1;
        for (int j=0; j<n; ++j)
            if (!inTree[j] && path[closest][j]<dist[j])
                dist[j] = path[closest][j];
    }

    FILE *fout = fopen("agrinet.out", "w");
    fprintf(fout, "%d\n", ans);
    fclose(fout);
    return 0;
}
