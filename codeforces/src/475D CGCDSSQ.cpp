//
// Created by Psy.C on 2026/2/15.
//
/**
时间复杂度：O(n log²(max_value))
外层循环n次
内层map大小最多log个GCD值
每次GCD计算O(log(max_value))
空间复杂度：O(n log(max_value))
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 110000;

int gcd(int a, int b) {
    const int ta = max(a, b), tb = min(a, b);
    a = ta, b = tb;
    while (b) {
        const int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int n, a[N], q;
map<int, int> m1, m2;//以各数字结尾的子数组个数
map<int, long long> res;//每个GCD值的出现次数

int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        m2.clear();
        for (auto &[fst, snd] : m1)
            m2[gcd(fst, a[i])] += snd;//延伸已有子数组
        m2[a[i]]++;//添加新子数组[a[i]]
        swap(m1, m2);
        for (auto &[fst, snd] : m1)
            res[fst] += snd;
    }
    cin >> q;
    while (q--) {
        int t; cin >> t;
        cout << res[t] << '\n';
    }
    return 0;
}