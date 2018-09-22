/*
 ID: bragcat1
 LANG: C++11
 TASK: lgame
 */

#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int MIN_LEN = 3;
const int MAX_LEN = 7;
const int ALPHABET_NUMBER = 26;
const int valueList[ALPHABET_NUMBER] = {2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5, 2, 3, 5, 7, 2, 1, 2, 4, 6, 6, 7, 5, 7};

int alphebetCnt[ALPHABET_NUMBER];
int currentCnt[ALPHABET_NUMBER];
vector<string> words;
vector<pair<string, string>> answer;

bool validateWordPair(const string &firstWord, const string &secondWord) {
    memset(currentCnt, 0, sizeof(currentCnt));
    for (auto ch : firstWord) {
        ++currentCnt[ch - 'a'];
    }
    for (auto ch : secondWord) {
        ++currentCnt[ch - 'a'];
    }

    bool valid = true;
    for (int i = 0; i < ALPHABET_NUMBER; ++i) {
        if (currentCnt[i] > alphebetCnt[i]) {
            valid = false;
            break;
        }
    }
    return valid;
}

int judge(string firstWord, string secondWord) {
    int value = 0;
    bool valid = validateWordPair(firstWord, secondWord);
    if (!valid) {
        return value;
    }

    for (int i = 0; i < ALPHABET_NUMBER; ++i) {
        value += currentCnt[i] * valueList[i];
    }
    return value;
}

bool cmp(pair<string, string> &a, pair<string, string> &b) {
    if (a.first < b.first) {
        return true;
    }
    else if (a.first == b.first) {
        return a.second < b.second;
    }
    else {
        return false;
    }
}

int main() {
    string str;
    ifstream fin("lgame.in");
    fin >> str;
    fin.close();

    for (auto ch : str) {
        ++alphebetCnt[ch - 'a'];
    }

    fin.open("lgame.dict");
    fin >> str;
    while (str != ".") {
        bool valid = validateWordPair(str, "");
        if (valid) {
            words.push_back(str);
        }
        fin >> str;
    }

    int maxValue = 0;
    for (int i = 0; i < words.size(); ++i) {
        int value = judge(words[i], "");
        if (value > 0) {
            if (value > maxValue) {
                maxValue = value;
                answer.clear();
            }
            if (value >= maxValue) {
                answer.emplace_back(words[i], "");
            }
        }
        for (int j = i; j < words.size(); ++j) {
            value = judge(words[i], words[j]);
            if (value > maxValue) {
                maxValue = value;
                answer.clear();
            }
            if (value >= maxValue) {
                answer.emplace_back(words[i], words[j]);
            }
        }
    }

    sort(answer.begin(), answer.end(), cmp);

    ofstream fout("lgame.out");
    fout << maxValue << endl;
    for (auto p : answer) {
        fout << p.first;
        if (p.second != "") {
            fout << " " << p.second;
        }
        fout << endl;
    }
    fout.close();

    return 0;
}
