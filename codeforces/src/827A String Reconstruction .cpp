//
// Created by Psy.C on 2026/9/24.
//
/**
s[N]：存储每一段子串（下标 1..n）。
cnt[x]：记录位置 x 当前被"哪一段"（s 的下标）所覆盖。0 表示未被覆盖。
len：目标串的最大长度（记录出现的最大位置坐标）
每组：读入子串 s[i] 和它出现的起始位置个数 k。
对每个起始位置 x：如果当前位置 x 当前指向的段（cnt[x]）比 s[i] 短，就用 s[i] 覆盖（记录 cnt[x] = i）。
同时维护 len 为所有放置位置的最大值，作为输出长度的上界。
这里只记录了每一段的起点位置 x 的归属，但段本身会覆盖连续 s[i].size() 个位置——所以后续输出时需要结合长度一起处理（这也是为什么输出循环里有复杂的跳跃逻辑）
遍历目标串位置 1..len：
若 cnt[i] == 0：该位置没有段覆盖，输出 'a'。
否则取 cnt[i] 对应的段（该起点处的最长段），从其中 j=0 开始连续输出：
但需要判断：如果后续某个位置 i+j 被一段更长的段覆盖（s[cnt[i+j]].size() + j > s[cnt[i]].size()），说明后面有更长的段要"接管"，就停止并跳过。
否则输出 s[cnt[i]][j]（最长段在此位置的字符）。
i += j-1：跳到已输出部分的末尾，外层 for 的 ++i 再前进一位。
核心思想：优先用每个起点处最长的段，一段一段"尽量往后铺"，遇到更长段接管就切换，没有覆盖的空位补 'a'。这是一种贪心的覆盖/拼接输出策略，保证了最终结果尽量使用最长段，空缺填补 'a'
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e6+5;
string s[N];
int cnt[10*N], len(-1);
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1, k; i <= n; ++i) {
        cin >> s[i] >> k;
        for (int j = 1, x; j <= k; ++j) {
            cin >> x;//本段要放置的起始位置（1-based）
            if (s[cnt[x]].size() < s[i].size())
                cnt[x] = i;//如果更长的段覆盖该起点，则取代
            len = max(len, x);//更新最大位置
        }
    }
    for (int i = 1; i <= len; ++i) {
        if (!cnt[i]) cout << 'a';//该位置没被任何段作为起点覆盖 → 补 'a'
        else {
            int j;
            for (j = 0; j < s[cnt[i]].size(); ++j) {
                if (s[cnt[i+j]].size() + j > s[cnt[i]].size()) break;
                cout << s[cnt[i]][j];//输出最长段在位置 i 的字符
            }
            i += j-1;//跳过这个最长段已经输出的部分
        }
    }
    return 0;
}