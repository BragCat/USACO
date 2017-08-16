/*
ID: lizhita1
LANG: C
TASK: milk3
*/

#include <stdio.h>
#include <string.h>

#define MAX_CAP 21

struct Status {
    int A, B, C;
};

void pour(int capA, int capB, int capC, int curA, int curB, int curC, int *nextA, int *nextB, int *nextC) {
    *nextA = curA, *nextB = curB, *nextC = curC;
    if (*nextA==0)
        return;
    if (*nextB==capB)
        return;
    if (*nextA<capB-(*nextB)) {
        *nextB += *nextA;
        *nextA = 0;
    }
    else {
        *nextA -= capB-*nextB;
        *nextB = capB;
    }
}

void addQue(int searched[][MAX_CAP][MAX_CAP], struct Status que[], int *qTail, int nextA, int nextB, int nextC) {
     if (!searched[nextA][nextB][nextC]) {
        ++(*qTail);
        que[*qTail].A = nextA;
        que[*qTail].B = nextB;
        que[*qTail].C = nextC;
        searched[nextA][nextB][nextC] = 1;
        //printf("%d %d %d\n", nextA, nextB, nextC);
     }
}
int main() {
    int capA, capB, capC;
    int qHead, qTail; 
    int searched[MAX_CAP][MAX_CAP][MAX_CAP];
    struct Status que[MAX_CAP*MAX_CAP*MAX_CAP];     
    int ans[MAX_CAP];
    
    FILE *fin = fopen("milk3.in", "r");
    fscanf(fin, "%d%d%d", &capA, &capB, &capC);
    fclose(fin);
    
    memset(ans, 0, sizeof(int)*MAX_CAP);
    memset(searched, 0, sizeof(int)*MAX_CAP*MAX_CAP*MAX_CAP);
    searched[0][0][capC] = 1;
    que[0].A = que[0].B = 0, que[0].C = capC;
    qHead = qTail = 0;
    while (qHead<=qTail) {
        int curA = que[qHead].A, curB = que[qHead].B, curC = que[qHead].C;
        if (curA==0)
            ans[curC] = 1;
        int nextA, nextB, nextC;
        ++qHead;
        pour(capA, capB, capC, curA, curB, curC, &nextA, &nextB, &nextC);
        addQue(searched, que, &qTail, nextA, nextB, nextC);
        pour(capA, capC, capB, curA, curC, curB, &nextA, &nextC, &nextB);
        addQue(searched, que, &qTail, nextA, nextB, nextC);
        pour(capB, capA, capC, curB, curA, curC, &nextB, &nextA, &nextC);
        addQue(searched, que, &qTail, nextA, nextB, nextC);
        pour(capB, capC, capA, curB, curC, curA, &nextB, &nextC, &nextA);
        addQue(searched, que, &qTail, nextA, nextB, nextC);
        pour(capC, capA, capB, curC, curA, curB, &nextC, &nextA, &nextB);
        addQue(searched, que, &qTail, nextA, nextB, nextC);
        pour(capC, capB, capA, curC, curB, curA, &nextC, &nextB, &nextA);
        addQue(searched, que, &qTail, nextA, nextB, nextC);
    } 

    int first = 1;
    FILE *fout = fopen("milk3.out", "w");
    for (int i=0; i<=capC; ++i)
        if (ans[i]) {
            if (!first)
                fprintf(fout, " ");
            else
                first = 0;
            fprintf(fout, "%d", i);
        }
    fprintf(fout, "\n");
    fclose(fout);

    return 0;
}
