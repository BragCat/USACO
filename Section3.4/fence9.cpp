/*
 ID: bragcat1
 LANG: C++11
 TASK: fence9
 */

#include <fstream>

using namespace std;
int n, m, p;

int main() {
    ifstream fin("fence9.in");
    fin >> n >> m >> p;
    fin.close();

    int count = 0;
    for (int i = 1; i <= n; ++i) {
        count += i * m / n + ((i * m % n == 0) ? -1 : 0);
    }
    if (p > n) {
        n = p - n;
        for (int i = 1; i < n; ++i) {
            count += i * m / n + ((i * m % n == 0) ? -1 : 0);
        }
    }
    else if (n == p) {
        count -= m - 1;
    }
    else {
        n = n - p;
        for (int i = 1; i <= n; ++i) {
            count -= i * m / n;
        }
        ++count;
    }

    ofstream fout("fence9.out");
    fout << count << endl;
    fout.close();

    return 0;
}