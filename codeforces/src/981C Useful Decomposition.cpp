//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
N = 100007：数组大小。
n：结点总数。
cnt[i]：结点 i 的度数（邻接边数）。
v[N]：用于存储度数为 1 的叶子结点。
tot：叶子结点计数
while (cin >> n)：多组测试数据，读不到输入就结束。
tot = 0：每组重置叶子计数。
读入 n-1 条边（树有 n-1 条边），每条边两端 a,b 的度数各 +1。
由于 tot=0 但没有清空 cnt，注意：多组数据之间 cnt 未清零，这是本代码的一个隐患（若多组数据可能出错，见补充说明）
遍历所有结点：
度数 ≥ 3 的结点：称其为"分叉点"。若出现多个度数 ≥3 的结点（x 已被占用），则输出 "No" 并退出这组（f=false，break）。
度数 == 1 的结点：记录到 v[]，tot++（叶子列表）。
结论逻辑：
一棵树中至多只能有 1 个度数 ≥3 的分叉点，否则判 No（代表树超过"毛毛虫/星形中心"结构）
若 f 为 false（前面已 No），直接 continue 处理下一组。
否则输出 "Yes\n"：
x == -1 情况（没有任何度数≥3 的结点）：说明树是一条纯链（路径），此时只需 tot 个叶子……实际这里直接输出 1 条边 v[0] v[1]（构造一个覆盖两个叶子的边，作为平凡解，比如删边方案的某种表达）。
有分叉点 x：输出 tot 条边，每条都是 x 连到一个叶子 v[i]——即以分叉点 x 为中心连向所有叶子
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+7;

int n, cnt[N], v[N], tot;
int main() {
    fast;
    while (cin >> n) {
        tot = 0; memset(cnt, 0, sizeof(cnt));
        for (int i = 0, a, b; i < n-1; i++) {
            cin >> a >> b;
            cnt[a]++, cnt[b]++;
        }
        int x = -1;
        bool f = true;
        for (int i = 1; i <= n; i++) {
            if (cnt[i] >= 3) {
                if (x == -1) x = i;
                else { cout << "No\n"; f = false; break; }
            }
            if (cnt[i] == 1) v[tot++] = i;
        }
        if (!f) continue; cout << "Yes\n";
        if (x == -1) cout << "1\n" << v[0] << ' ' << v[1] << '\n';
        else {
            cout << tot << '\n';
            for (int i = 0; i < tot; i++) cout << x << ' ' << v[i] << '\n';
        }
    }
    return 0;
}