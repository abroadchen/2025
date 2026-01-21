//
// Created by Psy.C on 2026/1/20.
//
/*
* 预处理：O(n)
查询：O(t)
总体：O(n + t)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;


int main() {
    fast;
    int t, c1[N], c2[N], c3[N], l, r; string s; cin >> s >> t;
    s = '$' + s;
    for (int i = 1; i < s.size(); ++i) {//从1到i位置'x'的总数
        c1[i] = c1[i-1] + (s[i]=='x' ? 1 : 0);//'x','y','z'的累积数量
        c2[i] = c2[i-1] + (s[i]=='y' ? 1 : 0);
        c3[i] = c3[i-1] + (s[i]=='z' ? 1 : 0);
    }
    while (t--) {
        cin >> l >> r;
        if (r - l < 2) { cout << "YES\n"; continue; }
        //区间[l,r]内'x'的数量
        if (const int x = c1[r] - c1[l-1], y = c2[r] - c2[l-1], z = c3[r] - c3[l-1];
            abs(x-y) <= 1 && abs(y-z) <= 1 && abs(x-z) <= 1) cout << "YES\n";//任意两个字符的数量差不超过1
        else cout << "NO\n";
    }
    return 0;
}