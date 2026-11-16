//
// Created by Psy.C on 2026/11/16.
//

/**
真正学会的起点..
读入一个整数 n，然后 n 减 2。这通常是把题目给的"点数/边数/某些数量"调整成内部需要的基数
开一个长度 8 的数组 a。
初始：a[0] = 1，a[N-1] = a[7] = 2，其余为 0
循环 n 次，每次从下标 0 开始找到第一个 a[i] < 8 的位置，把它 +1，然后 n 减 1。
效果：相当于把 (n 减掉的这部分) 以"进位"的方式分配到 a 里。注意这里的进位只在 a[i] < 8 时加，即每个元素最大到 8（N）。
一句话：a 数组被填充成某种"权重/容量分配"，总和为 1 + 2 + n（初始 3 + 循环加的 n）
c 是一个"补位/辅助"变量，初始 0。
ans 存放要输出的 (行索引, 位置号) 对
对每个 a[i] > 0 的行，先输出 (i, c) 这一对，并且该行的"剩余量"减 1（因为已经用掉一个位置）。
这里的 (i, c) 是每行的"起始锚点"。
接着进入分类讨论，分四种情况：

情况 A：a[i] == N-1（该行还剩 7 个空格）且 i == N-1
当这行是"最后一行"（下标 N-1 = 7），且剩余量恰好等于 7（N-1），就把这行除 c 之外所有 7 个位置全输出
情况 B：a[i] == N-1 且 i != N-1
否则（不是最后一行且剩余 7 格），从 N-1 到 0 倒序输出除 c 外的所有位置。
输出完把 c 取反（c = !c，即 0↔1），用于下一行的辅助位切换
情况 C：a[i] < N-1 且 i == N-1
最后一行、剩余量 < 7：从前往后输出位置，但至少要剩 1（条件 a[i] > 1），每输出一个 a[i] 减 1，直到把剩余量消耗到 1。
最后固定输出 (i, N-1)（最后一个位置），把最后的 1 用掉
情况 D：a[i] < N-1 且 i != N-1
非最后一行的普通补充：从前往后输出尚未满的位置，每输出一个 a[i] 减 1。
当该行被填满（a[i] == 0）时，把 c 更新为当前最后使用的位置 j——这样 c 总能跟踪"上一个用到的列"，避免下一行重复用同一列。
遍历所有生成的 (i, j) 对。
first + 'a' → 把行下标 0..7 变成字母 a..h。
second + 1 → 把列下标 0..7 变成数字 1..8。
最后一项后面换行，其余用空格分隔。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n;++i)
#define ii pair<int, int>
#define vi vector<int>
using namespace std;

constexpr int N = 8;

int main() {
    fast;
    int n; cin >> n; n -= 2;
    vi a(N); a[0] = 1; a[N-1] = 2;
    while (n) {
        rep(i,N) if (a[i] < N) { ++a[i]; break; }
        --n;
    }
    int c = 0; vector<ii> ans;
    rep(i,N) if (a[i]) {
        ans.emplace_back(i,c); --a[i];
        if (a[i] == N-1) {
            if (i == N-1) { rep(j,N) if (j != c) ans.emplace_back(i,j); }
            else {
                for (int j = N-1; ~j; --j) if (j != c) ans.emplace_back(i,j);
                c = !c;
            }
        } else {
            if (i == N-1) {
                for (int j = 0; j < N && a[i] > 1; ++j) if (j != c) {
                    ans.emplace_back(i,j); --a[i];
                }
                ans.emplace_back(i,N-1);
            } else {
                for (int j = 0; j < N && a[i]; ++j) if (j != c) {
                    ans.emplace_back(i,j); --a[i];
                    if (!a[i]) c = j;
                }
            }
        }
    }
    rep(i,ans.size())
        printf("%c%d%c", ans[i].first + 'a', ans[i].second + 1, i == ans.size() - 1 ? '\n' : ' ');
    return 0;
}