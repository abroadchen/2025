//
// Created by Psy.C on 2026/10/11.
//
/**
k 个字符串，n 为每个长度。
a[i][c]：记录第 i 个字符串中字符 c 的出现次数（a[i][s[i][j]-'a'+1]++ 统计每个字符次数，下标 1..26 对应 'a'..'z'）
读入每个字符串，统计其每个字符出现次数，并存入 a[i]。
校验：如果第 i 串的某种字符统计数与第 1 串不同（a[i][j] != a[1][j]），说明字符构成不一致，无法通过交换互相转化，直接输出 -1。
b[i] = 第 i 个字符串与 s[1] 在逐位置对比下不同的位置个数（即汉明距离）。注意：s[1] 与自己比较时 b[1]=0，i 从 1 开始但 b[1]=0 无影响
flg：如果 s[1] 中有某个字符出现次数 ≥ 2，flg=1。
含义：当交换的两个位置恰好在不同字符串里对应相同的字符时，b（汉明距离）可以不变。存在重复字符才可能实现"交换后完全不变"的情形，供后面判断用
二重循环枚举 s[1] 中要交换的两个位置 i、j（i<j）。
对每个字符串 s[p]（p=2..k），复制其当前汉明距离 b[p] 到 c[p]，然后模拟"把 s[1] 在 i、j 处交换"后，计算 s[p] 与 s[1] 的新汉明距离：
位置 i：原来 s[1][i] 与 s[p][i] 不同 → 交换后该位变成 s[1][j]，比较 s[1][j] 与 s[p][i]。
位置 j：类似处理。
代码这四行是在增量更新汉明距离：把 i 位和 j 位按交换前后与 s[p] 对应位的异同进行调整。
可行判断：交换后，s[p] 与 s[1] 的汉明距离必须是：
c[p] == 0（完全一致）且 flg（存在重复字符）——或
c[p] == 2（两个位置仍不同，说明这两个位置在各自串里匹配上了）——
才视为该串与交换后的 s[1] 相容。否则 f=0 表示这个交换候选失败。
若所有 s[p]（p=2..k）都相容（f 仍为 1），说明找到一组合法交换：swap(s[1][i], s[1][j]) 后输出 s[1] 并结束。
若全部候选都失败，最后输出 -1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=j; i<=k; ++i)
using namespace std;

constexpr int N = 5e3+5;

int k, n, a[N][27], b[N], flg, c[N];
string s[N];
int main() {
    fast;
    cin >> k >> n;
    rep(i,1,k) {
        cin >> s[i];
        rep(j,0,n-1) a[i][s[i][j]-'a'+1]++;
        rep(j,1,26) if (a[i][j] != a[1][j]) return cout << -1, 0;
        rep(j,0,n-1) if (s[1][j] != s[i][j]) b[i]++;
    }
    rep(i,1,26) if (a[1][i] >= 2) flg = 1;
    rep(i,0,n-2) rep(j,i+1,n-1) {
        int f = 1;
        rep(p,2,k) c[p] = b[p];
        rep(p,2,k) {
            if (s[1][i] != s[p][i]) c[p]--;
            if (s[1][j] != s[p][i]) c[p]++;
            if (s[1][i] != s[p][j]) c[p]++;
            if (s[1][j] != s[p][j]) c[p]--;
            if (c[p] == 0 && flg) continue;
            if (c[p] == 2) continue;
            f = 0; break;
        }
        if (f) {
            swap(s[1][i], s[1][j]);
            return cout << s[1], 0;
        }
    }
    cout << -1;
    return 0;
}