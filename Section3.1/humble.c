/*
ID: lizhita1
LANG: C
TASK: humble
 */

#include <stdio.h>

#define INF 0x7fffffff
#define MAXK 100
#define MAXN 100000
#define min(a,b) ((a)<(b))?(a):(b)

int ans[MAXN+1];
int ind[MAXK+1];
int prime[MAXK+1];
int k, n;

int main() {
    FILE *fin = fopen("humble.in", "r");
    fscanf(fin, "%d%d", &k, &n);
    for (int i=1; i<=k; ++i)
        fscanf(fin, "%d", &prime[i]);
    fclose(fin);
    
    ans[0] = prime[0] = 1;
    for (int i=1; i<=k; ++i)
        ind[i] = 0;
    for (int i=1; i<=n; ++i) {
        int nextAns = INF;
        for (int j=1; j<=k; ++j) {
            while (prime[j]*ans[ind[j]]<=ans[i-1]) 
                ++ind[j];
            nextAns = min(nextAns, prime[j]*ans[ind[j]]);
        }
        ans[i] = nextAns;
    }

    FILE *fout = fopen("humble.out", "w");
    fprintf(fout, "%d\n", ans[n]);
    fclose(fout);

    return 0;
}
