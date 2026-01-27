//
// Created by Psy.C on 2026/1/26.
//
/**
* op: 操作类型（1表示单个元素，2表示重复块）
l: 长度
c: 重复次数
x: 元素值
len: 累积长度
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100010
using namespace std;

struct node {
    int op{}, l, c, x; ll len;
    node() { x = l = c = 0; len = 0; }
    friend bool operator<(const node x1, const node x2) {
        return x1.len < x2.len;
    }
} t[N];

ll m;
int dfs(ll pos) {
    node now; now.len = pos;//创建临时节点，用于二分查找
    const ll w = lower_bound(t, t + m, now) - t;//第一个len >= pos的位置
    if (t[w].len == pos && t[w].op == 1) return t[w].x;//单个元素操作
    ll tmp = t[w].len;//当前块的结束位置
    tmp -= t[w].c * t[w].l;//当前块的起始位置
    pos -= tmp;//转换为相对位置
    pos %= t[w].l;
    if (pos == 0) pos = t[w].l;//设为最大长度
    return dfs(pos);//递归查找
}

int main() {
    fast;
    ll len = 1ll; cin >> m;
    for (ll i = 0, op, a, b; i < m; ++i) {
        cin >> op >> a;
        if (op == 1) {
            t[i].op = 1; t[i].x = static_cast<int>(a); t[i].len = len; len++;
        } else {
            cin >> b;
            t[i].op = 2; t[i].l = static_cast<int>(a);
            t[i].c = static_cast<int>(b); len += a * b;
            t[i].len = len - 1;
        }
    }
    ll n; cin >> n;
    for (ll i = 0, pos; i < n; ++i) {
        cin >> pos;
        cout << dfs(pos) << ' ';
    }
    cout << '\n';
    return 0;
}