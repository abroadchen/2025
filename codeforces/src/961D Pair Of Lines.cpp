//
// Created by Psy.C on 2026/10/21.
//
/**
b[i] 标记点 i 是否已被"覆盖"。
用三点共线判定（叉积等于 0）：点 i 在线段 s→e 方向直线上，当且仅当
(xe-xs)*(yi-ys) == (ye-ys)*(xi-xs)。
把所有在直线 s–e 上的点标记 b[i]=1。
可确证：check 把落在由点 s、e 确定的直线上的所有点全部标记
a[0], a[1] 记录前两个未被第一条直线覆盖的点。
若 sum < 2（即最多只有一个点不在第一条直线上），则一条直线已能覆盖（除至多一个点外全部）‍——其实这里 sum==1 时剩下那个点在第二条直线上可由任一直线覆盖…… 代码直接 return 1（YES）。sum<2 意味着不足 2 个点，说明两条直线绰绰有余。
可确证：如果第一条直线之外的点不足 2 个，直接返回"可行"
用点 a[0], a[1] 确定第二条直线，再把所有落在这条直线上的点标记 b[i]=1。
若还有 !b[i]（仍有点既不在第一条也不在第二条直线上），返回 0（NO）；否则返回 1（YES）。
可确证：若第二条直线能覆盖第一条之外的所有点则返回 YES。这是一个贪心正确性依赖"先取 s,e 直线为主直线"的分支假设
读入 n 个点坐标。
若 n < 4 直接输出 YES（点数太少必然能用两条直线覆盖，甚至一条）。
关键：尝试三条候选主直线 (0,1)、(0,2)、(1,2)。
正确性依据（经典题结论）：若能用两条直线覆盖所有点，那么总有一条直线的候选会成功。理由：前 3 个点（下标 0,1,2）中，必有两个点落在同一条覆盖直线上（抽屉原理：3 个点分到 2 条线，至少 2 点共线）。所以枚举 (0,1)、(0,2)、(1,2) 三种两两组合作为主直线，必能命中真正的那条覆盖线。
若三者之一使 check 返回 1 则 YES，否则 NO。
可确证主循环逻辑 + 正确性依据（3 点分入 2 条线必有两线重合 → 枚举前 3 点的两两组合足够
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define rep(i,n) for(i=0;i<n;i++)
using namespace std;

constexpr int N = 1e5+5;

struct node { ll x, y; } st[N];

int b[N];
ll n;
int check(int s, int e) {
    int i;
    memset(b,0,sizeof(b));
    rep(i,n)
        if ((st[e].x-st[s].x)*(st[i].y-st[s].y) == (st[e].y-st[s].y)*(st[i].x-st[s].x))
            b[i] = 1;
    int a[3], sum = 0;
    rep(i,n) {
        if (!b[i]) a[sum++] = i;
        if (sum == 2) break;
    }
    if (sum < 2) return 1;
    rep(i,n)
        if ((st[a[1]].x-st[a[0]].x)*(st[i].y-st[a[0]].y) == (st[a[1]].y-st[a[0]].y)*(st[i].x-st[a[0]].x))
            b[i] = 1;
    rep(i,n) if (!b[i]) return 0;
    return 1;
}



int main() {
    fast;
    ll i;
    while (cin >> n) {
        rep(i,n) cin >> st[i].x >> st[i].y;
        if (n < 4) { cout << "YES\n"; return 0; }
        if (check(0, 1) || check(0, 2) || check(1, 2)) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}