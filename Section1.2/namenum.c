/*
ID: lizhita1
LANG: C
TASK: namenum
*/

#include <stdio.h>
#include <string.h>

const int MAX_LEN = 14;
const int MAX_NUM = 5000;
int exist = 0;

void sort(char validName[][MAX_LEN], int left, int right) {
    int mid = left+(right-left)/2;
    char cmpName[MAX_LEN];
    int i = left, j = right;
    int cmpLen = strlen(validName[mid]);
    strcpy(cmpName, validName[mid]);

    while (i<=j) {
        while (strlen(validName[i])<cmpLen || (strlen(validName[i])==cmpLen && strcmp(validName[i], cmpName)<0)) ++i;
        while (strlen(validName[j])>cmpLen || (strlen(validName[j])==cmpLen && strcmp(validName[j], cmpName)>0)) --j;
        if (i<=j) {
            char temp[MAX_LEN];
            strcpy(temp, validName[i]);
            strcpy(validName[i], validName[j]);
            strcpy(validName[j], temp);
            ++i;
            --j;
        }
    }
    
    if (j>left)
        sort(validName, left, j);
    if (i<right)
        sort(validName, i, right);
}

int search(int len, char name[], int nameNum, char validName[][MAX_LEN]) {
    int left = 0, right = nameNum;
    while (left<=right) {
        int mid = left+(right-left)/2;
        if (len==strlen(validName[mid])) {
            int result = strcmp(name, validName[mid]);
            if (result==0)
                return 1;
            else if (result<0)
                right = mid-1;
            else 
                left = mid+1;
        }
        else if (len<strlen(validName[mid])) 
            right = mid-1;
        else 
            left = mid+1;
    }
    return 0;
}

void dfs(int current, int len, char number[], char name[], int nameNum, char validName[][MAX_LEN], FILE *fout) {
    char ch;
    if (current==len) {
        name[current] = '\0';
        if (search(len, name, nameNum, validName)) {
            fprintf(fout, "%s\n", name);
            exist = 1;
        }
        return;
    }
    switch (number[current]) {
        case '2': case '3': case '4': case '5': case '6': 
            for (ch='A'+3*(number[current]-'2'); ch<='C'+3*(number[current]-'2'); ++ch) {
                name[current] = ch;
                dfs(current+1, len, number, name, nameNum, validName, fout);
            }
            break;
        case '7':
            name[current] = 'P';
            dfs(current+1, len, number, name, nameNum, validName, fout);
            name[current] = 'R';
            dfs(current+1, len, number, name, nameNum, validName, fout);
            name[current] = 'S';
            dfs(current+1, len, number, name, nameNum, validName, fout);
            break;
        case '8':
            for (ch='T'; ch<='V'; ++ch) {
                name[current] = ch;
                dfs(current+1, len, number, name, nameNum, validName, fout);
            }
            break;
        case '9':
            name[current] = 'W';
            dfs(current+1, len, number, name, nameNum, validName, fout);
            name[current] = 'X';
            dfs(current+1, len, number, name, nameNum, validName, fout);
            name[current] = 'Y';
            dfs(current+1, len, number, name, nameNum, validName, fout);
            break;
    }
}

int main() {
    int i;
    char number[MAX_LEN];
    char validName[MAX_NUM][MAX_LEN];
    char name[MAX_LEN];

    FILE *fin = fopen("namenum.in", "r");
    FILE *fout = fopen("namenum.out", "w");
    FILE *fdict = fopen("dict.txt", "r");

    int n=0, nameNum=0;
    char ch;
    
    fgets(number, MAX_LEN, fin);
    number[strlen(number)-1] = '\0';
    n = strlen(number);
    fclose(fin);
    
    while (fgets(validName[nameNum], MAX_LEN, fdict)) {
        validName[nameNum][strlen(validName[nameNum])-1] = '\0';
        ++nameNum;
    }
    --nameNum;
    
    fclose(fdict);

    sort(validName, 0, nameNum);

    dfs(0, n, number, name, nameNum, validName, fout);
    
    if (exist==0)
        fprintf(fout, "NONE\n");

    fclose(fout);

    return 0;
}
