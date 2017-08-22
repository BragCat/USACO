/*
ID: lizhita1
LANG: C
TASK: zerosum
*/

#include <stdio.h>

#define MAXN 9

FILE *fin, *fout;
char ans[MAXN*2];
int n;

void search(int curDigit, int curNumber, int sum, int coe) {
    if (curDigit==n) {
        sum += coe*curNumber;
        if (sum==0) {
            ans[n*2-1] = '\0';
            fprintf(fout, "%s\n", ans);
        }
        return;
    }
    
    int sumSaved = sum;
    ans[curDigit*2-1] = ' ';
    search(curDigit+1, curNumber*10+curDigit+1, sum, coe);

    ans[curDigit*2-1] = '+';
    search(curDigit+1, curDigit+1, sum+coe*curNumber, 1);

    ans[curDigit*2-1] = '-';
    search(curDigit+1, curDigit+1, sum+coe*curNumber, -1);
}

int main() {
    fin = fopen("zerosum.in", "r");
    fscanf(fin, "%d", &n);
    fclose(fin);
    
    for (int i=0; i<n; ++i)
        ans[i*2] = (char)(i+1+'0');

    fout = fopen("zerosum.out", "w");
    search(1, 1, 0, 1); 
    fclose(fout);
    return 0;
} 
