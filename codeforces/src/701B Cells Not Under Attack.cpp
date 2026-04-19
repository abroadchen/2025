//
// Created by Psy.C on 2026/4/18.
//
/**
n: 网格大小（n×n网格）
k: 操作次数
x, y: 当前操作的坐标
nx, ny: 已染色的行数和列数
w[N]: 标记数组，记录每列是否被染色
h[N]: 标记数组，记录每行是否被染色
q: 队列，存储每次操作后的白色格子数量

循环处理k次操作
cin >> x >> y: 输入要染色的坐标(x,y)
if (!h[x]) { h[x] = true; nx++; }:
如果第x行未被染色
标记第x行为已染色
已染色行数nx加1
if (!w[y]) { w[y] = true; ny++; }:
如果第y列未被染色
标记第y列为已染色
已染色列数ny加1
q.push((ll)(n-nx)*(n-ny)):
(n-nx): 未染色的行数
(n-ny): 未染色的列数
(n-nx)*(n-ny): 剩余白色格子的数量（未被任何行或列覆盖的格子）
将结果压入队列

输出队列中除最后一个元素外的所有元素，用空格分隔
输出最后一个元素并换行
时间复杂度：O(k) 空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;
int n, k, x, y, nx, ny;
bool w[N], h[N];
queue<ll> q;
int main() {
    fast;
    cin >> n >> k;
    while (k--) {
        cin >> x >> y;
        if (!h[x]) { h[x] = true; nx++; }
        if (!w[y]) { w[y] = true; ny++; }
        q.push((ll)(n-nx)*(n-ny));
    }
    while (q.size() != 1) {
        cout << q.front() << ' '; q.pop();
    }
    cout << q.front() << '\n';
    return 0;
}