//
// Created by Psy.C on 2026/3/25.
//
/**
v存储每行的总和，id存储原始行号
n为矩阵大小，ans数组存储每行的排名结果

O(n²) 用于读入和求和
O(n log n) 用于排序
总体：O(n²)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 55;

struct node {
    int v, id;
    bool operator<(const node &o) const {
        return v < o.v;
    }
} a[N];///节点数组

ll n, ans[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1, x; j <= n; ++j) {
            cin >> x;//读入矩阵元素
            a[i].v += x;//累加到第i行的总和
        }
        a[i].id = i;//记录原始行号
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) ans[a[i].id] = i;//将排名结果存入ans数组
    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';//输出每行的排名
    return 0;
}