//
// Created by Psy.C on 2026/2/10.
//

#include <iostream>
#include <vector>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define P pair<ll, ll>
#define N 100000
using namespace std;

P operator+(const P &x, const P &y) {
    return {x.first + y.first, x.second + y.second};
}
P operator-(const P &x, const P &y) {
    return {x.first - y.first, x.second - y.second};
}

struct node {
    int l=0, r=0;
    ll k=0, m=0;
} sgt[N*40];

int tot;//分配的节点总数
/**
 *sgt[q].l=++tot或sgt[q].r=++tot：为子节点分配新编号
 * @param p 原节点编号
 * @param q 新节点编号
 * @param l 当前线段树节点对应区间的左右端点
 * @param r
 * @param k 要更新的位置
 * @param x 要增加到k和m的值
 * @param y
 */
void update(const int p, const int q, const int l, const int r, const int k, const int x, const int y) {
    sgt[q] = sgt[p];//复制原节点p到新节点q，然后在新节点上进行更新
    if (l + 1 == r) sgt[q].k += x, sgt[q].m += y;
    else {
        if (const int mid = (l + r) >> 1; k < mid) update(sgt[p].l, sgt[q].l=++tot, l, mid, k, x, y);
        else update(sgt[p].r, sgt[q].r=++tot, mid, r, k, x, y);
        sgt[q].k = sgt[sgt[q].l].k + sgt[sgt[q].r].k;
        sgt[q].m = sgt[sgt[q].l].m + sgt[sgt[q].r].m;
    }
}

/**
 *
 * @param p 当前线段树节点编号
 * @param l 当前线段树节点对应区间
 * @param r
 * @param x 查询区间[x,y)
 * @param y
 * @return
 */
P query(const int p, const int l, const int r, const int x, const int y) {
    if (x <= l && r <= y) return {sgt[p].k, sgt[p].m};
    if (r > x && l < y) {//有交集但不完全包含
        const int mid = (l + r) >> 1;
        return query(sgt[p].l, l, mid, x, y) + query(sgt[p].r, mid, r, x, y);
    }
    return {0, 0};//没有交集
}

int n, rt[N+10];
int main() {
    fast;
    cin >> n;
    vector<int> s(n+10), m(n+10), k(n+10);
    vector<ll> pref(n+10);
    map<int, int> odt;//有序字典odt，用于维护区间状态 分裂
    rt[0] = ++tot; //分配编号1
    for (int i = 1; i <= n; ++i) {
        cin >> s[i] >> m[i] >> k[i], odt[i] = -1;
        pref[i] = k[i] + pref[i-1];//k的前缀和
        if (k[i]) update(rt[i-1], rt[i]=++tot, 0, N+1, m[i]/k[i], k[i], m[i]);
        else rt[i] = rt[i-1];
    }
    //获取根节点rt[n]在区间[0,14)的k和m值
    auto [ks, ms] = query(rt[n], 0, N+1, 0, 14);
    auto rg = [&](const int l, const int r) {
        return pref[r] - pref[l-1];//区间和
    };
    odt[n+1] = -1;//边界点
    auto odiv = [&](int x) {//在有序字典中插入分割点
        //小于x的最大键值对的迭代器
        const auto it = prev(odt.upper_bound(x));
        odt.insert(it, {x, it->second});//在该位置插入新的键值对
    };
    //区间[l,r)在时间t到T之间的贡献
    auto operform = [&](const int l, const int r, const int t, int T) {
        ll ret = 0;
        if (~t) {//t是否不为-1
            T -= t;
            auto [ks, ms] = query(rt[r-1], 0, N+1, 0, T) -
                query(rt[l-1], 0, N+1, 0, T);
            ret = (rg(l, r-1)-ks)*T+ms;
        } else ret = min(m[l]*1ll, s[l]+1ll*T*k[l]);
        return ret;
    };
    auto oassign = [&](const int l, const int r, const int t) {
        odiv(l); odiv(r);//调用odiv在l和r处分割区间
        ll ret = 0;
        //遍历区间内的每个子区间，累加结果
        ///next(it)获取下一个迭代器
        ///it = odt.erase(it): 删除当前元素并移动到下一个
        for (auto it = odt.lower_bound(l); it->first != r; it = odt.erase(it))
            ret += operform(it->first, next(it)->first, it->second, t);
        odt[l] = t;//更新odt中的状态
        return ret;
    };
    int q; cin >> q;
    while (q--) {
        int t, l, r; cin >> t >> l >> r;
        cout << oassign(l, r + 1, t) << '\n';
    }
    return 0;
}