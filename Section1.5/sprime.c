/*
ID: lizhita1
LANG: C
TASK: sprime
*/

#include <stdio.h>
#include <string.h>

#define SUP 10001
#define MAX_N 8

int notPrime[SUP];
int primes[SUP];
int primeNum = 0;

void calc_primes() {
    memset(notPrime, 0, sizeof(0)*SUP);
    notPrime[0] = notPrime[1] = 1;
    for (int i=2; i<100; ++i)
        if (!notPrime[i]) {
            int j=i+i;
            while (j<SUP) {
                notPrime[j] = 1;
                j += i;
            }
        }
    for (int i=0; i<SUP; ++i)
        if (!notPrime[i])
            primes[primeNum++] = i;
}

int is_prime(int number) {
    if (number<SUP)
        return !notPrime[number];
    for (int i=0; i<primeNum; ++i)
        if (number%primes[i]==0)
            return 0;
    return 1;
}

void dfs(FILE *fout, int len, int number, int n) {
    int start;
    if (len==n) {
        fprintf(fout, "%d\n", number);
        return;
    }
    start = (len==0)?1:0;
    for (int i=start; i<=9; ++i)
        if (is_prime(number*10+i))
            dfs(fout, len+1, number*10+i, n);
}

int main() {
    int n;

    FILE *fin = fopen("sprime.in", "r");
    fscanf(fin, "%d", &n);
    fclose(fin);

    calc_primes();

    FILE *fout = fopen("sprime.out", "w");
    dfs(fout, 0, 0, n);
    fclose(fout);

    return 0;
}
