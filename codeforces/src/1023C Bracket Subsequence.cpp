//
// Created by Psy.C on 2026/11/1.
//

/**
真正学会的起点..
char a[N];       // 存储原始字符序列
string ans;      // 最终选出的合法括号子序列
int n, m, l, r;  // n: 长度; m: 括号对上限; l: 已取左括号数; r: 已取右括号数
（所以最多能取 m/2 个左括号、m/2 个右括号）
只有当下一个左括号不会超过上限 m/2 时才取（l+1 ≤ m/2）
只有当前已取左括号数 l 仍大于已取右括号数 r（即 r+1 ≤ l）时，才允许取右括号。这样才能保证每次取 ) 时都有未闭合的 (,最终形成合法括号序列
输出去除非法/超限字符后的合法括号子序列。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
using namespace std;

constexpr int N = 2e5+10;

int n, m, l, r;
char a[N];
string ans;
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) cin >> a[i];
    rep(i,n) {
        if (a[i] == '(' && 1 + l <= m/2) { l++; ans += '('; }
        if (a[i] == ')' && r + 1 <= l) { r++; ans += ')'; }
    }
    cout << ans;
    return 0;
}