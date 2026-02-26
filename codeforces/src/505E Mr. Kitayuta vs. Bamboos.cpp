//
// Created by Psy.C on 2026/2/25.
//
/**
d：天数/时间
id：节点编号
重载小于运算符，实现最大堆（d越大优先级越高）
h[M]：堆数组
sz：堆大小
push()：向堆中添加元素并维护堆性质
pop()：弹出堆顶元素并维护堆性质
top()：获取堆顶元素

c[N]：每个节点的操作次数计数
n：节点数
m：天数
k：每天最多操作数
a[N]：每个节点的增长率
h[N]：每个节点的初始值
p：每次操作的增益

检查值x是否可行
预处理：将不满足条件的节点加入堆中：
x - a[i]*m < h[i]：经过m天自然增长后仍不足
x/a[i]：需要多少天才能达到x
模拟m天，每天最多k次操作
取出堆顶元素：
如果所需天数小于当前天数，说明无法及时处理，返回false
执行操作：
增加该节点的操作次数
如果仍然不满足条件，重新计算并加入堆
如果堆为空，说明所有节点都能满足条件
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int read() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
constexpr int N = 1e5+1;
struct node {
    int d, id;
    bool operator<(const node &o) const {
        return d > o.d;
    }
};
constexpr int M = 2e5+1;
struct Heap {
    node h[M];
    int sz;
    void clear() { sz = 0; }
    bool empty() const { return !sz; }
    void push(const node x) {
        h[++sz] = x;
        push_heap(h + 1, h + 1 + sz);
    }
    node pop() {
        return pop_heap(h + 1, h + 1 + sz), h[sz--];
    }
    node top() const { return h[1]; }
} H;

int c[N], n, m, k;
ll a[N], h[N], p;
bool ok(const ll x) {
    H.clear(), memset(c, 0, sizeof(c));
    for (int i = 1; i <= n; ++i)
        if (x - a[i]*m < h[i])
            H.push(node(x/a[i], i));
    for (int i = 1; !H.empty() && i <= m; ++i)
        for (int j = 1; !H.empty() && j <= k; ++j) {
            auto [d, id] = H.pop();
            if (d < i) return false;
            ++c[id];
            if (x + c[id]*p - a[id]*m < h[id])
                H.push(node((x+c[id]*p)/a[id], id));
        }
    return H.empty();
}

ll l = 0, r, mid, ans;
int main() {
    n = read(), m = read(), k = read(), p = read();
    for (int i = 1; i <= n; ++i) {
        h[i] = read(), a[i] = read();
        r = max(r, h[i]+a[i]*m);
    }
    while (l <= r) {
        ok(mid = (l + r) >> 1) ? ans = mid, r = mid - 1 : l = mid + 1;
    }
    printf("%lld\n", ans);
    return 0;
}