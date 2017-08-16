/*
ID: lizhita1
LANG: C
TASK: numtri
*/

#include <stdio.h>

#define MAX_ROW 1000
#define max(a,b) ((a>b)?a:b)

int main() {
    int row, ans;
    int triangle[MAX_ROW][MAX_ROW];

    FILE *fin = fopen("numtri.in", "r");
    fscanf(fin, "%d", &row);
    for (int i=0; i<row; ++i)
        for (int j=0; j<=i; ++j)
            fscanf(fin, "%d", &triangle[i][j]);
    fclose(fin);

    for (int i=1; i<row; ++i)
        for (int j=0; j<=i; ++j)
            if (j==0)
                triangle[i][j] += triangle[i-1][j];
            else
                triangle[i][j] += max(triangle[i-1][j-1], triangle[i-1][j]);

    ans = 0;
    for (int j=0; j<row; ++j)
        ans = max(ans, triangle[row-1][j]);

    FILE *fout = fopen("numtri.out", "w");
    fprintf(fout, "%d\n", ans);
    fclose(fout);

    return 0;
}
