//
// Created by Psy.C on 2026/10/18.
//
/**
vector<int> q[N];   // q[i] 存第 i 段当前已收集的下标（1-based 位置）
int cnt;            // 当前"正在开放的段数"（还需要补 1 的段数）
int mx;             // 过程中开放的段数峰值
遇到 0：把它放进一段。由于 0 必须排在段的开头，每来一个 0 就意味着"新增一段待用 0 开头、等 1 来补尾"，所以 cnt++（开放段数 +1），下标放进 q[cnt-1]（即最新段）。

遇到 1：它应该被补进某段末尾。选择哪段？代码 --cnt 选的是当前开放段中最靠后的一段（q[--cnt]），即拿"最迟开的 0 段"来配对。因为 0 先到先开段，1 来时用后开（最危）的段配对，能最大化前段留给更多 1 的余量。

若 cnt==0：即此刻没有任何"已开且还没收尾"的 0 段可补 1（等价于出现"先 1 后 0"或 1 比其前缀 0 多），直接输出 -1
处理结束后要求 cnt == mx。

含义：mx 是开放段数峰值，cnt 是最终剩余开放段数。
如果峰值 > 最终段数，说明某段先被用 1 收尾后，又来了新的 0 并继续在同一段展开，即出现了"0 出现在 1 之后"的段（如 0 1 0 配成一段，0 在 1 后）→ 非法 → 输出 -1。
cnt==mx 才能保证所有段都是严格"先 0 后 1"且数量可由输出。
输出 cnt（段落数），随后每行输出该段的下标集合（段内按收集顺序即下标递增）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
using namespace std;

constexpr int N = 2e5+5;
char s[N];
int l, cnt, mx;
vector<int> q[N];
int main() {
    fast;
    cin >> s; l = strlen(s);
    rep(i,l) {
        if (s[i] == '0') q[cnt++].push_back(i+1);
        else {
            if (cnt == 0) { cout << -1 << '\n'; return 0; }
            q[--cnt].push_back(i+1);
        }
        mx = max(mx, cnt);
    }
    if (cnt != mx) { cout << -1 << '\n'; return 0; }
    cout << cnt << '\n';
    rep(i,cnt) {
        cout << q[i].size();
        for (int j : q[i]) cout << ' ' << j;
        cout << '\n';
    }
    return 0;
}