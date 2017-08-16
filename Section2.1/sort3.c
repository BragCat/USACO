/*
ID: lizhita1
LANG: C
TASK: sort3
*/

#include <stdio.h>
#include <string.h>

#define MAX_N 1000
#define min(a,b) ((a<b)?a:b)

int n;
int num[MAX_N];
int place[3][3];

int main() {
    FILE *fin = fopen("sort3.in", "r");
    fscanf(fin, "%d", &n);
    for (int i=0; i<n; ++i)
        fscanf(fin, "%d", &num[i]);
    fclose(fin);

    int oneCount = 0, twoCount = 0, threeCount = 0;
    for (int i=0; i<n; ++i)
        switch (num[i]) {
            case 1: ++oneCount; break;
            case 2: ++twoCount; break;
            case 3: ++threeCount;
        }
    
    memset(place, 0, sizeof(place));
    int segment = 0;
    for (int i=0; i<n; ++i) {
        if (i+1>oneCount+twoCount)
            segment = 2;
        else if (i+1>oneCount)
            segment = 1;
        ++place[num[i]-1][segment];
    }
    
    int ans = 0;
    for (int i=0; i<2; ++i)
        for (int j=i+1; j<3; ++j) {
            int t = min(place[i][j], place[j][i]);
            ans += t;
            place[i][j] -= t;
            place[j][i] -= t;
            place[i][i] += t;
            place[j][j] += t;
        }

    int flag = 1;
    for (int i=0; i<2; ++i) {
        for (int j=i+1; j<3; ++j)
            if (place[i][j]!=0) {
                ans += 2*place[i][j];
                flag = 0;
                break;
             }
        if (!flag)
            break;
    }
    
    FILE *fout = fopen("sort3.out", "w");
    fprintf(fout, "%d\n", ans);
    fclose(fout);
    return 0;
}
