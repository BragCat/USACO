/*
ID: lizhita1
LANG: C
TASK: runround
*/

#include <stdio.h>
#include <string.h>
#include <math.h>

unsigned int m;
int ans[10], mDigit[10], used[10];
int mLen;

int checkAns(int totLen) {
    int curIndex = totLen-1;
    int count = 1;
    int runed[10];
    memset(runed, 0, sizeof(runed));
    runed[curIndex] = 1;
    while (count<totLen) {
        curIndex = (curIndex-ans[curIndex])%totLen; 
        curIndex = (curIndex+totLen)%totLen;
        if (runed[curIndex])
            return 0;
        else
            runed[curIndex] = 1;
        ++count;
    }
    curIndex = (curIndex-ans[curIndex])%totLen;
    curIndex = (curIndex+totLen)%totLen;
    return curIndex==totLen-1;
}

int search(int totLen, int curIndex, int sign) {
    if (curIndex==-1) 
        return (sign)?0:checkAns(totLen);

    int start;
    if (sign)
        start = mDigit[curIndex];
    else
        start = 1;
    for (int i=start; i<=9; ++i)
        if (used[i]==0) {
            ans[curIndex] = i;
            used[i] = 1;
            if (totLen==mLen && sign && i==start) {
                if (search(totLen, curIndex-1, 1))
                    return 1;
            }
            else 
                if (search(totLen, curIndex-1, 0))
                    return 1;
            used[i] = 0;
        } 
    return 0;
}

int main() {
    FILE *fin = fopen("runround.in", "r");   
    fscanf(fin, "%u", &m);
    fclose(fin);

    memset(ans, 0, sizeof(ans)); 
    int len = 0;
    unsigned int t = m;
    while (t>0) {
        mDigit[len++] = t%10;
        t /= 10;
    }
    mLen = len;
    memset(used, 0, sizeof(used));
    while (1) {
        int result = search(len, len-1, len==mLen); 
        if (result) {
            FILE *fout = fopen("runround.out", "w");
            for (int i=len-1; i>=0; --i) 
                fprintf(fout, "%d", ans[i]);    
            fprintf(fout, "\n");
            fclose(fout);
            break;
        }
        ++len;
    }

    return 0;
}
