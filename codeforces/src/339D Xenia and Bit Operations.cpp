//
// Created by Psy.C on 2026/1/12.
//
/**
* tr：线段树数组，存储计算结果
a：原始输入数组
*rt：当前节点编号
l, r：当前节点对应的区间范围
x：当前层级的标识（从n开始递减）
*递归构建左右子树
关键点：根据 x % 2 决定合并操作
如果 x 为奇数：使用按位或（OR）操作
如果 x 为偶数：使用按位异或（XOR）操作
 *
*x：要更新的位置
val：新值
p：当前层级标识
*找到叶子节点并更新值
递归更新路径上的所有节点
同样根据层级奇偶性选择操作符
 *
*n：树的高度，叶子节点数量为 2^n
q：查询数量
*对于每个查询，更新位置 x 为值 y
输出根节点的值
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100006
using namespace std;

ll tr[N<<2], a[N<<2];
void build(const ll rt, const ll l, const ll r, const ll x) {
    if (l == r) { tr[rt] = a[l]; return; }
    const ll mid = (l + r) >> 1;
    build(rt<<1, l, mid, x - 1);
    build(rt<<1|1, mid + 1, r, x - 1);
    if (x % 2) tr[rt] = tr[rt<<1] | tr[rt<<1|1]; else {
        tr[rt] = tr[rt<<1] ^ tr[rt<<1|1];
    }
}

void update(const ll rt, const ll l, const ll r, const ll x, const ll val, const ll p) {
    if (l > x || r < x) return;
    if (l == x && r == x) { tr[rt] = val; return; }
    const ll mid = (l + r) >> 1;
    update(rt<<1, l, mid, x, val, p - 1);
    update(rt<<1|1, mid + 1, r, x, val, p - 1);
    if (p % 2) tr[rt] = tr[rt<<1] | tr[rt<<1|1]; else {
        tr[rt] = tr[rt<<1] ^ tr[rt<<1|1];
    }
}


int main() {
    fast;
    ll n, q, x, y; cin >> n >> q;
    const ll lim = 1<<n;
    for (int i = 1; i <= lim; ++i) cin >> a[i]; build(1, 1, lim, n);
    while (q--) {
        cin >> x >> y;
        update(1, 1, lim, x, y, n);
        cout << tr[1] << '\n';
    }
    return 0;
}