//
// Created by Psy.C on 2026/10/26.
//

/**
真正学会的起点..
a[N]：DFS 中记录每种数字实际用到的个数（digit x 用了 a[x] 个）。
f[N]：阶乘表 f[i] = i!。
ans：答案计数。
cnt[N]：原串中每个数字出现的次数（cnt[d] = 数字 d 出现次数）
到达叶子（枚举完 10 个数字）
当处理完数字 0-9，计算当前分配 a[0..9] 对应的排列数
多重集排列公式：总共用的字符数 tot 的全排列数 = tot! / ∏(每种数字个数)!
b) 减去"以 0 开头"的排列（若用了数字 0）
若数字 0 被用到（a[0]>=1），则"0 开头的排列"需去掉：固定 0 在首位，剩余 tot-1 个字符重排，0 剩下 a[0]-1 个，排列数 = (tot-1)! / ((a[0]-1)!·a[1]!···a[9]!)。
从 now 中减掉 p → 得到不以 0 开头的排列数
把当前分配得到的合法排列数累加进最终答案
对数字 x：可取个数 i 从 1 到它在原串中的出现次数 cnt[x]，分别设 a[x]=i 并递归下一个数字。
若 cnt[x]==0（原串没有这个数字，不能选它），直接空手递归 dfs(x+1)。
即：枚举"每个数字实际上用几个"（从 0 到 cnt[x]），并保证不会超过原串中该数字的数量

scanf("%s", s+1)：从下标 1 开始读入字符串。
strlen(s+1)：字符串长度 n（读取到 1-based）。
for(...) cnt[s[i]-'0']++：统计每个数字出现次数。
建阶乘表 f[i] = i!（f[0]=1）。
dfs(0)：从数字 0 开始 DFS。
输出 ans：最终的不以 0 开头的合法排列总数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=0; i<(n); i++)
#define int long long
using namespace std;

constexpr int N = 25;

int a[N], f[N], ans, cnt[N];
void dfs(int x) {
    if (x == 10) {
        int tot = 0, i;
        rep(i,10) tot += a[i];//总长度 tot = Σ a[i]
        int now = f[tot];
        rep(i,10) now/=f[a[i]];//now = tot! / (a[0]!·a[1]!···a[9]!)
        if (a[0] >= 1) {
            int p = f[tot-1]; p/=f[a[0]-1];
            for (i = 1; i < 10; i++) p/=f[a[i]];
            now -= p;
        }
        ans += now;
        return;
    }
    for (int i = 1; i <= cnt[x]; i++) { a[x] = i; dfs(x+1); }
    if (cnt[x] == 0) dfs(x+1);
}

char s[N];
signed main() {
    fast;
    scanf("%s", s+1);
    int n = strlen(s+1);
    for (int i = 1; i <= n; i++) cnt[s[i]-'0']++; f[0] = 1;
    for (int i = 1; i <= n; i++) f[i] = f[i-1]*i;
    dfs(0);
    cout << ans << '\n';
    return 0;
}