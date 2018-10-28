/*
 ID: bragcat1
 LANG: C++11
 TASK: cowcycle
 */

#include <fstream>

using namespace std;

int a[57], b[37], ansa[57], ansb[37];
int f, r, f1, r1, f2, r2, cnt;
double sum, tot, ans, c[2017], t;

void find_r(int k, int step) {
    if (step == r + 1) {
        if (a[f] * b[r] < 3 * a[1] * b[1]) {
            return;
        }
        cnt = 0;
        sum = tot = 0;
        for (int i = 1; i <= f; i++) {
            for (int j = 1; j <= r; j++) {
                c[++cnt] = double(a[i]) / double(b[j]);
            }
        }
        for (int i = 1; i < cnt; i++) {
            for (int j = i + 1; j <= cnt; j++) {
                if (c[i] > c[j]) {
                    t = c[i];
                    c[i] = c[j];
                    c[j] = t;
                }
            }
        }
        for (int i = 1; i < cnt; i++) {
            c[i] = c[i + 1] - c[i];
            sum += c[i];
        }
        sum /= --cnt;
        for (int i = 1; i <= cnt; i++) {
            tot += (c[i] - sum) * (c[i] - sum);
        }
        if (tot < ans) {
            ans = tot;
            for (int i = 1; i <= f; i++) {
                ansa[i] = a[i];
            }
            for (int i = 1; i <= r; i++) {
                ansb[i] = b[i];
            }
        }
        return;
    }
    for (int i = k; i <= r2 - r + step; i++) {
        b[step] = i;
        find_r(i + 1, step + 1);
    }
}

void find_f(int k, int step) {
    if (step == f + 1) {
        find_r(r1, 1);
        return;
    }
    for (int i = k; i <= f2 - f + step; i++) {
        a[step] = i;
        find_f(i + 1, step + 1);
    }
}

int main() {
    ifstream fin("cowcycle.in");
    fin >> f >> r >> f1 >> f2 >> r1 >> r2;
    fin.close();

    ans = ~0u >> 1;
    find_f(f1, 1);

    ofstream fout("cowcycle.out");
    for (int i = 1; i < f; i++) {
        fout << ansa[i] << ' ';
    }
    fout << ansa[f] << endl;
    for (int i = 1; i < r; i++) {
        fout << ansb[i] << ' ';
    }
    fout << ansb[r] << endl;
    fout.close();
    return 0;
}
