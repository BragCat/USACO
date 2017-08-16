/*
ID: lizhita1
LANG: C
TASK: milk
*/

#include <stdio.h>

const int MAX_N = 5000;

void sort(int price[], int amount[], int left, int right) {
    int mid = left+(right-left)/2;
    int cmpPrice = price[mid];
    int i = left, j = right;
    while (i<=j) {
        while (price[i]<cmpPrice) ++i;
        while (price[j]>cmpPrice) --j;
        if (i<=j) {
            int t = price[i];
            price[i] = price[j];
            price[j] = t;
            t = amount[i];
            amount[i] = amount[j];
            amount[j] = t;
            ++i;
            --j;
        }
    }
    if (j>left)
        sort(price, amount, left, j);
    if (i<right)
        sort(price, amount, i, right);
}

int main() {
    int m, n, i, ans, num;
    int price[MAX_N], amount[MAX_N];

    FILE *fin = fopen("milk.in", "r");
    fscanf(fin, "%d%d", &m, &n);
    for (i=0; i<n; ++i)
        fscanf(fin, "%d%d", &price[i], &amount[i]);
    fclose(fin);

    sort(price, amount, 0, n-1);

    ans = 0;
    num = 0;
    while (m>0) {
        if (m<=amount[num]) {
            ans += m*price[num];
            m = 0;
        }
        else {
            ans += amount[num]*price[num];
            m -= amount[num];
        }
        ++num;
    }

    FILE *fout = fopen("milk.out", "w");
    fprintf(fout, "%d\n", ans);
    fclose(fout);

    return 0;
}
