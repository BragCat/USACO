/*
 ID: bragcat1
 LANG: C++11
 TASK: calfflac
 */

#include <cctype>
#include <fstream>
#include <vector>

using namespace std;

string s;
vector<char> chars;
vector<int> indexes;

int main() {
    FILE *fin = fopen("calfflac.in", "r");
    char ch;
    while (fscanf(fin, "%c", &ch) != EOF) {
        s += ch;
    }
    fclose(fin);

    for (int i = 0; i < s.size(); ++i) {
        if (isalpha(s[i])) {
            chars.push_back(tolower(s[i]));
            indexes.push_back(i);
        }
    }

    int maxL = 0, st = 0, ed = 0;
    for (int i = 0; i < chars.size(); ++i) {
        int p = i, q = i;
        while (p >= 0 && q < chars.size() && chars[p] == chars[q]) {
            --p, ++q;
        }
        ++p, --q;
        if (q - p + 1 > maxL) {
            maxL = q - p + 1;
            st = indexes[p], ed = indexes[q];
        }
        p = i, q = i + 1;
        while (p >=0 && q < chars.size() && chars[p] == chars[q]) {
            --p, ++q;
        }
        ++p, --q;
        if (q - p + 1 > maxL) {
            maxL = q - p + 1;
            st = indexes[p], ed = indexes[q];
        }
    }

    ofstream fout("calfflac.out");
    fout << maxL << endl;
    fout << s.substr(st, ed - st + 1) << endl;
    fout.close();
    return 0;
}
