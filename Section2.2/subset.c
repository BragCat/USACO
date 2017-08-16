/*
ID: lizhita1
LANG: C
TASK: subset
*/

#include <stdio.h>
#include <string.h>

#define MAX_N 40
#define min(a,b) ((a<b)?a:b)

int n, ans;
int f[MAX_N][MAX_N*MAX_N/2];

int searchSubset(int remSum, int start) {
    if (start>n) 
        return (remSum==0)?1:0;
    if (f[start][remSum]!=-1) 
        return f[start][remSum];
    if (remSum==0) {
        f[start][remSum] = 1;
        return 1;
    }

    f[start][remSum] = 0;
    if (start>remSum)  
        return 0;

    for (int i=start; i<=min(remSum, n); ++i) 
        f[start][remSum] += searchSubset(remSum-i, i+1); 

    return f[start][remSum];
}

int main() {
    FILE *fin = fopen("subset.in", "r");
    fscanf(fin, "%d", &n);
    fclose(fin);

    memset(f, -1, sizeof(f));
    int sum = n*(1+n)/2;
    if (sum%2)
        ans = 0;
    else
        ans = searchSubset(sum/2-1, 2);

    FILE *fout = fopen("subset.out", "w");
    fprintf(fout, "%d\n", ans);
    fclose(fout);

    return 0;
}
