//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
l[i]：从左端 1 到 i，这一段被 G 完全覆盖（即向右延伸方向是否全部是 G）。l[i]=1 表示 1..i 全是 G。
r[i]：从 i 到右端 n，这段是不是全 G。r[i]=1 表示 i..n 全是 G。
p[]：所有非 G（"坏点"）的下标集合，tot 是坏点个数。
pre[i]：以 i 结尾的最长连续 G 前缀段长。
suf[i]：以 i 开头的最长连续 G 后缀段长。
cnt：字符串中 G 的总个数。
mx：不移动任何 G 时，原串里最长的连续 G 段长
l[i]=1 当且仅当当前位置是 G 且左边一路都是 G（即从 1 到 i 全 G）。这是"从最左端往右能连续多少个 G"
r[i]=1 当且仅当从 i 到 n 一路全 G
cnt = 总 G 数；p[] 按顺序记录每个坏点下标，共 tot 个
Suf[i] = 从 i 开始向右的最长连续 G 长度。用后缀递推：前一个 G 则累加，否则清零。
pre[i] = 以 i 结尾的最长连续 G 长度（前缀递推）。
t 在遇到坏点时结算当前 G 段长度到 mx 并清零。
最后再 mx=max(t,mx) 处理字符串结尾可能是 G 的尾巴。
此时 mx = 原串中不操作时的最长连续 G 段
对每个坏点 p[i]：

cur = pre[p[i]-1] + suf[p[i]+1]：越过这个坏点时，左右两边的 G 段长度之和。因为坏点把左右 G 段隔开，若把它两边之一"借"一个 G 过来补上，就能连起来。
如果 cur < cnt：说明字符串里还有其他位置的 G 可以搬过来填这个坏点（因为总 G 数 cnt > cur 才有富余的 G）。此时再检查 l[p[i]-1] || r[p[i]+1]——即坏点靠左端点一侧（或靠右端点一侧）是否从头都是 G，确保有"无 G 可借的散落 G"可动。满足则可把 cur 变为 cur+1（坏点补成 G），更新 ans。
如果 cur == cnt：说明两边的 G 刚好就是全部 G（没有富余 G 可搬），此时只能把坏点当"分隔符"原样保留，最长段就是 cur 本身（不能 +1）
答案 = 取"不操作的最长段 mx"和"搬一个 G 后的最长段 ans"两者更大者。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; i++)
#define per(i,n) for (int i = n; i >= 1; i--)
using namespace std;

constexpr int N = 2e5+5;

int n, cnt, p[N], tot, suf[N], pre[N];
string s;
bool l[N], r[N];
int main() {
    fast;
    cin >> n >> s; s = " " + s;
    rep(i,n) {
        if (s[i] == 'G' || l[i-1] == 1) l[i] = 1;
        else l[i] = 0;
    }
    per(i,n) {
        if (s[i] == 'G' || r[i+1] == 1) r[i] = 1;
        else r[i] = 0;
    }
    rep(i,n) {
        if (s[i] == 'G') cnt++;
        else p[++tot] = i;
    }
    per(i,n) {
        if (s[i] == 'G') suf[i] = suf[i+1] + 1;
        else suf[i] = 0;
    }
    int mx = -1, t = 0;
    rep(i,n) {
        if (s[i] == 'G') pre[i] = pre[i-1] + 1, t++;
        else { pre[i] = 0; mx = max(mx, t); t = 0; }
    }
    mx = max(t, mx);
    int ans = 0;
    rep(i,tot) {
        int cur = pre[p[i]-1] + suf[p[i]+1];
        if (cur < cnt && (l[p[i]-1] || r[p[i]+1])) ans = max(ans, cur+1);
        if (cur == cnt) ans = max(ans, cur);
    }
    cout << max(mx, ans) << '\n';
    return 0;
}