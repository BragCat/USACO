/*
 ID: bragcat1
 TASK: window
 LANG: C++11
 */

#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Window {
    char label;
    int rx, ry, lx, ly;
    Window(char label, int rx, int ry, int lx, int ly): label(label), rx(rx), ry(ry), lx(lx), ly(ly) {}
    Window(const Window &w): label(w.label), rx(w.rx), ry(w.ry), lx(w.lx), ly(w.ly) {}
};

vector<Window> windows;

int strToInt(string s) {
    int n = 0;
    for (char ch : s) {
        n = n * 10 + ch - '0';
    }
    return n;
}

vector<string> splitString(const string s) {
    vector<string> list;
    string::size_type st = 0;
    auto comma = s.find(',');
    while (comma != string::npos) {
        list.push_back(s.substr(st, comma - st));
        st = comma + 1;
        comma = s.find(',', st);
    }
    list.push_back(s.substr(st, s.size() - st));
    return list;
}

void swap(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}

void create(const string &line) {
    vector<string> content = splitString(line.substr(2, line.length() - 3));
    char label = content[0][0];
    int rx = strToInt(content[1]);
    int ry = strToInt(content[2]);
    int lx = strToInt(content[3]);
    int ly = strToInt(content[4]);
    if (rx > lx) {
        swap(rx, lx);
    }
    if (ry < ly) {
        swap(ry, ly);
    }
    windows.emplace_back(label, rx, ry, lx, ly);
}

int findIndex(char label) {
    int index = -1;
    for (int i = 0; i < windows.size(); ++i) {
        if (windows[i].label == label) {
            index = i;
            break;
        }
    }
    return index;
}

void top(const string &line) {
    char label = line[2];
    int index = findIndex(label);
    if (index != -1) {
        windows.push_back(windows[index]);
        windows.erase(windows.begin() + index);
    }
}

void bottom(const string &line) {
    char label = line[2];
    int index = findIndex(label);
    if (index != -1) {
        Window target(windows[index]);
        windows.erase(windows.begin() + index);
        windows.insert(windows.begin(), target);
    }
}

void destroy(string line) {
    char label = line[2];
    int index = findIndex(label);
    if (index != -1) {
        windows.erase(windows.begin() + index);
    }
}

int area(Window window) {
    return (window.lx - window.rx) * (window.ry - window.ly);
}

int split(const Window &w, const int i) {
    if (i == windows.size()) {
        return area(w);
    }
    Window ww = windows[i];
    if (w.lx <= ww.rx || w.rx >= ww.lx || w.ly >= ww.ry || w.ry <= ww.ly) {
        return split(w, i + 1);
    }
    if (w.lx <= ww.lx && w.rx >= ww.rx && w.ly >= ww.ly && w.ry <= ww.ry) {
        return 0;
    }
    int answer = 0;
    if (ww.rx > w.rx && ww.rx <= w.lx) {
        answer += split(Window(w.label, w.rx, w.ry, ww.rx, w.ly), i + 1);
    }
    if (ww.lx < w.lx && ww.lx >= w.rx) {
        answer += split(Window(w.label, ww.lx, w.ry, w.lx, w.ly), i + 1);
    }
    int rx = max(w.rx, ww.rx), lx = min(w.lx, ww.lx);
    if (ww.ly > w.ly && ww.ly <= w.ry) {
        answer += split(Window(w.label, rx, ww.ly, lx, w.ly), i + 1);
    }
    if (ww.ry < w.ry && ww.ry >= w.ly) {
        answer += split(Window(w.label, rx, w.ry, lx, ww.ry), i + 1);
    }
    return answer;
}

double calc(string line) {
    char label = line[2];
    int index = findIndex(label);
    return 100.0 * split(windows[index], index + 1) / area(windows[index]);
}

int main() {
    ifstream fin("window.in");
    ofstream fout("window.out");
    fout.setf(ios::fixed);
    fout.precision(3);
    string line;
    while (fin >> line) {
        switch(line[0]) {
            // create window
            case 'w':
                create(line);
                break;
            // bring to top
            case 't':
                top(line);
                break;
            // bring to bottom
            case 'b':
                bottom(line);
                break;
            // destroy window
            case 'd':
                destroy(line);
                break;
            // output
            case 's':
                fout << calc(line) << endl;
                break;
        }
    }
    fin.close();
    fout.close();
    return 0;
}
