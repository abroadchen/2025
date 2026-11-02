//
// Created by Psy.C on 2026/11/2.
//

/**
真正学会的起点..
所有到原点距离相同的点归入同一组（按半径平方 r = x²+y² 分组，用离散化 id 表示）。
get() 把向量 (x,y) 约分为 最简方向（去除公共因子），例如 (2,4) → (1,2)
ans[方向] 记录该方向上已有点的个数（注意含对称方向）。
a[id] 存储半径组 id 内所有点坐标
每个点 (x,y)，先算它到原点距离平方 r，找到所属半径组 id
与新点同半径的所有已有点 p，其 p+(x,y) 的方向计数 +=2（考虑到两个点的排列有两套顺序）。
自身方向也计数 +1，最后把点加入该组
与操作 1 完全反向，删除点时把相关方向计数减回
查询"多少对点不构成以原点为中心的对称"之类的计数：总点数 cnt 减去方向为 (2x,2y)（即最简方向与 x*2,y*2 相同）的点数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
using namespace std;

constexpr int N = 5e5+5;

map<ll,int> mp;
int idx;
inline int ID(ll r) {
    if (mp.contains(r)) return mp[r];
    return mp[r] = ++idx;
}
inline int gcd(int x, int y) { return !y ? x : gcd(y, x % y); }
inline ii get(ii x) {
    int z = gcd(x.first, x.second);
    return {x.first/z, x.second/z};
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

map<ii,int> ans;
vector<ii> a[N];
int main() {
    fast;
    int q, op, x, y, cnt = 0, i; q = rd();
    while (q--) {
        op = rd(), x = rd(), y = rd();
        ll r = x*x+y*y, id = ID(r);
        if (op == 1) {
            cnt++;
            for (i = 0; i < a[id].size(); i++)
                ans[get({a[id][i].first+x, a[id][i].second+y})] += 2;
            ans[get({x,y})]++;
            a[id].emplace_back(x,y);
        }
        if (op == 2) {
            cnt--;
            auto t = get({x,y});
            for (i = 0; i < a[id].size(); i++)
                if (a[id][i] != make_pair(x,y))
                    ans[get({a[id][i].first+x, a[id][i].second+y})] -= 2;
            auto it = a[id].begin();
            while (*it != make_pair(x,y)) ++it;
            a[id].erase(it);
            ans[t]--;
        }
        if (op == 3) cout << cnt-ans[get({x*2,y*2})] << '\n';
    }
    return 0;
}