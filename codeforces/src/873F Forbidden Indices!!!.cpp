//
// Created by Psy.C on 2026/10/6.
//
/**
读入字符串 ss，反转存入 s。
读入一串 0/1 标记 tf（也做了反转存储）。
对 s 构建后缀数组 sa 和排名 rk。
计算高度数组 h（相邻后缀的最长公共前缀 LCP）。
用 tf 标记对后缀分类，过滤掉被标记为 0（tf 为假）的后缀，只保留标记为 1 的后缀，重新组织高度数组 h2。
对过滤后的高度数组用单调栈求每个位置的"管辖范围"，从而求Max(高度 × 宽度)——这是典型求"最大矩形面积 / 最长公共前缀覆盖"的经典做法。
输出 ans
读入长度 n 和字符串 ss。
s[i] = ss[n-i+1]：把 ss 逆序放入 s。
逆序读入 n 个 0/1 字符到 tf。
所以 s 与 tf 是对应的（都按反转后的顺序
x[i] 是第一关键字（排名），初始为字符值。
sa 是后缀数组，y 是第二关键字的顺序。
通过 k 倍增（k=1,2,4,...）不断合并子串，直到所有排名唯一（cur >= n）。
每轮做两次计数排序（第二关键字、第一关键字）。
最终得到后缀数组 sa（后缀在字典序中的顺序）
rk[i]：后缀 i 的排名。
标准 Kasai 算法计算高度数组 h[rk[i]] = 后缀 i 与其前一名后缀的最长公共前缀长度
按后缀数组顺序遍历每个后缀。
sa[i] 是第 i 名的后缀起点。
tf[sa[i]] 表示该后缀起点位置的标记。
若该后缀 未被标记（!tf）：用其完整长度 n-sa[i]+1 更新 ans（这类后缀不需要经过后面的过滤）。
若被标记：维护 mn 为当前连续被标记后缀的最小高度。
若从前一个是被标记、当前未标记：把 min(mn, h[i]) 记入 h2（合并一段被标记后缀）。
若前一个也未标记：直接把 h[i] 记入 h2。
这一步相当于把被标记（tf=1）的后缀段压缩掉，只保留未标记部分的高度信息，重新组织成高度数组 h2（长度 tot）。
mn 初值 inf，tf[0]=1 作为哨兵
用过滤后的高度数组 h2 覆盖 h，更新 n 为新长度
求每个 h[i] 作为最小值能向左右延伸的范围：
左边界 l[i]：左边第一个高度 < h[i] 的位置（严格小于）。
右边界 r[i]：右边第一个高度 < h[i] 的位置。
这样每个 h[i] 覆盖的区间长度就是 r[i] - l[i]（减 1 后实际宽度为 r[i]-l[i]-1，但最终公式用了 r[i]-l[i]，需结合边界定义）
对每个位置，计算 h[i] × (r[i]-l[i])，取最大值作为答案 —— 这是求最大矩形面积的标准做法（柱状图中最大矩形 / 直方图最大矩形）。
几何意义：把 h[i] 看成柱子高度，r[i]-l[i] 是其覆盖宽度，总面积最大处对应最优解
 */
#include <bits/stdc++.h>
#define ll long long
#define rep(i,a,b) for (int i=a; i<=b; ++i)
#define per(i,a,b) for (int i=a; i>=b; --i)
using namespace std;
constexpr int N = 2e5+10, M = 130, inf = 2e9;
char ss[N], s[N], ch;
ll n, tf[N], m, x[N], c[N], sa[N], y[N], rk[N], h[N], ans, mn, h2[N], tot, l[N], r[N];
stack<int> st;
int main() {
    scanf("%d%s", &n, ss+1);
    rep(i,1,n) s[i] = ss[n-i+1];
    per(i,n,1) scanf(" %c", &ch), tf[i] = ch-'0';
    m = M - 1;
    rep(i,1,n) x[i] = s[i];
    rep(i,0,m) c[i] = 0;
    rep(i,1,n) c[x[i]]++;
    rep(i,1,m) c[i] += c[i-1];
    per(i,n,1) sa[c[x[i]]--] = i;
    for (int k = 1, cur; k <= n; k <<= 1) {
        cur = 0;
        for (int i = n; i > n-k; --i) y[++cur] = i;
        rep(i,1,n) if (sa[i] > k) y[++cur] = sa[i] - k;
        rep(i,0,m) c[i] = 0;
        rep(i,1,n) c[x[i]]++;
        rep(i,1,m) c[i] += c[i-1];
        per(i,n,1) sa[c[x[y[i]]]--] = y[i];
        cur = y[sa[1]] = 1;
        rep(i,2,n) {
            int a = sa[i] + k > n ? -1 : x[sa[i]+k],
            b = sa[i-1] + k > n ? -1 : x[sa[i-1]+k];
            y[sa[i]] = (x[sa[i]] == x[sa[i-1]]) &&
                (a == b) ? cur : (++cur);
        }
        swap(x, y);//循环更新排名
        if (cur >= n) break;
        m = cur;
    }
    rep(i,1,n) rk[sa[i]] = i;
    int cnt = 0;
    rep(i,1,n) {
        if (rk[i] == 1) continue;
        if (cnt) cnt--;
        while (i+cnt <= n && sa[rk[i]-1]+cnt <= n &&
            s[i+cnt] == s[sa[rk[i]-1]+cnt]) cnt++;
        h[rk[i]] = cnt;
    }
    tf[0] = 1;
    rep(i,1,n) {
        if (!tf[sa[i]]) ans = max(ans, n-sa[i]+1);
        if (tf[sa[i]]) mn = min(mn, h[i]);
        else if (!tf[sa[i]] && tf[sa[i-1]]) h2[++tot] = min(mn, h[i]), mn = inf;
        else h2[++tot] = h[i];
    }
    n = tot;
    rep(i,1,n) h[i] = h2[i];
    rep(i,1,n) {
        while (!st.empty() && h[st.top()] >= h[i]) st.pop();
        if (st.empty()) l[i] = 1; else l[i] = st.top();
        st.push(i);
    }
    while (!st.empty()) st.pop();
    per(i,n,1) {
        while (!st.empty() && h[st.top()] >= h[i]) st.pop();
        if (st.empty()) r[i] = n+1; else r[i] = st.top();
        st.push(i);
    }
    rep(i,1,n) ans = max(ans, h[i]*(r[i]-l[i]));
    cout << ans << '\n';
    return 0;
}