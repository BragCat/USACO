/*
ID: lizhita1
LANG: C
TASK: pprime
*/

#include <stdio.h>
#include <string.h>

#define SUP 10001
#define MAX_N 100000

int notPrime[SUP], primes[SUP];
int primeNum = 0;
int answers[SUP];
int ansNum = 0;

void calc_primes() {
    notPrime[1] = 1;
    for (int i=2; i<=100; ++i)
        if (notPrime[i]==0) {
            int j = i+i;
            while (j<SUP) {
                notPrime[j] = 1;
                j += i;
            }
        }
    for (int i=2; i<SUP; ++i)
        if (notPrime[i]==0)
            primes[primeNum++] = i;
} 

int generate_number(int len, int number[], int delta) {
    int ans = 0;
    for (int i=0; i<len; ++i)
        ans = ans*10+number[i];
    for (int i=len-1-delta; i>=0; --i)
        ans = ans*10+number[i];
    return ans;
}

int is_prime(int number) {
    if (number<SUP)
        return !notPrime[number];
    for (int i=0; i<primeNum; ++i)
        if (number%primes[i]==0)
            return 0;
    return 1;
}

void dfs(int len, int number[], int lena, int a, int lenb, int b) {
    int step, start;
    if (len*2-1>lenb) 
        return;
    if (len*2-1>=lena) {
        int result = generate_number(len, number, 1);
        // printf("%d\n", result);
        if (result>=a && result<=b && is_prime(result))
            answers[ansNum++] = result;
    }
    if (len*2>=lena && len*2<=lenb) {
        int result = generate_number(len, number, 0);
        // printf("%d\n", result);
        if (result>=a && result<=b && is_prime(result))
            answers[ansNum++] =result;
    }
    step = (len==0)?2:1;
    start = (len==0)?1:0;
    for (int i=start; i<=9; i+=step) {
        number[len] = i;
        dfs(len+1, number, lena, a, lenb, b);
    }
}

void sort(int array[], int l, int r) {
    int mid = l+(r-l)/2;
    int cmp = array[mid];
    int i=l, j=r;
    while (i<=j) {
        while (array[i]<cmp) ++i;
        while (array[j]>cmp) --j;
        if (i<=j) {
            int t = array[i];
            array[i] = array[j];
            array[j] = t;
            ++i;
            --j;
        }
    }
    if (j>l)
        sort(array, l, j);
    if (i<r)
        sort(array, i, r);
}

int main() {
    int a, b, lena, lenb, ta, tb;
    int number[10];

    FILE *fin = fopen("pprime.in", "r");
    fscanf(fin, "%d%d", &a, &b);
    fclose(fin);

    lena = 0;
    ta = a;
    while (ta>0) {
        ++lena;
        ta /= 10;
    }
    lenb = 0;
    tb = b;
    while (tb>0) {
        ++lenb;
        tb /= 10;
    }

    // printf("%d %d\n", lena, lenb);

    memset(notPrime, 0, sizeof(int)*SUP);
    calc_primes();
//    for (int i=0; i<primeNum; ++i)
//        printf("%d\n", primes[i]);

    dfs(0, number, lena, a, lenb, b);
    sort(answers, 0, ansNum-1);

    FILE *fout = fopen("pprime.out", "w");
    for (int i=0; i<ansNum; ++i)
        fprintf(fout, "%d\n", answers[i]);
    fclose(fout);
    return 0;
}
