/*
 ID: bragcat1
 TASK: cowxor
 LANG: C++11
 */

#include <cstring>
#include <fstream>

using namespace std;

const int MAX_N = 100000;
const int DIGIT_NUM = 21;

struct TrieNode {
    TrieNode *l = nullptr, *r = nullptr;
    int index = -1;
};

int n;
int num[MAX_N];
bool digits[DIGIT_NUM];
TrieNode *root;

void insertIntoTrie(int index) {
    TrieNode *node = root;
    for (int i = DIGIT_NUM - 1; i >= 0; --i) {
        if (digits[i]) {
            if (!node -> r) {
                node -> r = new TrieNode();
            }
            node = node -> r;
        } else {
            if (!node -> l) {
                node -> l = new TrieNode();
            }
            node = node -> l;
        }
    }
    node -> index = index;
}

int main() {
    ifstream fin("cowxor.in");
    fin >> n;
    for (int i = 0; i < n; ++i) {
        fin >> num[i];
    }
    fin.close();

    for (int i = 1; i < n; ++i) {
        num[i] ^= num[i - 1];
    }

    int ans = 0, st = 0, ed = 0;
    root = new TrieNode();
    insertIntoTrie(-1);
    for (int i = 0; i < n; ++i) {
        memset(digits, 0, sizeof(digits));
        int x = num[i], cnt = 0;
        while (x > 0) {
            digits[cnt++] = (x & 1) == 1;
            x = x >> 1;
        }
        TrieNode *node = root;
        for (int j = DIGIT_NUM - 1; j >= 0; --j) {
            if (digits[j]) {
                if (node->l) {
                    node = node->l;
                } else {
                    node = node->r;
                }
            } else {
                if (node->r) {
                    node = node->r;
                } else {
                    node = node->l;
                }
            }
        }
        if (node -> index == -1) {
            if (ans < num[i]) {
                ans = num[i];
                st = 0, ed = i;
            }
        } else {
            int t = num[node->index] ^num[i];
            if (t > ans) {
                ans = t;
                st = node->index + 1, ed = i;
            }
        }
        insertIntoTrie(i);
    }

    ofstream fout("cowxor.out");
    fout << ans << ' ' << st + 1 << ' ' << ed + 1 << endl;
    fout.close();
    return 0;
}
