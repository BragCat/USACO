/*
ID: lizhita1
LANG: C
TASK: stamps
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXK 200
#define MAXN 50
#define MAXV 10000

#define max(a,b) ((a)>(b))?(a):(b)
#define min(a,b) ((a)<(b))?(a):(b)

int n, k;
int needs[MAXK*MAXV+1];

int main() {
    memset(needs, -1, sizeof(needs));
    needs[0] = 0;
    int maxV = 0, v;

    FILE *fin = fopen("stamps.in", "r");
    fscanf(fin, "%d%d", &k, &n);
    for (int i=0; i<n; ++i) {
        fscanf(fin, "%d", &v); 
        maxV = max(maxV, v);
        for (int j=v; j<=k*maxV; ++j)
            if (needs[j-v]!=-1) 
                if (needs[j]==-1)
                    needs[j] = needs[j-v]+1;
                else
                    needs[j] = min(needs[j], needs[j-v]+1);
    }
    fclose(fin);

    FILE *fout = fopen("stamps.out", "w");
    int ans = 0;
    for (int i=1; i<=k*maxV; ++i)
        if (needs[i]!=-1 && needs[i]<=k)
            ans = i;
        else
            break;
    fprintf(fout, "%d\n", ans);
    fclose(fout);

    exit(0);
}
