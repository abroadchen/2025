//
// Created by Psy.C on 2025/9/15.
//

#include <ios>
#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string n, m; cin >> n >> m;
    if (n == "0") {
        if (m == "0") cout << "OK" << endl;
        else cout << "WRONG_ANSWER" << endl;
        return 0;
    }

    int count_n[10] = {0}, count_m[10] = {0};
    for (char c : n) count_n[c - '0']++;
    for (char c : m) count_m[c - '0']++;

    bool same_digits = true;
    for (int i = 0; i < 10; ++i) {
        if (count_n[i] != count_m[i]) {
            same_digits = false;
            break;
        }
    }
    if (!same_digits) {
        cout << "WRONG_ANSWER" << endl;
        return 0;
    }

    string correct = "";
    for (int i = 1; i < 10; ++i) {
        if (count_n[i] > 0) {
            correct += to_string(i);
            count_n[i]--;
            break;
        }
    }
    if (correct.empty() && count_n[0] > 0) correct = "0";
    else if (correct.empty()) {
        cout << "WRONG_ANSWER" << endl;
        return 0;
    } else {
        for (int i = 0; i < 10; ++i) {
            while (count_n[i] > 0) {
                correct += to_string(i);
                count_n[i]--;
            }
        }
    }

    if (correct == m) cout << "OK" << endl;
    else cout << "WRONG_ANSWER" << endl;

    return 0;
}