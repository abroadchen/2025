//
// Created by Psy.C on 2025/9/11.
//


#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<string> lines;
    string line;

    while (getline(cin, line)) {
        lines.push_back(line);
    }

    int maxWidth = 0;
    for (const string& s : lines) {
        maxWidth = max(maxWidth, (int)s.length());
    }

    for (int i = 0; i < maxWidth + 2; i++) cout << "*";
    cout << endl;

    bool leftAlign = true;
    for (const string& s : lines) {
        int len = s.length();
        int spaces = maxWidth - len;
        int leftSpaces = spaces / 2;
        int rightSpaces = spaces - leftSpaces;

        if (spaces % 2 == 1) {
            if (leftAlign) {
                leftSpaces = spaces / 2;
                rightSpaces = spaces - leftSpaces;
                leftAlign = false;
            } else {
                rightSpaces = spaces / 2;
                leftSpaces = spaces - rightSpaces;
                leftAlign = true;
            }
        }
        cout << "*";
        for (int i = 0; i < leftSpaces; i++) cout << " ";
        cout << s;
        for (int i = 0; i < rightSpaces; i++) cout << " ";
        cout << "*" << endl;
    }

    for (int i = 0; i < maxWidth + 2; i++) cout << "*";
    cout << endl;

    return 0;
}