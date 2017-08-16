/*
ID: lizhita1
LANG: C
TASK: combo
*/

#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define min(a,b) ((a<b)?a:b)

int calc_over(int n, int a, int b) {
    if (n<=5)
        return n;
    int flag[MAX_N+1];
    int i, ans = 0;

    memset(flag, 0, sizeof(int)*(MAX_N+1));
    for (i=a-2; i<=a+2; ++i) {
        int pos = i;
        if (pos<=0) 
            pos += n;
        if (pos>n)
            pos -= n;
        flag[pos] = 1;
    }
    for (i=b-2; i<=b+2; ++i){
        int pos = i;
        if (pos<=0)
            pos += n;
        if (pos>n)
            pos -= n;
        if (flag[pos]==1)
            ++ans;
    }
    return ans;
}

int main() {
    int n, ans, i, overlap;
    int john[3], master[3];

    FILE *fin = fopen("combo.in", "r");
    fscanf(fin, "%d", &n);
    for (i=0; i<3; ++i)
        fscanf(fin, "%d", &john[i]);
    for (i=0; i<3; ++i)
        fscanf(fin, "%d", &master[i]);
    fclose(fin);

    ans = 2*min(5, n)*min(5, n)*min(5, n);
    overlap = 1;
    for (i=0; i<3; ++i)
        overlap *= calc_over(n, john[i], master[i]);
    ans -= overlap;
    
    FILE *fout = fopen("combo.out", "w");
    fprintf(fout, "%d\n", ans);
    fclose(fout);
    return 0;
}
