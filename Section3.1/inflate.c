/*
ID: lizhita1
LANG: C
TASK: inflate
 */

#include <stdio.h>

#define MAXM 10000
#define max(a,b) ((a)<(b))?b:a

int m, n, v, w, f[MAXM+1];

int main() {
    FILE *fin = fopen("inflate.in", "r");
    fscanf(fin, "%d%d", &m, &n);
    for (int i=0; i<n; ++i) {
        fscanf(fin, "%d%d", &v, &w);
        for (int j=w; j<=m; ++j)
            f[j] = max(f[j], f[j-w]+v);
    }
    fclose(fin);

    int ans = 0;
    for (int i=0; i<=m; ++i)
        ans = max(ans, f[i]);

    FILE *fout = fopen("inflate.out", "w");
    fprintf(fout, "%d\n", ans);
    fclose(fout);
    return 0;
}
