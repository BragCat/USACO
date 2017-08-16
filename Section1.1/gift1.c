/*
ID: lizhita1
LANG: C
PROB: gift1
*/

#include <stdio.h>
#include <string.h>

int fgetline(char *line, int max, FILE *fp) {
    if (fgets(line, max, fp)) {
        line[strlen(line)-1] = '\0';
        return strlen(line);
    }
    else 
        return 0;
}

int main() {
    const int MAX_N = 10;
    const int MAX_NAME_LEN = 15;
    int n;
    char name[MAX_NAME_LEN];
    char names[MAX_N][MAX_NAME_LEN];
    int money[MAX_N];
    int i, j, budget, num, part, remain;
 
    memset(money, 0, sizeof(money));

    FILE *fin = fopen("gift1.in", "r");
    FILE *fout = fopen("gift1.out", "w");
    fscanf(fin, "%d", &n);
    getc(fin);
    for (i=0; i<n; ++i) 
        fgetline(names[i], MAX_NAME_LEN, fin);

    while (fgetline(name, MAX_NAME_LEN, fin)) {
        fscanf(fin, "%d%d", &budget, &num);
        getc(fin);        
        if (num!=0) {
            part = budget/num;
            remain = budget%num;
        } 
        else 
            continue;
        for (i=0; i<n; ++i)
            if (strcmp(name, names[i])==0) {
                money[i] -= budget-remain;
                break;
            }
        for (i=0; i<num; ++i) {
            fgetline(name, MAX_NAME_LEN, fin);
            for (j=0; j<n; ++j)
                if (strcmp(name, names[j])==0) {
                    money[j] += part;
                    break;
                }
        }
    }
    
    for (i=0; i<n; ++i) 
        fprintf(fout, "%s %d\n", names[i], money[i]);

    fclose(fin);
    fclose(fout);
    return 0;
}
