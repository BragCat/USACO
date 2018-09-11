/*
 ID: bragcat1
 LANG: C++11
 TASK: heritage
 */

#include <fstream>

using namespace std;

string preOrder, inOrder, postOrder;
int root;

void searchTree(int startIndex, int endIndex) {
    if (startIndex >= endIndex) {
        return;
    }
    char label = preOrder[root++];
    for (int i = startIndex; i < endIndex; ++i) {
        if (inOrder[i] == label) {
            searchTree(startIndex, i);
            searchTree(i + 1, endIndex);
            break;
        }
    }
    postOrder += label;
}

int main() {
    ifstream fin("heritage.in");
    fin >> inOrder >> preOrder;
    fin.close();

    searchTree(0, inOrder.size());

    ofstream fout("heritage.out");
    fout << postOrder << endl;
    fout.close();
    return 0;
}
