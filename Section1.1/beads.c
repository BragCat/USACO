/*
ID: lizhita1
LANG: C
PROG: beads
*/

#include <stdio.h>

int main() {
    const int MAX_N = 350;
    
    int n, ans = 0;
    char beads[MAX_N];
    int i;
    
    FILE *fin = fopen("beads.in", "r");
    FILE *fout = fopen("beads.out", "w");

    fscanf(fin, "%d", &n);
    getc(fin);
    for (i=0; i<n; ++i)
        beads[i] = getc(fin);

    for (i=0; i<n; ++i) {
        int leftCount = 1, rightCount = 1;
        int leftPos = i, rightPos = (i+1)%n;
        char leftColor = beads[leftPos], rightColor = beads[rightPos];
        
        while (leftPos!=rightPos) {
            int nextPos = leftPos-1;
            if (nextPos<0)
                nextPos = n-1;
            if (nextPos==rightPos)
                break;
            if (beads[nextPos]==leftColor || leftColor=='w' || beads[nextPos]=='w') {
                ++leftCount;
                if (leftColor=='w')
                    leftColor = beads[nextPos];
                leftPos = nextPos;
            }
            else 
                break;
        }
        
        while (leftPos!=rightPos) {
            int nextPos = (rightPos+1)%n;
            if (nextPos==leftPos)
                break;
            if (beads[nextPos]==rightColor || rightColor=='w' || beads[nextPos]=='w') {
                ++rightCount;
                if (rightColor=='w')
                    rightColor = beads[nextPos];
                rightPos = nextPos;
            } 
            else 
                break;
        }
        
        if (leftCount+rightCount>ans)
            ans = leftCount+rightCount;
    }

    fprintf(fout, "%d\n", ans);

    fclose(fin);
    fclose(fout);

    return 0;
}
