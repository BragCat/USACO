/*
 ID: bragcat1
 LANG: C++14
 TASK: msquare
 */

#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include <set>

using namespace std;

const int NUMBER = 8;
const string initSeq = "12348765";

struct BfsState {
    string seq;
    unsigned long father;
    char operation;

    BfsState() {
        seq = initSeq;
        father = 0;
        operation = '#';
    }

    BfsState(string seq, unsigned long father, char operation) {
        this -> seq = seq;
        this -> father = father;
        this -> operation = operation;
    }

    /*
    BfsState(BfsState &bfsState) {
        this -> seq = bfsState.seq;
        this -> father = bfsState.father;
        this -> operation = bfsState.operation;
    }
     */
};

string getOperationSequence(vector<BfsState> &queue, int &steps) {
    string operationSequence;
    steps = 0;
    auto index = queue.size() - 1;
    while (index != 0) {
        operationSequence = queue[index].operation + operationSequence;
        index = queue[index].father;
        ++steps;
    }
    return operationSequence;
}

int main() {
    string target;
    ifstream fin("msquare.in");
    for (auto i = 0; i < NUMBER; ++i) {
        int x;
        fin >> x;
        target += static_cast<char>(x + '0');
    }
    target = target.substr(0, 4) + target[7] + target[6] + target[5] + target[4];
    fin.close();

    ofstream fout("msquare.out");
    int steps = 0;
    string operationSeq;
    if (target == initSeq) {
        fout << steps << endl;
        fout << endl;
    }
    else {
        vector<BfsState> queue;
        set<string> searchedState;
        BfsState initState;
        queue.push_back(initState);
        searchedState.insert(initSeq);
        vector<BfsState>::size_type head = 0;
        while (head != queue.size()) {
            BfsState bfsState(queue[head]);
            string currentSeq;
            // operation A
            currentSeq = bfsState.seq.substr(4, 4) + bfsState.seq.substr(0, 4);
            if (searchedState.find(currentSeq) == searchedState.end()) {
                BfsState newBfsState(currentSeq, head, 'A');
                queue.push_back(newBfsState);
                searchedState.insert(currentSeq);
                if (currentSeq == target) {
                    operationSeq = getOperationSequence(queue, steps);
                    break;
                }
            }

            // operation B
            currentSeq = bfsState.seq[3] + bfsState.seq.substr(0, 3) + bfsState.seq[7] + bfsState.seq.substr(4, 3);
            if (searchedState.find(currentSeq) == searchedState.end()) {
                BfsState newBfsState(currentSeq, head, 'B');
                queue.push_back(newBfsState);
                searchedState.insert(currentSeq);
                if (currentSeq == target) {
                    operationSeq = getOperationSequence(queue, steps);
                    break;
                }
            }

            // operation C
            currentSeq = "";
            currentSeq = currentSeq + bfsState.seq[0] + bfsState.seq[5] + bfsState.seq[1] + bfsState.seq[3]
                    + bfsState.seq[4] + bfsState.seq[6] + bfsState.seq[2] + bfsState.seq[7];
            if (searchedState.find(currentSeq) == searchedState.end()) {
                BfsState newBfsState(currentSeq, head, 'C');
                queue.push_back(newBfsState);
                searchedState.insert(currentSeq);
                if (currentSeq == target) {
                    operationSeq = getOperationSequence(queue, steps);
                    break;
                }
            }
            ++head;
        };
        fout << steps << endl;
        fout << operationSeq << endl;
    }
    fout.close();
    return 0;
}
