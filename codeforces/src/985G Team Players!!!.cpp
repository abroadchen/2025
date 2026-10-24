//
// Created by Psy.C on 2026/10/24.
//

/**
真正学会的起点..
a[0..2]：三个线性系数（权函数的权重）。
d[u]：每个点的度数。
r[i]：第 i 条边 (u,v)。
e[u]：邻接表。
ans：累计答案（ull 防溢出）
读入系数 a、m 条边，并统计每个点度数 d
这里枚举中间点 i，统计以 i 为"中位"的三元组。假设三元组按 (x<y<z) 排序，i 作为某个位置的元素，枚举它出现的所有可能组合：
i 作为最小值 x=i：比 i 大的数有 n-1-i 个，从中任选 2 个作为 y,z，组合数 C(n-1-i, 2)，贡献 a[0]*i（i 是 x）。
i 作为中间值 y=i：一个小于 i（i 个），一个大于 i（n-1-i 个），组合 i*(n-1-i)，贡献 a[1]*i。
i 作为最大值 z=i：两个小于 i 的数，从 i 个中选 2 个，C(i,2)，贡献 a[2]*i。
求和得到不考虑图边、纯数字的三元组权值和（所有无序三元组 (x,y,z) 的
a
0
x
+
a
1
y
+
a
2
z
a
0
​
 x+a
1
​
 y+a
2
​
 z）
对每条边 (x,y)（规定 x<y），考虑所有包含这条边的三元组中，需要减去的"不合法"贡献（这部分与图的边相关，可能是减去"不该算的"）。
三个式子分别处理三元组中第 3 个点相对于 x、y 的位置：
第三个点 < x：有 (x-1) 个候选（组合 C(x-1,2)? 这里标注为补全重排）。
第三个点在 x、y 之间：(y-x-1) 个。
第三个点 > y：(n-y-1) 个。
每式用等差数列求和公式 1ull*.../2 表示组合数，乘以对应权。
（这是容斥：从"所有三元组"中扣除与图中边有关的过度计数。）
建无向邻接表 e。
对每个点 i，将其邻居排序，然后线性扫描统计包含 i 且与图中边相关的三元组贡献（利用累加和 s0/s1 技巧把 O(deg²) 变 O(deg)）：
j 是比 i 小的邻居：作为 (j, 中间?, i) 组合累加。
j 是比 i 大的邻居：作为另一类组合累加。
这是经典的"枚举中间顶点统计经过它的三元组/角"，用前缀和优化
度数分治 / 重定向：清空邻接表，对每条边按"度数更大者"定向（tie 比较保证从度数小的指向度数大的，消除歧义），把边存成有向图 e（度数小→大）。
统计三角形（三元环）‍：用 v[] 标记技巧枚举所有三元环 (i,j,k)（图中三个点两两相连的三角形）：
对每个 i，先给所有邻居 j 打上标记 v[j]=i。
再遍历 i 的邻居 j 的邻居 k，若 v[k]==i 则 (i,j,k) 构成三元环。
对每个三元环，将其三个点排序后从 ans 中扣掉 a[0]*b[0]+a[1]*b[1]+a[2]*b[2]（容斥修正）。
重定向保证了每个三元环只会被枚举一次（从度数最小点出发），总复杂度 O(m√m) 级别
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ull unsigned long long
#define rep(i,n) for (int i=1; i<=(n); ++i)
#define ii pair<int,int>
using namespace std;

constexpr int N = 2e5+1;

int n, m, d[N], v[N];
ull a[3], ans;
ii r[N];
vector<int> e[N];
int main() {
    fast;
    cin >> n >> m;
    for (ull &i : a) cin >> i;
    rep(i,m) {
        cin >> r[i].first >> r[i].second;
        ++d[r[i].first], ++d[r[i].second];
    }
    for (int i = 0; i < n; ++i) {
        ans += a[0]*i*(1ull*(n-1-i)*(n-2-i)/2);
        ans += a[1]*i*i*(n-1-i);
        ans += a[2]*i*(1ull*i*(i-1)/2);
    }
    rep(i,m) {
        int x = r[i].first, y = r[i].second;
        x > y && (swap(x, y), 0);
        ans -= a[0]*(1ull*(x-1)*x/2)+(a[1]*x+a[2]*y)*x;
        ans -= a[1]*(1ull*(x+y)*(y-x-1)/2)+(a[0]*x+a[2]*y)*(y-x-1);
        ans -= a[2]*(1ull*(y+n)*(n-y-1)/2)+(a[0]*x+a[1]*y)*(n-y-1);
    }
    rep(i,m) {
        e[r[i].first].push_back(r[i].second);
        e[r[i].second].push_back(r[i].first);
    }
    for (int i = 0; i < n; ++i) {
        ranges::sort(e[i]);
        int c0 = 0, c1 = 0; ull s0 = 0, s1 = 0;
        for (int j : e[i]) {
            if (j < i) {
                ans += a[0]*s0+(a[1]*j+a[2]*i)*c0;
                ++c0, s0 += j;
            } else {
                ans += a[0]*s0+(a[1]*i+a[2]*j)*c0;
                ans += a[1]*s1+(a[0]*i+a[2]*j)*c1;
                ++c1, s1 += j;
            }
        }
    }
    for (int i = 0; i < n; ++i) e[i].clear();
    rep(i,m) {
        if (tie(d[r[i].first], r[i].first) > tie(d[r[i].second], r[i].second))
            swap(r[i].first, r[i].second);
        e[r[i].first].push_back(r[i].second);
    }
    fill_n(v, n, -1);
    for (int i = 0; i < n; ++i) {
        for (int j : e[i]) v[j] = i;
        for (int j : e[i]) for (int k : e[j]) if (v[k] == i) {
            int b[3] = {i, j, k};
            sort(b, b+3);
            ans -= a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
        }
    }
    cout << ans;
    return 0;
}