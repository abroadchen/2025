//
// Created by Psy.C on 2026/2/19.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+1;
int n, a[N], b[N];
int main() {
    fast;
    cin >> n;
    ll sum = 0;
    int l1 = 0, l2 = 0, tag = 0;
    for (int i = 0, x; i < n; ++i) {
        cin >> x; sum += x;
        if (x > 0) { a[l1++] = x; tag = 1; }
        else { b[l2++] = -x; tag = 2; }//负数取绝对值存入b数组
    }
    if (sum > 0) cout << "first\n";
    else if (sum < 0) cout << "second\n";
    else {//总和为0时，需要进一步比较
        int flag = 0;
        for (int i = 0; i < l1 && i < l2; ++i) {
            if (a[i] > b[i]) { flag = 1; break; }//a数组当前元素更大，第一个玩家胜
            if (a[i] < b[i]) { flag = 2; break; }
        }
        if (!flag) {
            if (l1 == l2)//长度相等，看最后处理的是哪种数
                cout << (tag == 1 ? "first" : "second") << '\n';
        } else//不相等，看哪个更大
            cout << (flag == 1 ? "first" : "second") << '\n';
    }
    return 0;
}