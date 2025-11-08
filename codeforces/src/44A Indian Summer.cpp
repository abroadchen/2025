//
// Created by Psy.C on 2025/9/26.
//

#include <iostream>
#include <set>
using namespace std;

int main() {

    int n; cin >> n;
    set<pair<string, string>> lev;
    while (n--) {
        string s1, s2; cin >> s1 >> s2;
        lev.insert(pair<string, string>(s1, s2));
    }
    cout << lev.size() << endl;
    return 0;
}