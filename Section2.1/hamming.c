/*
ID: lizhita1
LANG: C
TASK: hamming
*/

#include <stdio.h>

#define MAX_N 64
#define MAX_B 8
#define MAX_D 7

int n, b, d;

int calc_dist(int numA, int numB) {
    int xorNum = numA^numB;
    int dist = 0;
    for (int i=0; i<b; ++i)
        if (xorNum & (1<<i))
            ++dist;
    return dist;
}

int main() {
    FILE *fin = fopen("hamming.in", "r");
    fscanf(fin, "%d%d%d", &n, &b, &d);
    fclose(fin);
    
    int ans[MAX_N];
    int count = 1;
    ans[0] = 0;
   
    for (int i=1; i<(1<<b); ++i) {
        int valid = 1;
        for (int j=0; j<count; ++j)
            if (calc_dist(ans[j], i)<d) {
                valid = 0;
                break;
            }
        if (valid)
            ans[count++] = i;
        if (count==n)
            break;
    }

    count = 0;
    FILE *fout = fopen("hamming.out", "w");
    for (int i=0; i<n; ++i) {
        fprintf(fout, "%d", ans[i]);
        ++count;
        if (count==10) {
            fprintf(fout, "\n");
            count = 0;
        }
        else if (i==n-1)
            fprintf(fout, "\n");
        else
            fprintf(fout, " ");
    }
    fclose(fout);
    return 0;
}
