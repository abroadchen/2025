//
// Created by Psy.C on 2026/4/17.
//
///时间复杂度取决于树的高度，对于n个节点的完全二叉树，高度为log(n)
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define pll pair<ll, ll>
using namespace std;

map<pll, ll> mp;///存储树上边的权重

///更新从节点u到节点v路径上的权重
void upd(ll u, ll v, ll w) {
    while (u != v) {
        if (v < u) swap(u, v);//确保v是较大值
        mp[{v, v/2}] += w;//在v和其父节点v/2之间加上权重w
        v /= 2;//将v移动到其父节点
    }
}

///计算从节点u到节点v路径上的总权重
ll get(ll u, ll v) {
    ll ans = 0;
    while (u != v) {
        if (v < u) swap(v, u);//确保v是较大值
        ans += mp[{v, v/2}];//累加v与其父节点间的权重
        v /= 2;//将v移动到其父节点
    }
    return ans;
}

void out() {
    int q; cin >> q;
    while (q--) {
        ll x, u, v, w;
        cin >> x >> u >> v;
        if (x == 1) {
            cin >> w;
            upd(u, v, w);//更新路径权重
        }
        else
            cout << get(u, v) << '\n';//路径权重之和
    }
}


int main() {
    fast;
    out();
    return 0;
}