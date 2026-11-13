//
// Created by Psy.C on 2026/11/13.
//

/**
真正学会的起点..
对小素数直接返回 true。
扫描已筛出的素数表 pri[1..tot]，若 x 能被其中任何一个整除 → 是合数，返回 false。
否则 → 是素数
枚举 i 从 2 到 N（即 1e5），用 check() 判断，是素数就追加到 pri[]。
完成后 pri[] 存有 [2, 1e5) 内的全部素数，tot 为素数个数
从左到右遍历素数表 pri[]，找到第一个能整除 n 的素数，那就是 n 的最小质因子 p。
然后输出公式：(n - p) / 2 + 1。
若遍历完（n 在试除法下找不到质因子，通常是 n 本身就是大于表范围或未覆盖的素数），输出 1
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 1e5;

int tot, pri[N+5];//素数表
bool check(int x) {
    if (x == 2 || x == 3 || x == 5 || x == 7) return 1;
    rep(i,tot) if (x%pri[i] == 0) return 0;
    return 1;
}
void get() { for (int i = 2; i < N; i++) if (check(i)) pri[++tot] = i; }

ll n;
int main() {
    fast;
    get(); cin >> n;
    rep(i,tot) if (n%pri[i] == 0) {
        cout << (n-pri[i])/2+1 << '\n';
        return 0;
    }
    cout << "1\n";
    return 0;
}