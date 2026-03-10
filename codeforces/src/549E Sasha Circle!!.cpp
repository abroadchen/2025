//
// Created by Psy.C on 2026/3/9.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e5+5;

struct node {
    ll x, y;
    node(ll x=0, ll y=0) : x(x), y(y) {}
    bool operator<(const node &o) const {
        return x != o.x ? x < o.x : y < o.y;
    }
    friend istream &operator>>(istream &is, node &o) {
        return is >> o.x >> o.y;
    }
    friend ostream &operator<<(ostream &os, const node &o) {
        return os << '(' << o.x << ',' << o.y << ')';
    }
} p[N], q[N];

node operator+(node a, node b) { return node(a.x + b.x, a.y + b.y); }
node operator-(node a, node b) { return node(a.x - b.x, a.y - b.y); }
ll operator*(node a, node b) { return a.x * b.x + a.y * b.y; }
ll operator^(node a, node b) { return a.x * b.y - a.y * b.x; }
///点b是否在线段ac上
ll contain(node a, node b, node c) {
    node x = a - b, y = c - b;
    return !(x^y) && x*y <= 0;//共线且在区间内
}

///斜率
struct node2 {
    ll p, q, op;
    node2(ll x=0, ll y=1) {
        if (y < 0) x = -x, y = -y;
        p = x, q = y; op = p < 0;
    }
    void out() { cout << p << '/' << q << '\n'; }
    bool operator==(const node2 &o) const {
        return op == o.op && p*o.q == q*o.p;
    }
    bool operator<(const node2 &o) const {
        return op != o.op ? op > o.op : p*o.q < q*o.p;
    }
    bool operator>(const node2 &o) const {
        return op != o.op ? op < o.op : p*o.q > q*o.p;
    }
    bool operator<=(const node2 &o) const {
        return *this < o || *this == o;
    }
    bool operator>=(const node2 &o) const {
        return *this > o || *this == o;
    }
};
///向量夹角的余切值
node2 cot(node a, node b, node c) {
    node x = a - b, y = c - b;
    return node2(x*y, x^y);
}

///分治处理凸包上的边，寻找最优分割点
ii e[N];
int cnt, b[N];
void merge(int l, int r) {
    e[++cnt] = {b[l], b[r]};
    if (l+1 == r) return;
    node2 mx(1, 0);
    int pos = -1;
    for (int i = l+1; i < r; ++i)
        if (cot(p[b[l]], p[b[i]], p[b[r]]) < mx) {
            mx = cot(p[b[l]], p[b[i]], p[b[r]]);
            pos = i;
        }
    merge(l, pos); merge(pos, r);
}

///直线是否能分离两个点集
int n, m;
bool check(int l, int r) {
    node a = p[l], b = p[r];
    node2 ls(-1, 0), rs(1, 0);
    for (int i = 1; i <= n; ++i) {
        node2 w = cot(a, p[i], b);
        ll d = (a - p[i]) ^ (b - p[i]);
        if (d > 0) ls = max(ls, w);
        else if (d < 0) rs = min(rs, w);
        if (ls > rs) return false;
    }
    for (int i = 1; i <= m; ++i) {
        node2 w = cot(a, q[i], b);
        ll d = (a - q[i]) ^ (b - q[i]);
        if (d > 0) rs = min(rs, w);
        else if (d < 0) ls = max(ls, w);
        else if (contain(a, q[i], b)) return false;
        if (ls >= rs) return false;
    }
    return true;
}

///Graham扫描法求凸包
///上下凸包分别处理
///对每条边尝试分离两个点集
int tot, s[N], t;
bool solve() {
    tot = cnt = 0;
    sort(p + 1, p + n + 1);
    s[t=1] = 1;
    for (int i = 2; i <= n; ++i) {
        while (t > 1 && ((p[i]-p[s[t-1]])^(p[s[t]]-p[s[t-1]])) >= 0)
            t--;
        s[++t] = i;
    }
    for (int i = 1; i <= t; ++i) b[++tot] = s[i];
    s[t=1] = 1;
    for (int i = 2; i <= n; ++i) {
        while (t > 1 && ((p[i]-p[s[t-1]])^(p[s[t]]-p[s[t-1]])) <= 0)
            t--;
        s[++t] = i;
    }
    for (int i = t - 1; i > 1; --i) b[++tot] = s[i];
    merge(1, tot);
    for (int i = 1; i <= cnt; ++i)
        if (check(e[i].first, e[i].second))
            return true;
    return false;
}


int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> p[i];
    for (int i = 1; i <= m; ++i) cin >> q[i];
    if (n == 1 || m == 1) {//单点情况
        cout << "YES\n";
        return 0;
    }
    ///旋转卡壳
    cout << (solve() || (swap(p, q), swap(n, m), solve())
        ? "YES\n" : "NO\n");
    return 0;
}