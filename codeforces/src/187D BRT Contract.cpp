//
// Created by Psy.C on 2025/12/2.
//
/*
*n: 数组大小/节点数
g: 基础参数
p: 模数相关参数
q: 查询数量
*sum[N]: 前缀和数组
suf[N]: 后缀计算数组
 *f: map容器，用于维护区间信息
 *b, e: map迭代器，用于区间操作
 *
*reduce函数：将x标准化到[0, p)范围内
x>>63 & p：如果是负数，加上p使其变为正数
*insert函数：在map中插入新区间[l,r]
找到覆盖区域，删除被覆盖的区间，插入新区间端点
*drive函数：计算从位置i到某个位置的"代价"
通过map找到合适的j位置，计算相应的值
 *
*从后往前处理每个位置：
计算区间范围[l,r]
计算后缀值suf[i]
根据l和r的大小关系插入区间到map中

p - reduce(x + sum[j])：从当前位置到某个基准点的距离
+ suf[j]：加上从当前位置到终点的额外成本


通过插入两个区间来表示这个环形区间：
第一个区间：[80, 100)
第二个区间：[0, 20]
 *
*预处理：O(n log n)
每次查询：O(log n)
总体：O(n log n + q log n)
 */
#include <iostream>
#include <map>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100010
using namespace std;

int n, g, p, q;
ll sum[N], suf[N];
map<int, int> f;
map<int, int>::iterator b, e;

inline ll reduce(ll x) { return x %= p, x + (x>>63 & p); }
void insert(const int i, const int l, const int r) {
    b = f.lower_bound(l); e = f.upper_bound(r);
    const int t = (--e)->second;
    f.erase(b, ++e);
    f[l] = i; f[r] = t;
}

ll drive(const int i, const ll x) {
    const int j = (--f.upper_bound(static_cast<int>(reduce(x))))->second;
    return sum[j] - sum[i] +
        (j == n ? 0 : p - reduce(x + sum[j]) + suf[j]);
}

int main() {
    fast;
    int i; ll l, r, t, ans = 0;
    cin >> n >> g >> p; ++n; p += g;
    for (i = 1; i <= n; ++i) {
        cin >> sum[i];
        sum[i] += sum[i-1];
    }
    f[0] = n;//设置边界条件
    for (i = n - 1; i; --i) {
        l = reduce(g - sum[i]), r = reduce(-sum[i]);
        suf[i] = drive(i, -sum[i]);
        l < r ? insert(i, static_cast<int>(l), static_cast<int>(r)) :
            (insert(i, static_cast<int>(l), p),
                insert(i, 0, static_cast<int>(r)));
    }
    for (cin >> q; q; --q) {
        cin >> t; ans = t + drive(0, t);
        cout << ans << '\n';
    }
    return 0;
}