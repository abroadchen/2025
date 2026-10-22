//
// Created by Psy.C on 2026/10/22.
//
/**
node：保存原始值 num、原下标 id、以及压缩后的"排名" rk（稍后用于数值离散化）。
a 存原数组的值；d 用作 DP 数组；ans 最长长度；st 最长序列的起始值
读入数组，同时记录每个元素的值和原下标，然后按值排序
排序后按顺序扫描：

若当前值与上一个相同 → 排名相同（rk 相同）→ 保证"值相等 → 排名相等"。
若当前值 = 上一个值 + 1（相邻）→ 排名 +1 → 保证"值相邻 → 排名相邻"。
否则（有跳跃）→ 排名 +2 → 保证"值不相邻 → 排名也不相邻（中间留空）"。
最后把每个元素的 num 替换成自己的 rk，完成压缩。这样做的意义：让"数值连续 +1"的连续子序列，在离散化后的排名上也正好表现为连续递推（rk, rk+1, rk+2…），便于 DP
从后往前遍历。
状态转移：d[x] = d[x+1] + 1。含义：以值 x 结尾的"连续递增子序列"最长长度 = 以值 x+1 结尾的 + 1。
因为要构造连续递增（值差 1），所以 dp 依赖下一个值 x+1 的最长长度。
每次更新若出现更长答案，记录起始值 st = a[i] 和长度 ans。
由于从后往前，d[a[i]+1] 已经在更早（更靠后）的遍历中算好，保证转移正确
先输出最长长度 ans。
再从头遍历原数组，从起始值 st 开始，每遇到 a[i] == st 就输出下标 i 并把 st 递增（期待下一个值 st+1），从而输出整条子序列在原数组中的位置
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e5+5, M = 4e5+5;

struct node {
    int num, id, rk;
    bool operator<(const node &o) const {
        return num < o.num;
    }
} tr[N];

int a[M], d[M], ans, st;
int main() {
    fast;
    int n, i; cin >> n;
    for (i = 1; i <= n; i++) { cin >> a[i]; tr[i].num = a[i]; tr[i].id = i; }
    sort(tr+1, tr+n+1);
    for (i = 1; i <= n; i++) {
        if (tr[i].num == tr[i-1].num) tr[i].rk = tr[i-1].rk;
        else if (tr[i-1].num+1 == tr[i].num) tr[i].rk = tr[i-1].rk+1;
        else tr[i].rk = tr[i-1].rk+2;
    }
    for (i = 1; i <= n; i++) a[tr[i].id] = tr[i].rk;
    for (i = n; i >= 1; i--) {
        d[a[i]] = d[a[i]+1] + 1;
        if (ans < d[a[i]]) { st = a[i]; ans = d[a[i]]; }
    }
    cout << ans << '\n';
    for (i = 1; i <= n; i++) if (a[i] == st) cout << i << ' ', st++;
    cout << '\n';
    return 0;
}