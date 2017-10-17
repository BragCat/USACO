/*
ID: lizhita1
LANG: C
TASK: contact
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

#define MINLEN 1
#define MAXLEN 12
#define MAXN 50
#define MAXL 200000
#define MAXMAP 8192

int len, lena, lenb, n;
char seq[MAXL];
int count[MAXMAP], next[MAXMAP], prev[MAXL], first[MAXL];
char ans[MAXLEN+1];

void initialize() {
    memset(count, 0, sizeof(count));
    memset(next, -1, sizeof(next));
    memset(prev, -1, sizeof(prev));
    memset(first, -1, sizeof(first));
}

int mapToNumber(int start, int end) {
    int len = end-start;
    int res = pow(2, len)-2;
    int base = 1;
    for (int i=end-1; i>=start; --i) {
        if (seq[i]=='1') 
            res += base;
        base *= 2;
    } 
    return res;
}

int mapToString(int number) {
    int len = 1;
    while (pow(2, len+1)-2<=number) 
        ++len;
    number -= pow(2, len)-2;
    for (int i=len-1; i>=0; --i) {
        ans[i] = (char)(number%2+'0');
        number /= 2;
    }
    ans[len] = '\0';
}

void countNumber() {
    for (int i=lena; i<=lenb; ++i) {
        for (int j=0; j<=len-i; ++j) 
            ++count[mapToNumber(j, j+i)];
    }   
}

void concatenate() {
    for (int i=0; i<MAXMAP; ++i) {
        if (prev[count[i]]!=-1) 
            next[prev[count[i]]] = i;
        else
            first[count[i]] = i;
        prev[count[i]] = i;
    }
}

int main() {
    FILE *fin = fopen("contact.in", "r");
    fscanf(fin, "%d%d%d", &lena, &lenb, &n);
    char ch;
    len = 0;
    while ((ch=fgetc(fin))!=EOF) {
        if (ch!='\n')
           seq[len++] = ch; 
    }
    fclose(fin);

    initialize();
    countNumber();
    concatenate(); 

    FILE *fout = fopen("contact.out", "w");
    int current = len;
    while (n>0) {
        while (current>0 && first[current]==-1) 
            --current;
        if (current==0)
            break;
        fprintf(fout, "%d\n", current);
        int cnt = 0, ptr = first[current];
        while (ptr!=-1) {
            cnt = (cnt+1)%6;
            mapToString(ptr);
            fprintf(fout, "%s", ans);
            ptr = next[ptr];
            if (cnt==0) 
                fprintf(fout, "\n");
            else
                if (ptr!=-1)
                    fprintf(fout, " ");
                else
                    fprintf(fout, "\n");
        }
        --n;
        --current;
    }
    fclose(fout);
    return 0;
}
