/*
ID: lizhita1
LANG: C
TASK: money
*/

#include <stdio.h>
#include <string.h>

#define MAXV 25
#define MAXN 10000 

int main() {
    int v, n, coins[MAXV + 1];
    FILE *fin = fopen("money.in", "r");
    fscanf(fin, "%d%d", &v, &n);
    for (int i = 1; i <= v; ++i)
        fscanf(fin, "%d", coins + i);
    fclose(fin);

    long long f[MAXV + 1][MAXN + 1];
    memset(f, 0, sizeof(f));
    f[0][0] = 1;
    for (int i = 1; i <= v; ++i) {
        for (int j = 0; j <= n; ++j) {
            f[i][j] = f[i - 1][j];
            if (j >= coins[i]) {
                f[i][j] += f[i][j - coins[i]]; 
            }
        }
    }
    
    FILE *fout = fopen("money.out", "w");
    fprintf(fout, "%lld\n", f[v][n]);
    fclose(fout);
    return 0;
}
