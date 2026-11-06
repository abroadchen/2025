//
// Created by Psy.C on 2026/11/6.
//

/**
真正学会的起点..
读入 n, m。
m == 1 的边界：直接输出 n(n+1)/2（即 n*(n+1)/2），这是"长度为 n 的串的子串总数"。说明该题与子串计数有关，且 m=1 时可直接公式。
读入 m×n 矩阵，按列优先存入 s（s[j+(i-1)*n]：先列 j 后行 i），形成一个长度为 len = n*m 的一维数组。
lim = n 作为初始字符集大小（值域上限）
第一轮：把每个元素值 s[i] 作为初始"排名" rk[i]，基数排序得到初始 sa（后缀数组第一轮）。
倍增：b 每次翻倍（1,2,4,...），借助上一个 b 的排序得到 2b 的排序（经典 SA 倍增）。
id：按第二关键字（后缀第 b 位之后）排序的关键字顺序生成。
用rk 做第一关键字桶排。
lst 保存旧排名，cmp(sa[i],sa[i-1]) 判断两后缀是否仍相等（用旧排名比较 lst[x]==lst[y] && lst[x+b]==lst[y+b]），相等则共享排名 num，否则递增。num 达到 len 说明所有后缀排名唯一，提前 break
经典的 Kasai 算法计算 h[rk[i]] = 后缀 i 与其前一名后缀的最长公共前缀长度。
rk[i]==1 跳过。
注意 s[i+num] 的越界问题：s 数组只定义到 len，i+num 可能越界访问到未初始化（但这里是全局数组，超出部分为 0，而元素值域 ≥1 时 0 会自然终止循环，恰好在很多题意下"哨兵"起效）。若题意允许元素值为 0，则这里可能出错——需结合原题值域确认。
单调队列维护一个长度为 m 的滑动窗口内 h 的最小值（q.front() 处是当前窗口最小 h）。
对每个 i ≥ m，累加窗口内最小 h 到 ans。
这是求"所有长度 ≥ / 恰 m 的……最小 LCP"的经典求和。结合 m==1 时输出子串总数，此逻辑大概率是在统计重复子串/公共前缀相关的计数。

*/
#include <bits/stdc++.h>
#define rep(i,n) for(int i=1;i<=n;i++)
#define per(i,n) for(int i=n;i>=1;i--)
#define cmp(x,y) (lst[x]==lst[y]&&lst[x+b]==lst[y+b])
#define ll long long
using namespace std;

constexpr int N = 1e6+10;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, m, s[N], len, lim, cnt[N], rk[N], sa[N], num, id[N], ky[N], lst[N<<1], h[N];
deque<int> q;
ll ans;
int main() {
    n = rd(), m = rd();
    if (m == 1) { cout << ((1ll*(n+1)*n)>>1); return 0; }
    rep(i,m) rep(j,n) s[j+(i-1)*n] = rd();
    len = n*m, lim = n;
    rep(i,len) ++cnt[rk[i]=s[i]];
    rep(i,lim) cnt[i] += cnt[i-1];
    per(i,len) sa[cnt[rk[i]]--] = i;
    for (int b = 1; b <= len; b <<= 1) {
        num = 0;
        for (int i = len; i > len-b; i--) id[++num] = i;
        rep(i,len) if (sa[i] > b) id[++num] = sa[i] - b;
        memset(cnt, 0, sizeof(cnt));
        rep(i,len) ++cnt[ky[i]=rk[id[i]]];
        rep(i,lim) cnt[i] += cnt[i-1];
        per(i,len) sa[cnt[ky[i]]--] = id[i];
        memcpy(lst+1, rk+1, len*sizeof(int));
        num = 0;
        rep(i,len) rk[sa[i]] = cmp(sa[i],sa[i-1])?num:++num;
        if (num == len) break;
        lim = num;
    }
    num = 0;
    rep(i,len) {
        if (rk[i] == 1) continue;//排名 1 的后缀无前驱
        if (num) --num;
        while (s[i+num] == s[sa[rk[i]-1]+num]) ++num;//与排名前一名比 LCP
        h[rk[i]] = num;
    }
    rep(i,len) {
        while (!q.empty() && q.front() <= i-m+1) q.pop_front();
        while (!q.empty() && h[q.back()] >= h[i]) q.pop_back();
        q.push_back(i);
        if (i >= m) ans += h[q.front()];
    }
    cout << ans;
    return 0;
}