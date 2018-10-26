/*
 ID: bragcat1
 LANG: C++11
 TASK: hidden
 */

#include <fstream>

using namespace std;

const int MAX_N = 100000;

int n;
char word[MAX_N * 2];

int main() {
    ifstream fin("hidden.in");
    fin >> n;
    for (int i = 0; i < n; ++i) {
        fin >> word[i];
    }
    fin.close();

    for (int i = 0; i < n; ++i) {
        word[i + n] = word[i];
    }

    int i = 0, j = 1;
    while (j < n) {
        int k = 0;
        for (; k < n; ++k) {
            if (word[i + k] != word[j + k]) {
                break;
            }
        }
        if (word[i + k] <= word[j + k]) {
            j += k == 0 ? 1 : k;
        } else {
            i = j++;
        }
    }

    ofstream fout("hidden.out");
    fout << i << endl;
    fout.close();
    return 0;
}
