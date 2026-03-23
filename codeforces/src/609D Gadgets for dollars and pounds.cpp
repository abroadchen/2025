//
// Created by Psy.C on 2026/3/23.
//
/**
d[]和p[]分别存储两种类型的任务
dd[]和pp[]存储两种资源的成本
vt存储解决方案
s是预算上限

对于给定的资源级别x，判断是否能完成k个任务且不超过预算：
贪心策略：优先选择成本较低的任务
比较cd*d[id].w和cp*p[ip].w决定选择哪种类型的任务
记录选择的方案到vt中

n种资源级别，m个任务，k个需要完成的任务，预算s
读入资源成本并维护前缀最小值（确保资源级别越高，成本不增加）
分类存储任务，t=1为第一类，t=2为第二类，然后按权重升序排序
二分搜索寻找最小的资源级别，使得能够完成所有k个任务且不超过预算
输出最优方案：资源级别和每个任务的具体分配

初始状态：d1 = 1
条件判断：如果 dd[d1] > dd[l]，即当前资源级别的成本高于最优资源级别的成本
执行动作：d1++，尝试更高的资源级别
循环终止：当 dd[d1] <= dd[l] 时停止
实际含义：
由于 dd 数组是前缀最小值数组（dd[i] = min(dd[1], dd[2], ..., dd[i])），这意味着：
dd[1] >= dd[2] >= dd[3] >= ... >= dd[n]（非递增）
dd[l] 是最优资源级别 l 的成本
我们要找的是成本不超过 dd[l] 的最小索引

时间复杂度：
O((n + m) log n)，其中二分搜索需要log n次，每次check函数需要O(n+m)时间。
空间复杂度：
O(n + m)，用于存储各种数组和向量
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e5+5, inf = 0x3f3f3f3f;

struct node {
    int id; ll w;
    bool operator<(const node &o) const {
        return w < o.w;
    }
} d[N<<1], p[N<<1];

int k, c1, c2;
vector<ii> vt;
ll dd[N<<1], pp[N<<1], s;
int check(int x) {
    vt.clear();
    ll cd = dd[x], cp = pp[x], ans = 0;
    for (int i = 1, id = 0, ip = 0; i <= k; ++i) {
        if ((id < c1 && ip == c2) ||
            (id < c1 && ip < c2 && cd*d[id].w < cp*p[ip].w)) {
            ans += d[id].w * cd;
            vt.emplace_back(d[id].id, 1);
            id++;
        } else {
            ans += p[ip].w * cp;
            vt.emplace_back(p[ip].id, 2);
            ip++;
        }
    }
    if (ans > s) return 0;
    return 1;
}

int n, m;
int main() {
    fast;
    cin >> n >> m >> k >> s;
    memset(dd, inf, sizeof(dd));
    memset(pp, inf, sizeof(pp));
    for (int i = 1; i <= n; ++i) {
        cin >> dd[i];
        dd[i] = min(dd[i-1], dd[i]);
    }
    for (int i = 1; i <= n; ++i) {
        cin >> pp[i];
        pp[i] = min(pp[i-1], pp[i]);
    }
    for (int i = 1, t, tt; i <= m; ++i) {
        cin >> t >> tt;
        if (t == 1) { d[c1].id = i; d[c1++].w = tt; }
        else { p[c2].id = i; p[c2++].w = tt; }
    }
    sort(d, d + c1); sort(p, p + c2);
    if (check(n) == 0) cout << "-1\n";
    else {
        int l = 1, r = n, mid;
        while (l <= r) {
            mid = (l + r) >> 1;
            if (check(mid)) r = mid - 1;
            else l = mid + 1;
        }
        int d1 = 1, d2 = 1;
        while (dd[d1] > dd[l]) d1++;
        while (pp[d2] > pp[l]) d2++;
        cout << l << '\n';
        for (auto &[fst, snd] : vt) {
            if (snd == 1) cout << fst << ' ' << d1 << '\n';
            else cout << fst << ' ' << d2 << '\n';
        }
    }
    return 0;
}