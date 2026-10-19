//
// Created by Psy.C on 2026/10/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, a, b;
int main() {
    fast;
    cin >> n >> a; n--;//剩 n-1 次
    while (n--) {//循环读剩余每个数
        cin >> b;
        if (abs(b-a) > 1) { cout << "NO"; return 0; }//相邻差>1 → 提前失败
        a = b;//更新前一个
    }
    cout << "YES";
    return 0;
}