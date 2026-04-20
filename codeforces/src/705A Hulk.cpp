//
// Created by Psy.C on 2026/4/19.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
int main() {
    fast;
    cin >> n;
    if (n == 1) cout << "I hate it";
    else {//多个单词的情况
        for (int i = 1; i < n; ++i) {
            if (i%2 == 1) cout << "I hate that ";
            else cout << "I love that ";
        }
        //最后一个词
        if (n%2 == 0) cout << "I love it";
        else cout << "I hate it";
    }
    return 0;
}