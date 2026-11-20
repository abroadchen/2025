//
// Created by Psy.C on 2026/11/20.
//

/**
真正学会的起点..
读入数组；
m[val] 记录每个值最后一次出现的下标（map 赋值会覆盖，最终留下最右位置）；
r 初始为 a[0]这个值最后一次出现的位置 —— 作为当前"已合并区间的右边界"
从头扫每个位置 i：

若 i > r：说明当前"合并区间"已经能封口——在这一处可以选择切一刀 / 或作为一个独立块分割点，每个这样的"自由切点"让方案数乘 2（切或不切两种选择）。
先 cnt %= mod 控制溢出，再 cnt *= 2。
更新 r = max(r, m[a[i]])：把当前区间右边界扩展到覆盖到"该值最后一次出现位置"，保证区间完整性。
输出 cnt % mod
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int mod = 998244353;
int main() {
    fast;
    int n; cin >> n;
    vector<int> a(n);
    map<int, int> m;
    for (int i = 0; i < n; i++) { cin >> a[i]; m[a[i]] = i;}
    int r = m[a[0]];
    ll cnt = 1;
    for (int i = 1; i < n; i++) {
        if (i > r) { cnt %= mod; cnt *= 2; }
        r = max(r, m[a[i]]);
    }
    cout << cnt%mod;
    return 0;
}