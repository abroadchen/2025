//
// Created by Psy.C on 2025/9/28.
//

#include <string>
#include <iostream>
#include <vector>
using namespace std;

const int N = 12;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector<string> m{"January", "February", "March", "April", "May", "June", "July",
        "August", "September", "October", "November", "December"};

    string cur; getline(cin, cur);
    int start(0);
    for (int i = 0; i < N; ++i) {
        if (m[i] == cur) {
            start = i;
            break;
        }
    }
    int wait; cin >> wait;
    cout << m[(start + wait) % N] << endl;
    return 0;
}