/*
 ID: bragcat1
 TASK: tour
 LANG: C++11
 */

#include <fstream>
#include <map>
#include <string>

using namespace std;

const int MAX_N = 100;

int n, m;
map<string, int> num;
int adj[MAX_N][MAX_N];
int f[MAX_N][MAX_N];

void swap(int &a, int &b) {
    int t = a;
    a = b, b = t;
}

int main() {
    ifstream fin("tour.in");
    fin >> n >> m;
    for (int i = 0; i < n; ++i) {
        string s;
        fin >> s;
        num.insert({s, i});
    }
    for (int i = 0; i < m; ++i) {
        string s, t;
        fin >> s >> t;
        int sn = num[s], tn = num[t];
        if (sn > tn) {
            swap(sn, tn);
        }
        adj[sn][tn] = 1;
    }
    fin.close();

    f[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = 0; k < j; ++k) {
                if (adj[k][j] && f[i][k] > 0) {
                    f[i][j] = max(f[i][j], f[i][k] + 1);
                }
            }
            f[j][i] = f[i][j];
        }
    }

    int ans = 1;
    for (int i = 0; i < n - 1; ++i) {
        if (adj[i][n - 1]) {
            ans = max(ans, f[i][n - 1]);
        }
    }

    ofstream fout("tour.out");
    fout << ans << endl;
    fout.close();
    return 0;
}