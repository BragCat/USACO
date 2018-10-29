/*
 ID: bragcat1
 TASK: fence3
 LANG: C++11
 */

#include <cmath>
#include <fstream>

using namespace std;

const int MAX_N = 150;
const int MAX_X = 1000;

int n, tx, ty;
int f[MAX_N][4];
double ans = -1;
double x, y;

double calcDist(int xx, int yy) {
    double x = static_cast<double>(xx) / 10, y = static_cast<double>(yy) / 10;
    double dist = 0;
    for (int i = 0; i < n; ++i) {
        if (f[i][0] == f[i][2]) {
            double dx = abs(x - f[i][0]);
            double dy = min(abs(y - f[i][1]), abs(y - f[i][3]));
            if (y >= f[i][1] && y <= f[i][3]) {
                dy = 0;
            }
            dist += sqrt(dx * dx + dy * dy);
            if (ans > 0 && ans < dist) {
                return dist;
            }
        } else {
            double dx = min(abs(x - f[i][0]), abs(x - f[i][2]));
            double dy = abs(y - f[i][1]);
            if (x >= f[i][0] && x <= f[i][2]) {
                dx = 0;
            }
            dist += sqrt(dx * dx + dy * dy);
            if (ans > 0 && ans < dist) {
                return dist;
            }
        }
    }
    return dist;
}


int main() {
    ifstream fin("fence3.in");
    fin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 4; ++j) {
            fin >> f[i][j];
        }
        if (f[i][0] > f[i][2]) {
            swap(f[i][0], f[i][2]);
        }
        if (f[i][1] > f[i][3]) {
            swap(f[i][1], f[i][3]);
        }
    }
    fin.close();

    for (int i = 0; i < MAX_X; i += 10) {
        for (int j = 0; j < MAX_X; j += 10) {
            double d = calcDist(i, j);
            if (ans < 0 || d < ans) {
                ans = d;
                tx = i;
                ty = j;
            }
        }
    }
    x = static_cast<double>(tx) / 10, y = static_cast<double>(ty) / 10;

    for (int i = -100; i <= 100; ++i) {
        for (int j = -100; j <= 100; ++j) {
            double d = calcDist(tx + i, ty + j);
            if (ans < 0 || d < ans) {
                ans = d;
                x = static_cast<double>(tx + i) / 10;
                y = static_cast<double>(ty + j) / 10;
            }
        }
    }

    ofstream fout("fence3.out");
    fout.setf(ios::fixed);
    fout.precision(1);
    fout << x << ' ' << y << ' ' << ans << endl;
    fout.close();
    return 0;
}
