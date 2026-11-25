//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
交互查询接口：向评测机询问 v1 和 v2 两个集合与节点 x 之间的距离关系（二值 0/1）‍。
输出格式：v1 大小、v1 元素、v2 大小、v2 元素、x，然后读回一个整数返回（rd()）
sz[i]：节点 i 的子树大小。
cmp：按子树大小递增排序（在 sort 中用于对节点 id 排序）
id[]：节点编号，用于排序；fa[]：二叉树/普通树的父节点数组；vis[]：是否已被确定归属（已找到父亲）
以 1 为根。
v1={1}，v2={2..n}。
根 1 的"子树大小"手工设为 n（整棵树的节点数）。
对每个 i≥2，用 ask({1},{2..n}, i) 求出 sz[i]（即节点 i 在某种度量下的子树大小/深度信息）
id[] 初始为 1..n，按 sz 升序排序。
根 1 标记为已确定（不参与找父亲）
对每个还没处理的节点 id[i]（其 sz≠1，即有子节点）：
x = 当前还需分配的子树大小。
在所有未确定父亲、且非自身的节点 v 中进行二分查找，找到属于 id[i] 子树的那个节点 v[l]：
每次取前一半 t=v[0..mid]，ask({1}, t, id[i]) 判断 id[i] 是否落在 t 前前缀里（若是则向 mid，否则向右）。
找到后令 fa[v[l]] = id[i]，标记 v[l] 已确定，x -= sz[v[l]]（从剩余需分配的大小中扣掉这个孩子的子树大小），继续 while 直到 x 用完。
即：从小到大贪心，每次二分定位一个孩子，扣除其子树大小，完成建树
收集每个节点 i 与它的父节点 fa[i]，输出所有树边 (fa[i], i)。
以 ANSWER 标记答案（符合交互题要求），输出 n-1 条边。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<=k; i++)
#define ll long long
#define vl vector<ll>
#define ii pair<int,int>
using namespace std;

constexpr int N = 2e5+10;
inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

ll ask(vl v1, vl v2, ll x) {
    cout << v1.size() << endl;
    for (auto i : v1) cout << i << ' ';
    cout << endl << v2.size() << endl;
    for (auto i : v2) cout << i << ' ';
    cout << endl << x << endl;
    return rd();
}

ll sz[N];
bool cmp(ll x, ll y) { return sz[x] < sz[y]; }

ll n, id[N], fa[N];
bool vis[N];
void solve() {
    cin >> n;
    vl v1 = {1}, v2;
    rep(i,2,n) v2.push_back(i); sz[1] = n;
    rep(i,2,n) sz[i] = ask(v1,v2,i);
    rep(i,1,n) id[i] = i;
    sort(id+1,id+1+n,cmp);
    vis[1] = 1;
    rep(i,1,n) if (sz[id[i]] != 1) {
        ll x = sz[id[i]];
        while (x > 1) {
            vl v;
            rep(j,1,n) if (!vis[j] && id[i] != j) v.push_back(j);
            ll l = 0, r = v.size()-1;
            while (l < r) {
                ll mid = (l+r)>>1;
                vl t;
                rep(j,0,mid) t.push_back(v[j]);
                if (ask({1},t,id[i])) r = mid; else l = mid+1;
            }
            fa[v[l]] = id[i], vis[v[l]] = 1, x -= sz[v[l]];
        }
    }
    vector<ii> ans;
    rep(i,2,n) ans.emplace_back(fa[i],i);
    cout << "ANSWER" << endl;
    for (auto [fst, snd] : ans) cout << fst << ' ' << snd << endl;
}


int main() {
    fast;
    solve();
    return 0;
}