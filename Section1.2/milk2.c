/*
ID: lizhita1
LANG: C
PROG: milk2
 */

#include <stdio.h>

struct Internal {
    int start;
    int end;
};

void sort(struct Internal *left, struct Internal *right) {
    struct Internal *mid = left+(right-left)/2;
    int flagSt = mid->start, flagEd = mid->end;
    struct Internal *i = left, *j = right;
    while (i<=j) {
        while (i->start<flagSt || (i->start==flagSt && i->end<flagEd)) ++i;
        while (j->start>flagSt || (j->start==flagSt && j->end>flagEd)) --j;
        if (i<=j) {
            struct Internal temp = *i;
            *i = *j;
            *j = temp;
            ++i;
            --j;
        }
    }
    if (j>left)
        sort(left, j);
    if (i<right)
        sort(i, right);
}

int main() {
    const int MAX_N = 5000;

    int ansOne = 0, ansNone = 0;
    int n, start, end, i;
    struct Internal durations[MAX_N];

    FILE *fin = fopen("milk2.in", "r");
    FILE *fout = fopen("milk2.out", "w");

    fscanf(fin, "%d", &n);
    for (i=0; i<n; ++i)
        fscanf(fin, "%d%d", &durations[i].start, &durations[i].end);

    sort(durations, durations+n-1);

    start = durations[0].start, end = durations[0].end;
    ansOne = end-start;
    for (i=1; i<n; ++i) {
        if (end<durations[i].start) {
            if (durations[i].start-end>ansNone)
                ansNone = durations[i].start-end;
            start = durations[i].start;
            end = durations[i].end;
        }
        else {
            if (durations[i].end>end)
                end = durations[i].end;
        }
        if (end-start>ansOne)
            ansOne = end-start;
    }

    fprintf(fout, "%d %d\n", ansOne, ansNone);
    
    fclose(fin);
    fclose(fout);
    return 0;
}
