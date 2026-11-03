//
// Created by Psy.C on 2026/11/3.
//

/**
真正学会的起点..
a、b 是两个人各自要分到的值，s = a+b 是总和要分解的量
目标：把 s 拆成尽量多的互不相等的块，每块不大不小，整体可表示。
每次取当前递增大小 i；如果剩余 s 已经小于 i（不够再生成更大的块），就把最后一块直接取成余额 s。
得到的块序列 c[1..num]，这些块互不相同，总和等于最初 a+b
从大到小（因为 i 从 num 递减）遍历所有块。
只要当前块 c[i] 不超过 a 的剩余量，就把它分给 a：v 记录、vis[i] 标记"已被 a 拿走"、a 减少。
a 一旦归零立即停止（贪心能凑出 a，因为块足够小且足够多）
第一行：a 分到的块数量，然后列出这些块。
第二行（用 \n 分隔）：b 分到的块数量 = num - v.size()，然后列出未被 a 拿走的剩余块
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+1;

int a, b, s, c[N], num;
vector<int> v;
bool vis[N];
int main() {
    fast;
    cin >> a >> b; s = a + b;
    for (int i = 1; i <= s; i++) {
        if (i > s) i = s;
        c[++num] = i;
        s -= i;
    }
    for (int i = num; i >= 1; i--) {
        if (c[i] <= a) {
            a -= c[i];
            v.push_back(c[i]); vis[i] = 1;
        }
        if (!a) break;
    }
    cout << v.size() << '\n';
    for (int i : v) cout << i << ' ';
    cout << '\n' << num-v.size() << '\n';
    for (int i = 1; i <= num; i++) if (!vis[i]) cout << c[i] << ' ';
    return 0;
}