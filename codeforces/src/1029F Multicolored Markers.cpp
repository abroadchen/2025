//
// Created by Psy.C on 2026/11/2.
//

/**
真正学会的起点..
solve(tot, a) 中 tot 是总面积（要拼成的矩形面积），a 是一块的面积。
收集 a 的所有不超过 sqrt(a) 的因数（即每对 (d, a/d) 的小者）
tot 是两块拼成的矩形的总面积，目标是最小化周长 2*(长+宽)。
从 sqrt(tot) 向下枚举 i（i 是矩形的宽/短边），tot/i 是长边。
要点：把 a 这块嵌入矩形时，要求其占用宽 ≤ i、占用高 ≤ tot/i（即能塞进矩形的某个角落不越界）。
a 的因数 f[p] 作为 a 占用的一条边，另一条是 a/f[p]。
要求 f[p] ≤ i（宽不超）且 a/f[p] ≤ tot/i（高不超）。
找到满足条件的最短边 i（从大到小枚举即周长从小到大），立即返回周长
总面积 tot = n + m（两块拼成一个矩形，面积相加）。
分别假设"以 n 为参考塞入"和"以 m 为参考塞入"，取周长最小值。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll solve(ll tot, ll a) {
    vector<int> f;
    for (int i = 1; 1ll*i*i <= a; ++i)
        if (a%i == 0) f.push_back(i);//只存 ≤ sqrt(a) 的因数
    int p = (int)f.size()-1;//p 指向最大因数
    for (int i = sqrt(tot); i >= 1; --i) {
        if (tot%i) continue;//i 不是 tot 因数则跳过
        while (f[p] > i) --p;//移动指针,使 f[p] ≤ i
        if (a/f[p] <= tot/i) return 2ll*(i+tot/i);
    }
}

ll n, m;
int main() {
    fast;
    cin >> n >> m;
    cout << min(solve(n+m,n), solve(n+m,m)) << '\n';
    return 0;
}