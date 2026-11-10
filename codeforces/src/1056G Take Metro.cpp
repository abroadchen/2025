//
// Created by Psy.C on 2026/11/10.
//

/**
真正学会的起点..
只执行 t % n 步（不足一整轮的零头），并同步把 t 减掉这些步，让 t 变成 n 的整数倍。
初始 s 直接按“当前 s 决定步长”逐步移动——这步保证后续 t 都是整轮
余数步已执行完后 t 恰好为 0，直接输出当前 s。
从当前 s 开始不断用“整轮转移”x -> nxt[x]，给每个遇到的 x 记录 nxt[x]。
一旦 nxt[x] 已存在（走到之前来过的状态）就停止——此时 x 落在环上。
这就是判环：所有状态里，那些可以重复到过的状态构成环。注意：之后会计算从 s 走到环的几步 和 环的长度
s 到环起点 x 走了 cnt 圈（整轮数）。每整轮是 n 步，所以走这段需要 cnt*n 步
若剩余整轮步数 t ≤ 从 s 到环的步数 cnt*n，那就没有进入环，直接把这个范围内的 t 一步一 % 模拟出来（out）
减去“走到环”的步数，s 直接快进到环起点 x。
从 nxt[x] 数一遍，得到环的长度 cnt（整轮数）。
剩余 t 对环长（cnt*n 步）‍取模，快速跳过无数整圈。
最后在环上再模拟剩余 t 步，输出终点 s
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+5;

int n;
int add(int x, int p) { return x+p>n ? x+p-n : x+p; }

int m;
void out(int s, ll t) {
    for (ll i = t; i >= 1; --i)
        s = add(s, s<=m ? i%n : n-i%n);
    cout << s << '\n';
}

int s, x, nxt[N], cnt;
ll t;
int main() {
    fast;
    cin >> n >> m >> s >> t;
    for (int i = t%n; i >= 1; --i, --t) s = add(s, s<=m ? i : n-i);
    if (t == 0) { cout << s << '\n'; return 0; }
    for (x = s; !nxt[x]; x = nxt[x]) {
        int tmp = x;
        for (int i = n; i >= 1; --i) tmp = add(tmp, tmp<=m ? i : n-i);
        nxt[x] = tmp;
    }
    for (int pz = s; pz != x; pz = nxt[pz]) ++cnt;
    if (t <= 1ll*cnt*n) { out(s, t); return 0; }
    t -= 1ll*cnt*n; cnt = 1; s = x;
    for (int pz = nxt[x]; pz != x; pz = nxt[pz]) ++cnt;
    t %= 1ll*cnt*n; out(s, t);
    return 0;
}