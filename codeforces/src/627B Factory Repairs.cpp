//
// Created by Psy.C on 2026/3/28.
//
/**
n: 数组长度
k: 一个偏移参数
a, b: 两个数组的最大容量限制

读取位置d和增加值val
查询当前位置在两个数组中的当前值
容量限制逻辑：
对于ta数组：如果当前值+v ≤ a，则直接更新v，否则只能更新到上限a
对于tb数组：同样的容量限制逻辑
确保任何位置的值不超过各自的容量限制
读取查询位置p
s1: 如果p>1，则查询tb数组中[1,p-1]区间的所有值之和
s2: 如果p+k≤n，则查询ta数组中[p+k,n]区间的所有值之和
输出s1+s2，即tb数组前面部分和ta数组后面部分的总和

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

struct node {
    int n;
    vector<ll> bit;
    node(const int n) {
        this->n = n;
        bit.resize(n+1, 0);//树状数组通常从索引1开始使用
    }
    int low_bit(int x) { return x & -x; }//确定树状数组中节点的覆盖范围
    void update(int x, ll val) {
        while (x <= n) {
            bit[x] += val;
            x += low_bit(x);//更新所有受影响的节点
        }
    }
    ll query(int x) {
        ll sum = 0;
        while (x) {
            sum += bit[x];
            x -= low_bit(x);
        }
        return sum;
    }
    ll query(int l, int r) { return query(r) - query(l - 1); }
};

ll n, k, a, b, q;
int main() {
    fast;
    cin >> n >> k >> a >> b >> q;
    node ta(n), tb(n);
    int op;
    while (q--) {
        cin >> op;
        if (op == 1) {
            int d; ll val; cin >> d >> val;
            ll v1 = ta.query(d, d), v2 = tb.query(d, d);
            if (v1 + val <= a) ta.update(d, val);
            else ta.update(d, a-v1);
            if (v2 + val <= b) tb.update(d, val);
            else tb.update(d, b-v2);
        } else {
            int p; cin >> p;
            ll s1 = 0, s2 = 0;
            if (p > 1) s1 = tb.query(1, p-1);
            if (p + k <= n) s2 = ta.query(p+k, n);
            cout << s1 + s2 << '\n';
        }
    }
    return 0;
}