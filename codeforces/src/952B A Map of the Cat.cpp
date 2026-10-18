//
// Created by Psy.C on 2026/10/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

string s;
int main() {
    fast;
    for (int i = 0; i < 10; ++i) {
        cout << i << endl;
        getline(cin, s);
        if (s=="great"||s=="cool"||s=="not bad"||s=="don't touch me"||s=="don't think so") {
            cout << "normal\n";
            return 0;
        }
        if (s=="don't even"||s=="are you serious"||s=="no way"||s=="worse"||
            s=="terrible"||s=="go die in a hole") {
            cout << "grumpy\n";
            return 0;
        }
    }
    return 0;
}