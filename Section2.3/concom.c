/*
ID: lizhita1
LANG: C
TASK: concom
 */

#include <stdio.h>
#include <string.h>

#define MAXNCOM 100

int main() {
    int n, own[MAXNCOM+1][MAXNCOM+1], con[MAXNCOM+1][MAXNCOM+1];
    memset(own, 0, sizeof(own));
    memset(con, 0, sizeof(con));
    FILE *fin = fopen("concom.in", "r");
    fscanf(fin, "%d", &n);
    for (int i=0; i<n; ++i) {
        int x, y, p;
        fscanf(fin, "%d%d%d", &x, &y, &p); 
        own[x][y] = p;
        con[x][y] = (p>50);
    }
    fclose(fin);

    for (int i=1; i<=MAXNCOM; ++i)      
        con[i][i] = 1;

    while (1) {
        int flag = 0;
        for (int i=1; i<=MAXNCOM; ++i) 
            for (int j=1; j<=MAXNCOM; ++j)
                if (con[i][j]==0) {
                    int total = 0;
                    for (int k=1; k<=MAXNCOM; ++k) 
                        if (con[i][k]) 
                            total += own[k][j];
                    if (total>50) {
                        con[i][j] = 1;
                        flag = 1;
                    }
                }
        if (!flag)
            break;
    }

    FILE *fout = fopen("concom.out", "w");
    for (int i=1; i<=MAXNCOM; ++i)
        for (int j=1; j<=MAXNCOM; ++j)
            if (i!=j && con[i][j])
                fprintf(fout, "%d %d\n", i, j);
    fclose(fout);
    return 0;
}
