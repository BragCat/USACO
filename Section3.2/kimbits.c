/*
ID: bragcat1
LANG: C
TASK: kimbits
*/

#include <stdio.h>

const int MAXN = 31;

double CalcCombinationNumber(int n, int k) {
    double answer = 1;
    for (int i = n; i > n - k; --i) {
        answer *= i;
    }
    for (int i = k; i > 0; --i) {
        answer /= i;
    }
    return answer;
}

int main(void) {
    int N, L;
    double I;

    FILE *fin = fopen("kimbits.in", "r");
    fscanf(fin, "%d%d%lf", &N, &L, &I);
    fclose(fin);

    char answer[MAXN];
    for (int i = 0; i < N; ++i) {
        double count = 0;
        for (int j = 0; j <= L; ++j) {
            count += CalcCombinationNumber(N - i - 1, j);
        }
        if (count >= I) {
            answer[i] = '0';
        }
        else {
            answer[i] = '1';
            I -= count;
            --L;
        }
    }

    FILE *fout = fopen("kimbits.out", "w");
    for (int i = 0; i < N; ++i) {
        fprintf(fout, "%c", answer[i]);
    }
    fprintf(fout, "\n");
    fclose(fout);

    return 0;
}