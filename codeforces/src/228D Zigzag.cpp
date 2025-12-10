//
// Created by Psy.C on 2025/12/10.
//
/*
*b[N]：原始输入数组
a[N]：维护的数组（用于更新操作）
 *
*树状数组的单点更新函数：
在tr数组的pos位置增加v值
从pos位置开始，沿着父节点路径向上更新
每次移动到pos + lb(pos)位置
*树状数组的前缀和查询函数：
计算tr数组前pos项的和
从pos位置开始，沿着子节点路径向下累加
每次移动到pos - lb(pos)位置
 *
*声明三维数组tr，用于存储多个树状数组：
第一维[7]：支持z值从0到6（实际使用2到6）
第二维[10]：每个z值对应最多2*(z-1)个模数组
第三维[N]：每个树状数组的实际存储空间
 *
*查询函数，计算区间[l,r]内的特殊加权和：
对于给定的参数z，遍历相关的2*(z-1)个树状数组
计算每个树状数组在区间[l,r]上的和值val
根据位置j和模数mod计算权重系数p
根据p的值应用不同的权重规则：
p==0: 权重为2
p<=z: 权重为p
p>z: 权重为(2*z-p)
累加所有加权值到res
*更新函数，在位置pos设置新值v：
对于z从2到6，更新相应的树状数组
在对应模数的位置添加差值(v - a[pos])
更新a[pos]为新值v
 *
 *O(log n)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define rep(i,n) for(int i=1;i<=n;++i)
#define N 100010
using namespace std;

int n;
ll b[N], a[N];
int lb(const int x) { return x & (-x); }

void add(ll tr[], int pos, const int v) {
    for (; pos <= n; pos += lb(pos)) tr[pos] += v;
}

ll sum(const ll tr[], int pos) {
    ll v = 0;
    for (; pos >= 1; pos -= lb(pos)) v += tr[pos];
    return v;
}

ll tr[7][10][N];
ll query(const int l, const int r, const int z) {
    ll res = 0;
    for (int j = 0; j < 2*(z-1); ++j) {
        const ll val =  sum(tr[z][j], r) - sum(tr[z][j], l-1);
        const int mod = 2 * (z - 1),
        p = (j - l % mod + 1 + mod) % mod;
        if (p == 0) res += 2 * val;
        else if (p <= z) res += p * val;
        else res += (2 * z - p) * val;
    }
    return res;
}


void update(const int pos, const int v) {
    for (int i = 2; i <= 6; ++i)
        add(tr[i][pos%(2*(i-1))], pos, static_cast<int>(v - a[pos]));
    a[pos] = v;
}

int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> b[i];
    rep(i,n) update(i, static_cast<int>(b[i]));//初始化树状数组
    int m; cin >> m;
    while (m--) {
        int op; cin >> op;
        if (op == 1) {
            int p, v; cin >> p >> v;
            update(p, v);
        } else {
            int l, r, z; cin >> l >> r >> z;
            cout << query(l, r, z) << '\n';
        }
    }
    return 0;
}