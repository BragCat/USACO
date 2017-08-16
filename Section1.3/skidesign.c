/*
ID: lizhita1
LANG: C
TASK: skidesign
*/

#include <stdio.h>

#define MAX_N 1000
#define MAX_HEIGHT 100
#define MAX_INT 0x7fffffff

int main() {
    int n, ans;
    int height[MAX_N];

    FILE *fin = fopen("skidesign.in", "r");
    fscanf(fin, "%d", &n);
    for (int i=0; i<n; ++i)
        fscanf(fin, "%d", &height[i]);

    ans = MAX_INT;
    for (int i=0; i<=MAX_HEIGHT-17; ++i) {
        int cost = 0;
        for (int j=0; j<n; ++j)
            if (height[j]<i)
                cost += (i-height[j])*(i-height[j]);
            else if (height[j]>i+17)
                cost += (height[j]-i-17)*(height[j]-i-17);
        if (cost<ans)
            ans = cost;
    }

    FILE *fout = fopen("skidesign.out", "w");
    fprintf(fout, "%d\n", ans);
    fclose(fout);
    return 0;
}
