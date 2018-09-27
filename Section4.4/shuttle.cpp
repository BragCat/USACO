/*
ID: bragcat1
LANG: C++11
TASK: shuttle
*/

#include <fstream>

using namespace std;

const int MAXN = 12;

int n;

int main() {
    ifstream fin("shuttle.in");
    fin >> n; 
    fin.close();

    int p = n + 1;
    int cnt = 1;
    int len = 1;
    int delta = 1;
    int dir = -1;
    bool space = false;
    ofstream fout("shuttle.out");
    for (int i = 0; i < (n + 1) * (n + 1); ++i) {
        if (space) {
            fout << " ";
        }
        if (i > 0) {
            fout << p;
            space = true;
        }
        --cnt;
        if (!cnt) {
            if (len == n + 1) {
                delta = -1;
            }
            len += delta;
            cnt = len; 
            if (delta > 0) {
                p += dir;
                dir = -dir;
            }
            else {
                dir = -dir;
                p += dir;
            }
        }
        else {
            p += 2 * dir;
        }
        if (i > 0 && !(i % 20)) {
            fout << endl;
            space = false;
        }
    }
    if (((n + 1) * (n + 1) - 1) % 20) {
        fout << endl;
    }
    fout.close();

    return 0;
}
