//
// Created by Psy.C on 2026/10/10.
//
/**
n：字符串长度；str[1..n] 只含 'a'、'b'、'?'（? 可当作 a 或 b）。
m：读入的一个"段长"参数。
w、d：每个状态的两个代价维度，做字典序最小化（先比 w，再比 d）
pre[i] = 前缀 1..i 中 ? 的个数。后面用 pre[r] - pre[l-1] 求区间 ? 数，即区间可变的未知字符个数
从后往前，x[i] 表示从位置 i 起，能匹配的 "ab" 交替前缀长度：

若 str[i] 可作 'a'（是 a 或 ?）且 str[i+1] 可作 'b'（是 b 或 ?），则能构成一个 "ab"，长度 = x[i+2] + 2（跳到再后两格继续延伸）。
若 str[i] 可作 a 但 str[i+1] 不能作 b，则只有 'a' 本身，长度 = 1。
若 str[i] 不能作 a，则长度 0。
所以 x[i] 是"从 i 开始最长连续 abab...（a在奇数位、b在偶数位）的匹配长度，均为偶数或结尾单个 a"
初始哨兵放在 n+1，w=0,d=0（空段收益 0）。定义 node 的 operator<：先比 w（小的小），w 相同时比 d（小的小）——即求 w 最小、其次 d 最小
倒序遍历 i：

若 x[i] >= m：说明从位置 i 起能匹配到一段长度 ≥ m 的 "ab…a/b" 片段，可取一段长度为 m 的 "ab" 重复段。此时：
st[i+m] 是后缀 i+m..n 的最优状态（w 最小、d 最小）。取其后，
dp[i] = w + 1：w（段数）+1（新增这一段），表示从 i 开始能取到的"段数"（dp 是一个"段"的收益/数量）。
c[i] = d + (pre[i+m-1]-pre[i-1])：d 加上这个长度为 m 的窗口内 ? 的个数（窗口内 ? 的数量作为"代价/变量数"累加）。注意窗口是 i..i+m-1（pre[i+m-1]-pre[i-1]）。
ans = min(ans, {dp[i], c[i]})：全局答案取所有 i 的 {w=dp[i], d=c[i]} 最小者（字典序：段数 w 最小，再 ? 数 d 最小）。
st[i] = min({dp[i],c[i]}, st[i+1])：后缀最小——st[i] 保存从 i 到 n 这段后缀里 {w,d} 最小的状态，供前面 st[i+m] 查询使用
输出 ans 的 d（即 ? 的累计/代价维度
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 1e6+5;
constexpr ll inf = 1e18;
struct node {
    ll w, d;
    bool friend operator<(const node &a, const node &b) {
        if (a.w == b.w) return a.d < b.d;
        return a.w > b.w;
    }
} st[N];

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

ll n, m, dp[N], c[N];
char str[N];
int pre[N], x[N];
int main() {
    rd(n); scanf("%s", str+1);
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i-1];
        if (str[i] == '?') pre[i] = pre[i-1] + 1;
    }
    for (ll i = n; i >= 1; --i) {
        if (str[i] == 'a' || str[i] == '?') {
            if (str[i+1] == 'b' || str[i+1] == '?')
                x[i] = x[i+2] + 2;
            else x[i] = 1;
        } else x[i] = 0;
    }
    st[n+1] = {.w = 0, .d = 0};
    auto ans = node{.w = -1, .d = inf};
    rd(m);
    for (ll i = n; i >= 1; --i) {
        if (x[i] >= m) {
            auto [w, d] = st[i+m];
            dp[i] = w + 1;
            c[i] = d + pre[i+m-1] - pre[i-1];
        }
        ans = min(ans, {.w = dp[i], .d = c[i]});
        st[i] = min(node{.w = dp[i], .d = c[i]}, st[i+1]);
    }
    cout << ans.d << '\n';
    return 0;
}