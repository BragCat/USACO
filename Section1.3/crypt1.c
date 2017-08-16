/*
ID: lizhita1
LANG: C
TASK: crypt1
*/

#include <stdio.h>

const int MAX_N = 9;
int ans = 0;

int checkDigit(int number, int n, int digits[]) {
    int i;
    while (number>0) {
        int digit = number%10;
        int exist = 0;
        for (i=0; i<n; ++i)
            if (digits[i]==digit) {
                exist = 1;
                break;
            }
        if (!exist)
            return 0;
        number /= 10;
    }
    return 1;
}

int isValid(int number[], int n, int digits[]) {
    int numA = number[0]*100+number[1]*10+number[2];
    int first = numA*number[4], second = numA*number[3], result = second*10+first;
    if (first>=1000 || second>=1000)
        return 0;
    if (!checkDigit(first, n, digits) || !checkDigit(second, n, digits))
        return 0;
    if (!checkDigit(result, n, digits)) 
        return 0;
    return 1;
}

void dfs(int pos, int number[], int n, int digits[]) {
    int i;
    if (pos==5) {
        if (isValid(number, n, digits))
            ++ans;
        return;
    }

    for (i=0; i<n; ++i) {
        number[pos] = digits[i];
        dfs(pos+1, number, n, digits);
    }
}

int main() {
    int n, i;
    int digits[MAX_N];
    int number[5];

    FILE *fin = fopen("crypt1.in", "r");
    fscanf(fin, "%d", &n);
    for (i=0; i<n; ++i)
        fscanf(fin, "%d", &digits[i]);
    fclose(fin);
    
    dfs(0, number, n, digits);
    
    FILE *fout = fopen("crypt1.out", "w");
    fprintf(fout, "%d\n", ans);
    fclose(fout);

    return 0;
}
