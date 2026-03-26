//
// Created by Psy.C on 2026/3/26.
//
/**
读入数组元素
如果相邻元素相等，将它们合并到同一个连通分量
find(i)和find(i-1)找到各自的根节点
如果根节点不同，则合并（将u的根指向v的根）

循环处理m个查询
每个查询包含：区间[l,r]和目标值x
从右端点r开始向左搜索
find(t)：找到t所在连通分量的根节点
t = find(t) - 1：跳过整个连通分量（因为连通分量内元素相同）
如果找到不等于x的元素，输出位置并标记flag=1
如果整个区间都符合要求，输出-1
时间复杂度：近似O(m·α(n))，其中α是阿克曼函数的反函数 空间复杂度：O(n)

O(1) < O(α(n)) < O(log log n) < O(log n) < O(√n) < O(n) < O(n log n) < O(n²)
n范围	α(n)值
n ≤ 4	1
4 < n ≤ 20	2
20 < n ≤ 2^65536	3
更大值	4

阿克曼函数A(m,n)是一个快速增长的递归函数
A(0, n) = n + 1
A(m, 0) = A(m-1, 1)  (当m > 0)
A(m, n) = A(m-1, A(m, n-1))  (当m > 0, n > 0)

α(n) = min{k ≥ 1 : A(k, k) ≥ n}
α(n)是使得A(k,k) ≥ n的最小k值

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+5;

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int n, m, a[N];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] == a[i-1]) {
            int u = find(i), v = find(i-1);
            if (u != v) fa[u] = v;
        }
    }
    for (int i = 1; i <= m; ++i) {
        int flag = 0, l, r, x;
        cin >> l >> r >> x;
        int t = r;
        while (l <= t) {
            if (a[t] != x) {
                cout << t << '\n';
                flag = 1;
                break;
            }
            t = find(t) - 1;
        }
        if (flag == 0) cout << "-1\n";
    }
    return 0;
}