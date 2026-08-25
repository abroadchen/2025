//
// Created by Psy.C on 2026/5/9.
//
/**
n:节点数,m:边数,k:特殊节点数,p[]:特殊节点数组,tot[]:每个连通块大小,mx:最大特殊连通块大小,ans:答案,num:普通节点总数
tag[]:标记是否为特殊节点,vis[]:访问标记数组
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1007, M = 1e5+7;
struct node { ll to, pre; } e[M<<1];
ll cnt, head[N];
void add(ll fr, ll to) {
    e[++cnt] = {to, head[fr]}, head[fr] = cnt;
}

ll fa[N];
ll find(ll x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void uni(ll x, ll y) { fa[find(x)] = find(y); }
ll get(ll x) { return x*(x-1)/2; }

ll n, m, k, p[N], tot[N], mx, ans, num;
bool tag[N], vis[N];
int main() {
    fast;
    cin >> n >> m >> k;
    for (ll i = 1; i <= n; ++i) fa[i] = i;
    for (ll i = 1; i <= k; ++i) {
        cin >> p[i];
        tag[p[i]] = true;
    }
    for (ll i = 1, u, v; i <= m; ++i) {
        cin >> u >> v; add(u, v); add(v, u);
        uni(u, v);
    }
    for (ll i = 1; i <= n; ++i) {
        ++tot[find(i)];//增加i所在连通块的大小
        tag[find(i)] |= tag[i];//如果i是特殊节点，则其所在连通块也是特殊的
    }
    for (ll i = 1; i <= n; ++i) {
        ll fx = find(i);//获取当前节点所属连通块的根
        if (vis[fx]) continue;//已经处理过这个连通块
        vis[fx] = true;//标记已访问
        if (tag[fx]) {//特殊连通块
            if (tot[fx] <= mx)//当前特殊块不大于最大特殊块
                ans += get(tot[fx]);//直接加入答案
            else {
                ans += get(mx);//先加上原来的最大值贡献
                mx = tot[fx];//更新最大特殊块大小
            }
        } else num += tot[fx];//不是特殊块，累加到普通节点总数
    }
    ans += get(mx + num);//最大特殊连通块与所有普通节点合并后计算贡献
    cout << ans - m << '\n';//减去原始边数m
    return 0;
}